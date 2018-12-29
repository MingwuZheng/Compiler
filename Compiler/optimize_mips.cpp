#include "compiler.h"
#include "mips.h"
#define IS_LABEL(x) ((x).paranum==0 && (x).op != "syscall")
#define IS_MOVE(x) ((x).op == "move" || ((x).op == "addiu" && (x).op3 == "0"))
#define FUNC_BEGIN(x) (IS_LABEL(x) && (x).op[0] != '$')
#define BLOCK_END(x) ((x).op == "beq"||(x).op == "bne"||(x).op == "bgt"||(x).op == "bge"||(x).op == "blt"||(x).op == "ble"||(x).op == "j"||(x).op == "jr"||IS_LABEL(x))//û��jal
#define REG_USE(name, mp) ((mp).paranum > 1 && (name == (mp).op2 || name == (mp).op3 || ((mp).op == "sw" && name == (mp).op1)))
#define REG_DEF(name, mp) (!(BLOCK_END((mp))) && ((((mp).op != "sw" && name == (mp).op1) && !((mp).op == "lw" && (mp).calling)) || ((mp).op == "syscall" && name == "$v0")))
#define STACK_PART(mp) (((mp).op == "sw" || (mp).op == "lw") && (mp).calling)
//syscall�ı�$v0
//j��ָ��һ������
//li��la��move��������


extern vector<mips_code>mipscodes;

void folding() {
	for (vector<mips_code>::iterator iter = mipscodes.begin(); iter != mipscodes.end();) {
		if ((*iter).op == "jr" && (*(iter - 1)).op == "jr")
			iter = mipscodes.erase(iter); //����д��mipscode.erase(iter);
		else if (IS_MOVE(*iter) && (*iter).op1 == (*iter).op2)
			iter = mipscodes.erase(iter);
		else iter++;
	}
	if (SAFE_MODE) return;
	for (vector<mips_code>::iterator iter = mipscodes.begin(); iter != mipscodes.end();) {
		if ((*iter).op == "move" && (*iter).op2 == (*(iter - 1)).op1) {
			(*(iter - 1)).op1 = (*iter).op1;
			iter = mipscodes.erase(iter); //����д��mipscode.erase(iter);
		}
		else iter++;
	}
}

void copy_propagation() {
#define REPLACE(src, des, mp) do{if((mp).op=="sw")(mp).op1=src;\
								else{(mp).op2=((mp).op2==des)?src:(mp).op2;\
									(mp).op3=((mp).op3==des)?src:(mp).op3;}}while(0)
	vector<mips_code>::iterator pointer, temp;
	int debugi,debugt;
	for (vector<mips_code>::iterator iter = mipscodes.begin(); iter != mipscodes.end();) {
		debugi = iter - mipscodes.begin();
		if (IS_MOVE(*iter) && (*iter).op1[1] == 't') {
			string des = (*iter).op1, src = (*iter).op2;
			bool delete_flag = true;
			pointer = iter;
            for (temp = iter + 1; temp != mipscodes.end() && !BLOCK_END(*temp); temp++) {
				debugt = temp - mipscodes.begin();
				if (REG_USE(des, *temp) && !(STACK_PART(*temp))) {
					REPLACE(src, des, *temp);
				}
				if (REG_DEF(des, *temp))
					break;
				if (REG_DEF(src, *temp)) {
					for (vector<mips_code>::iterator i = temp + 1; i != mipscodes.end() && !BLOCK_END(*i); i++) {
						if (REG_USE(des, *i))
							delete_flag = false;
					}
					break;
				}
			}
			if (BLOCK_END(*temp) && ((*temp).op1 == des || (*temp).op2 == des)) {
				(*temp).op1 = ((*temp).op1 == des) ? src : (*temp).op1;
				(*temp).op2 = ((*temp).op2 == des) ? src : (*temp).op2;
			}
			if (delete_flag) {
				int steps = temp - pointer - 1;
				for (vector<mips_code>::iterator d = pointer + 1; steps > 0; steps--) {
					if (STACK_PART(*d) && (*d).op1 == des)
						d = mipscodes.erase(d);
					else d++;
				}
				iter = mipscodes.erase(pointer);
			}
			else iter++;
		}
		else iter++;
	}
}

void stack_decrease() {
	for (vector<mips_code>::iterator iter = mipscodes.begin(); iter != mipscodes.end();) {
		if ((*iter).calling && (*iter).op == "sw" && (*iter).op1[1] == 't') {
			string treg = (*iter).op1;
			bool delete_sl = true;
			vector<mips_code>::iterator guard = iter;
			while ((*guard).calling)guard++;
			while (guard!=mipscodes.end() && !BLOCK_END(*guard)) {
				if (REG_USE(treg, *guard) && !(*guard).calling) {
					delete_sl = false;
					break;
				}
				if (REG_DEF(treg, *guard))
					break;
				guard++;
			}
			if (guard != mipscodes.end() && BLOCK_END(*guard)) {
				if ((*guard).op1 == treg || (*guard).op2 == treg)
					delete_sl = false;
			}
			if (delete_sl) {
				for (vector<mips_code>::iterator d = iter + 1; (*d).calling;) {
					if ((*d).op == "lw" && (*d).op1 == treg) {
						d = mipscodes.erase(d);
						break;
					}
					else d++;
				}
				iter = mipscodes.erase(iter);
			}
			else iter++;
		}
		else iter++;
	}
}

bool block_dce() {
	bool continue_delete = false;
	for (vector<mips_code>::iterator iter = mipscodes.begin(); iter != mipscodes.end();) {
		if ((*iter).op != "sw" && (*iter).paranum > 1 && (*iter).op1[1] == 't' && !(*iter).calling && !BLOCK_END(*iter)) {
			string treg = (*iter).op1;
			bool delete_dc = true;
			vector<mips_code>::iterator guard = iter + 1;
			while (guard != mipscodes.end() && !BLOCK_END(*guard)) {
				if (REG_USE(treg, *guard) && !STACK_PART(*guard)) {
					delete_dc = false;
					break;
				}
				if (REG_DEF(treg, *guard))
					break;
				guard++;
			}
			if (guard != mipscodes.end() && BLOCK_END(*guard)) {
				if ((*guard).op1 == treg || (*guard).op2 == treg)
					delete_dc = false;
			}
			if (delete_dc) {
				iter = mipscodes.erase(iter);
				continue_delete = true;
			}
			else iter++;
		}
		else iter++;
	}
	return continue_delete;
}

void mips_optimize() {
	
	if (!SAFE_MODE) {
		copy_propagation();
		stack_decrease();
		while(block_dce());
	}
	folding();
}