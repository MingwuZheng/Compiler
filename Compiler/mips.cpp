#include "compiler.h"
#include "midcode.h"

#define REG_NUM 9 //$t9用于缓冲
#define MIDVAR_MAX 100
#define FUNCTION_OFFSET 32*4//栈底默认存32个寄存器
#define STK_BOTTOM "$3"//栈底寄存器 $v1 编号3


fstream mips_f;
int cur_func;//记得更新

int midvar[MIDVAR_MAX];
int midnum = 0;//记得函数退出清空



class reg_pool {
	bool reg[REG_NUM];
	string queue[REG_NUM];
	int varnum;

	reg_pool() {
		varnum = 0;
		for (int i = 0; i < REG_NUM; i++) {
			reg[i] = true;
			queue[i] = "";
		}
	}

	int var2reg(string var) {
		for (int i = 0; i < varnum; i++) {
			if (queue[i] == var)
				return i;
		}
		return -1;
	}



};

//读到中间变量记得登记
int var2offset(string var,bool *sp) {
#define ACTAB symtabs[cur_func]
	if (var[0] == '#') {
		*sp = true;
		int index;
		string temp = var;
		temp.erase(temp.begin()); 
		index = stoi(temp);
		if (midvar[index] == 0) {//新建中间变量
			midnum++;
			midvar[index] = midnum;
			mips_f << "sub " << STK_BOTTOM << "," << STK_BOTTOM << ",4" << endl;
			return  -4 * midnum;
		}
		else return  -4 * midvar[index];
	}
	if (ACTAB.ele(var) == NULL) {//标识符在全局符号表里
		*sp = false;
		return 4 * GTAB.ele(var)->addr;
	}
	else {//标识符在局部符号表里
		*sp = true;
		return 4 * ACTAB.ele(var)->addr + FUNCTION_OFFSET;
	}

}






void header() {
	mips_f << ".data" << endl;
	for (int i = 0; i < const_strings.size(); i++)
		mips_f << "\t$string" << i << ":" << " .asciiz" << " \"" << const_strings[i] << "\""<<endl;
	/////////////
	mips_f << "j main" << endl;
}



void mips_main() {
	mips_f.open("mips.txt");




}