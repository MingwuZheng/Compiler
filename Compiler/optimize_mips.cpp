#include "compiler.h"
#include "mips.h"

#define IS_LABEL(x) ((x).paranum==0 && (x).op != "syscall")
#define IS_FUNCLABEL(x) (IS_LABEL(x) && (x).op[0] != '$')
#define IS_MOVE(x) ((x).op == "move" || ((x).op == "addiu" && (x).op3 == "0"))
#define FUNC_BEGIN(x) (IS_LABEL(x) && (x).op[0] != '$')
#define BLOCK_END(x) ((x).op == "beq"||(x).op == "bne"||(x).op == "bgt"||(x).op == "bge"||(x).op == "blt"||(x).op == "ble"||(x).op == "j"||(x).op == "jr"||IS_LABEL(x))//没有jal
#define REG_USE(name, mp) ((mp).paranum > 1 && (name == (mp).op2 || name == (mp).op3 || ((mp).op == "sw" && name == (mp).op1)))
#define REG_DEF(name, mp) (!(BLOCK_END((mp))) && ((((mp).op != "sw" && name == (mp).op1) && !((mp).op == "lw" && (mp).calling)) || ((mp).op == "syscall" && name == "$v0")))
#define STACK_PART(mp) (((mp).op == "sw" || (mp).op == "lw") && (mp).calling)
//syscall改变$v0
//j类指令一个参数
//li、la和move两个参数

extern map<string, vector<set<string>>>funcname2outtab;
extern vector<mips_code>mipscodes;

void folding() {
	for (vector<mips_code>::iterator iter = mipscodes.begin(); iter != mipscodes.end();) {
		if ((*iter).op == "jr" && (*(iter - 1)).op == "jr")
			iter = mipscodes.erase(iter); //不能写成mipscode.erase(iter);
		else if (IS_MOVE(*iter) && (*iter).op1 == (*iter).op2)
			iter = mipscodes.erase(iter);
		else iter++;
	}
	if (!SAFE_MODE) {
		for (vector<mips_code>::iterator iter = mipscodes.begin(); iter != mipscodes.end();) {
			if ((*iter).op == "move" && (*iter).op2 == (*(iter - 1)).op1 && REG_DEF((*iter).op2, (*(iter - 1)))) {
				(*(iter - 1)).op1 = (*iter).op1;
				iter = mipscodes.erase(iter); //不能写成mipscode.erase(iter);
			}
			else iter++;
		}
	}
	for (vector<mips_code>::iterator iter = mipscodes.begin(); iter != mipscodes.end();) {
		if ((*iter).op == "div" && !ISLNUM((*iter).op3)) {
			string res = (*iter).op1;
			(*iter).paranum = 2;
			(*iter).op1 = (*iter).op2;
			(*iter).op2 = (*iter).op3;
			(*iter).op3 = "";
			mips_code* mflo = new mips_code(1, "mflo", res, "", "", false);
			iter = mipscodes.insert(iter + 1, *mflo);
		}
		iter++;
	}

	vector<mips_code>::iterator i, temp;
	for (i = mipscodes.begin(); i != mipscodes.end();) {
		bool delete_goto = false;
		if ((*i).op == "j") {
			temp = i + 1;
			string taget_label = (*i).op1;
			while (IS_LABEL(*temp)) {
				if ((*temp).op == taget_label) {
					delete_goto = true;
					break;
				}
				temp++;
			}
			if (delete_goto)
				i = mipscodes.erase(i);
			else i++;
		}
		else i++;
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
			if (temp != mipscodes.end() && (BLOCK_END(*temp) && ((*temp).op1 == des || (*temp).op2 == des))) {
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
			while (guard != mipscodes.end() && !BLOCK_END(*guard)) {
				if (REG_USE(treg, *guard) && !STACK_PART(*guard)) {
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
	
	string curfunc;
	int curcall;
	for (vector<mips_code>::iterator iter = mipscodes.begin(); iter != mipscodes.end();) {
		if (IS_FUNCLABEL(*iter)) {
			curcall = -1;
			curfunc = (*iter).op;
		}
		if ((*iter).calling && !(*(iter - 1)).calling)
			curcall++;
		if ((*iter).calling && (*iter).op == "sw" && ((*iter).op1[1] == 's' || (*iter).op1[1] == 'a')) {
			string sreg = (*iter).op1;
			bool delete_sl = true;
			vector<mips_code>::iterator guard = iter;
			while ((*guard).calling)guard++;
			while (guard != mipscodes.end() && !BLOCK_END(*guard)) {
				if (REG_USE(sreg, *guard) && !STACK_PART(*guard)) {
					delete_sl = false;
					break;
				}
				if (REG_DEF(sreg, *guard) && !(*guard).calling)
					break;
				guard++;
			}
			if (guard != mipscodes.end() && BLOCK_END(*guard)) {
				if ((*guard).op1 == sreg || (*guard).op2 == sreg)
					delete_sl = false;
			}
			if (delete_sl && (funcname2outtab[curfunc])[curcall].find(sreg) != (funcname2outtab[curfunc])[curcall].end()) {
				for (vector<mips_code>::iterator d = iter + 1; (*d).calling;) {
					if ((*d).op == "lw" && (*d).op1 == sreg) {
						d = mipscodes.erase(d);
						break;
					}
					else d++;
				}
				iter = mipscodes.erase(iter);
				if ((*iter).calling && !(*(iter - 1)).calling)
					curcall--;
			}
			else iter++;
		}
		else iter++;
	}
	
	for (vector<mips_code>::iterator iter = mipscodes.begin(); iter != mipscodes.end();) {
		if ((*iter).calling && (*iter).op == "sw" && ((*iter).op1[1] == 's' || (*iter).op1[1] == 'a' || (*iter).op1[1] == 't')) {
			string reg = (*iter).op1;
			bool delete_sl = true;
			vector<mips_code>::iterator guard = iter;
			while ((*guard).op != "jal")guard++;
			string desfunc = (*guard).op1;
			guard = mipscodes.begin();
			while (!IS_FUNCLABEL(*guard) || (*guard).op != desfunc)guard++;
			guard++;
			while (guard != mipscodes.end() && !IS_FUNCLABEL(*guard)) {
				if (REG_DEF(reg, *guard) && !STACK_PART(*guard)) {
					delete_sl = false;
					break;
				}
				guard++;
			}
			if (delete_sl) {
				for (vector<mips_code>::iterator d = iter + 1; (*d).calling;) {
					if ((*d).op == "lw" && (*d).op1 == reg) {
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