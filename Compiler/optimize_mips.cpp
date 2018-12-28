#include "compiler.h"
#include "mips.h"
#define IS_LABEL(x) ((x).paranum==0 && (x).op != "syscall")
#define IS_MOVE(x) ((x).op == "move" || ((x).op == "addiu" && (x).op3 == "0"))
#define FUNC_BEGIN(x) (IS_LABEL(x) && (x).op[0] != '$')
#define BLOCK_END(x) ((x).op == "beq"||(x).op == "bne"||(x).op == "bgt"||(x).op == "bge"||(x).op == "blt"||(x).op == "ble"||(x).op == "j"||(x).op == "jr"||IS_LABEL(x))//没有jal
#define REG_USE(name, mp) ((mp).paranum > 1 && (name == (mp).op2 || name == (mp).op3 || ((mp).op == "sw" && name == (mp).op1)))
#define REG_DEF(name, mp) ((((mp).op != "sw" && name == (mp).op1) && !((mp).op == "lw" && (mp).calling)) || ((mp).op == "syscall" && name == "$v0"))
//syscall改变$v0
//j类指令一个参数
//li、la和move两个参数


extern vector<mips_code>mipscodes;

void folding() {
	for (vector<mips_code>::iterator iter = mipscodes.begin(); iter != mipscodes.end();) {
		if ((*iter).op == "jr" && (*(iter - 1)).op == "jr")
			iter = mipscodes.erase(iter); //不能写成mipscode.erase(iter);
		else if (IS_MOVE(*iter) && (*iter).op1 == (*iter).op2)
			iter = mipscodes.erase(iter);
		else iter++;
	}
	if (SAFE_MODE) return;
	for (vector<mips_code>::iterator iter = mipscodes.begin(); iter != mipscodes.end();) {
		if ((*iter).op == "move" && (*iter).op2 == (*(iter - 1)).op1) {
			(*(iter - 1)).op1 = (*iter).op1;
			iter = mipscodes.erase(iter); //不能写成mipscode.erase(iter);
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
				if (REG_USE(des, *temp)) {
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
			if (delete_flag)
				iter = mipscodes.erase(pointer);
			else iter++;
		}
		else iter++;
	}
}



void mips_optimize() {
	folding();
	if (SAFE_MODE) return;
	copy_propagation();
}