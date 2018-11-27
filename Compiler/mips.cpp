#include "compiler.h"
#include "midcode.h"

#define REG_NUM 9 //$t9用于缓冲
#define MIDVAR_MAX 100
#define REGS_OFFSET 32*4//栈底默认存32个寄存器
#define STK_BOTTOM "$fp"//栈底寄存器 $v1 编号3\$fp
#define GLOBAL "$gp"//先认为是0开始存全局变量
#define TEMP "$t9"
#define TREG(x) ("$t" + to_string(x))

#define ISLNUM(x) (((x[0] >= '0') && (x[0] <= '9')) || x[0] == '+' || x[0] == '-')
#define ISLCHAR(x) (x[0] == '\'')

#define curmc midcodes[mcptr]
fstream mips_f;

int cur_func;//记得更新
int midvar[MIDVAR_MAX];
int midnum = 0;//记得函数退出清空

int mcptr = 0;

int var2offset(string var, bool *sp);
void call_handler();

class reg_pool {
public:
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
	void flush() {
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

	int dequeue(string name) {
		if (name == "") {//弹出队首
			bool sp;
			int off = var2offset(queue[0], &sp);
			mips_f << "add " << TEMP << "," << (sp ? "$sp" : GLOBAL) << "," << off << endl;
			mips_f << "sw " << TREG(var2reg(queue[0])) << "," << TEMP;
			for (int i = 0; i < varnum - 1; i++)
				queue[i] = queue[i + 1];
			varnum--;
			return varnum;
		}
	}
	int inqueue(string name) {
		if (varnum < REG_NUM) {
			for (int i = 0; i < REG_NUM; i++) {
				if (reg[i]) {
					queue[varnum++] = name;
					reg[i] = false;
					return i;
				}
			}
		}
		else {
			int i = dequeue("");
			reg[i] = false;
			queue[varnum++] = name;
			return i;
		}
	}
	int apply_reg(string name) {
		int r = var2reg(name);
		if (ISLNUM(name)) {
			mips_f << "li " << TEMP << "," << name;
			return 9;
		}
		else if (ISLCHAR(name)) {
			int ascii = name[1];
			mips_f << "li " << TEMP << "," << ascii;
			return 9;
		}
		if (r != -1)return r;
		else return inqueue(name);
	}
};
reg_pool rp;

//读到中间变量记得登记
int var2offset(string var, bool *sp) {
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
		return REGS_OFFSET + ACTAB.filledsize - 4 * ACTAB.ele(var)->addr;
	}
}

void content() {
	switch (curmc.op)
	{
	case RET: {
		if (curmc.op1 != "") {
			int reg = rp.apply_reg(curmc.op1);
			mips_f << "move " << "$v0," << TREG(reg) << endl;
		}
		mips_f << "jr" << endl;
		break;
	}
	case PUSH: {
		call_handler();
		break;
	}
	case SET: {
		mips_f << curmc.op1 << ":" << endl;
		break;
	}
	case GOTO: {
		mips_f << "j " << curmc.op1 << endl;
		break;
	}
	case ADD: {
		int res;
		int res_reg = rp.apply_reg(curmc.result);
		if (ISLNUM(curmc.op1) && ISLNUM(curmc.op2)) {//常量合并优化
			res = stoi(curmc.op1) + stoi(curmc.op2);
			mips_f << "li " << TREG(res_reg) << "," << res;
			break;
		}
		int op1_reg = rp.apply_reg(curmc.op1);
		int op2_reg = rp.apply_reg(curmc.op2);
		mips_f << "add " << TREG(res_reg) << "," << TREG(op1_reg) << "," << TREG(op2_reg) << endl;
		break;
	}
	case SUB: {
		int res;
		int res_reg = rp.apply_reg(curmc.result);
		if (ISLNUM(curmc.op1) && ISLNUM(curmc.op2)) {//常量合并优化
			res = stoi(curmc.op1) - stoi(curmc.op2);
			mips_f << "li " << TREG(res_reg) << "," << res;
			break;
		}
		int op1_reg = rp.apply_reg(curmc.op1);
		int op2_reg = rp.apply_reg(curmc.op2);
		mips_f << "sub " << TREG(res_reg) << "," << TREG(op1_reg) << "," << TREG(op2_reg) << endl;
		break;
	}
	case MUL: {
		int res;
		int res_reg = rp.apply_reg(curmc.result);
		if (ISLNUM(curmc.op1) && ISLNUM(curmc.op2)) {//常量合并优化
			res = stoi(curmc.op1) * stoi(curmc.op2);
			mips_f << "li " << TREG(res_reg) << "," << res;
			break;
		}
		int op1_reg = rp.apply_reg(curmc.op1);
		int op2_reg = rp.apply_reg(curmc.op2);
		mips_f << "mul " << TREG(res_reg) << "," << TREG(op1_reg) << "," << TREG(op2_reg) << endl;
		break;
	}
	case DIV: {
		int res;
		int res_reg = rp.apply_reg(curmc.result);
		if (ISLNUM(curmc.op1) && ISLNUM(curmc.op2)) {//常量合并优化
			res = stoi(curmc.op1) / stoi(curmc.op2);
			mips_f << "li " << TREG(res_reg) << "," << res;
			break;
		}
		int op1_reg = rp.apply_reg(curmc.op1);
		int op2_reg = rp.apply_reg(curmc.op2);
		mips_f << "div " << TREG(res_reg) << "," << TREG(op1_reg) << "," << TREG(op2_reg) << endl;
		break;
	}
	case NEG: {
		int res_reg = rp.apply_reg(curmc.result);
		if (ISLNUM(curmc.op1)) {
			mips_f << "li " << TREG(res_reg) << "," << -stoi(curmc.op1) << endl;
			break;
		}
		int op1_reg = rp.apply_reg(curmc.op1);
		mips_f << "sub " << TREG(res_reg) << ",$0," << TREG(op1_reg) << endl;
		break;
	}
	case EQL: {
		bool res;
		if (ISLCHAR(curmc.op1) && ISLCHAR(curmc.op2)) {
			res = (curmc.op1[1] == curmc.op2[1]);
			mcptr++;
			if ((curmc.op == BNZ && res) || (curmc.op == BZ && !res))
				mips_f << "j " << curmc.op1 << endl;
			break;
		}
		else if (ISLNUM(curmc.op1) && ISLNUM(curmc.op2)) {
			res = stoi(curmc.op1) == stoi(curmc.op2);
			mcptr++;
			if ((curmc.op == BNZ && res) || (curmc.op == BZ && !res))
				mips_f << "j " << curmc.op1 << endl;
			break;
		}
		int op1_reg = rp.apply_reg(curmc.op1);
		int op2_reg = rp.apply_reg(curmc.op2);
		int res_reg = rp.apply_reg(curmc.result);
		mcptr++;
		if (curmc.op == BNZ)
			mips_f << "beq " << TREG(op1_reg) << "," << TREG(op2_reg) << "," << curmc.op1 << endl;
		else mips_f << "bne " << TREG(op1_reg) << "," << TREG(op2_reg) << "," << curmc.op1 << endl;
		break;
	}
	case NEQ: {
		bool res;
		if (ISLCHAR(curmc.op1) && ISLCHAR(curmc.op2)) {
			res = (curmc.op1[1] != curmc.op2[1]);
			mcptr++;
			if ((curmc.op == BNZ && res) || (curmc.op == BZ && !res))
				mips_f << "j " << curmc.op1 << endl;
			break;
		}
		else if (ISLNUM(curmc.op1) && ISLNUM(curmc.op2)) {
			res = stoi(curmc.op1) != stoi(curmc.op2);
			mcptr++;
			if ((curmc.op == BNZ && res) || (curmc.op == BZ && !res))
				mips_f << "j " << curmc.op1 << endl;
			break;
		}
		int op1_reg = rp.apply_reg(curmc.op1);
		int op2_reg = rp.apply_reg(curmc.op2);
		int res_reg = rp.apply_reg(curmc.result);
		mcptr++;
		if (curmc.op == BNZ)
			mips_f << "bne " << TREG(op1_reg) << "," << TREG(op2_reg) << "," << curmc.op1 << endl;
		else mips_f << "beq " << TREG(op1_reg) << "," << TREG(op2_reg) << "," << curmc.op1 << endl;
		break;
	}
	case GTR: {
		bool res;
		if (ISLCHAR(curmc.op1) && ISLCHAR(curmc.op2)) {
			res = (curmc.op1[1] > curmc.op2[1]);
			mcptr++;
			if ((curmc.op == BNZ && res) || (curmc.op == BZ && !res))
				mips_f << "j " << curmc.op1 << endl;
			break;
		}
		else if (ISLNUM(curmc.op1) && ISLNUM(curmc.op2)) {
			res = stoi(curmc.op1) > stoi(curmc.op2);
			mcptr++;
			if ((curmc.op == BNZ && res) || (curmc.op == BZ && !res))
				mips_f << "j " << curmc.op1 << endl;
			break;
		}
		int op1_reg = rp.apply_reg(curmc.op1);
		int op2_reg = rp.apply_reg(curmc.op2);
		int res_reg = rp.apply_reg(curmc.result);
		mcptr++;
		if (curmc.op == BNZ)
			mips_f << "bgt " << TREG(op1_reg) << "," << TREG(op2_reg) << "," << curmc.op1 << endl;
		else mips_f << "bleq " << TREG(op1_reg) << "," << TREG(op2_reg) << "," << curmc.op1 << endl;
		break;
	}
	case LES: {
		bool res;
		if (ISLCHAR(curmc.op1) && ISLCHAR(curmc.op2)) {
			res = (curmc.op1[1] < curmc.op2[1]);
			mcptr++;
			if ((curmc.op == BNZ && res) || (curmc.op == BZ && !res))
				mips_f << "j " << curmc.op1 << endl;
			break;
		}
		else if (ISLNUM(curmc.op1) && ISLNUM(curmc.op2)) {
			res = stoi(curmc.op1) < stoi(curmc.op2);
			mcptr++;
			if ((curmc.op == BNZ && res) || (curmc.op == BZ && !res))
				mips_f << "j " << curmc.op1 << endl;
			break;
		}
		int op1_reg = rp.apply_reg(curmc.op1);
		int op2_reg = rp.apply_reg(curmc.op2);
		int res_reg = rp.apply_reg(curmc.result);
		mcptr++;
		if (curmc.op == BNZ)
			mips_f << "ble " << TREG(op1_reg) << "," << TREG(op2_reg) << "," << curmc.op1 << endl;
		else mips_f << "bgeq " << TREG(op1_reg) << "," << TREG(op2_reg) << "," << curmc.op1 << endl;
		break;
	}
	case GEQ: {
		bool res;
		if (ISLCHAR(curmc.op1) && ISLCHAR(curmc.op2)) {
			res = (curmc.op1[1] >= curmc.op2[1]);
			mcptr++;
			if ((curmc.op == BNZ && res) || (curmc.op == BZ && !res))
				mips_f << "j " << curmc.op1 << endl;
			break;
		}
		else if (ISLNUM(curmc.op1) && ISLNUM(curmc.op2)) {
			res = stoi(curmc.op1) >= stoi(curmc.op2);
			mcptr++;
			if ((curmc.op == BNZ && res) || (curmc.op == BZ && !res))
				mips_f << "j " << curmc.op1 << endl;
			break;
		}
		int op1_reg = rp.apply_reg(curmc.op1);
		int op2_reg = rp.apply_reg(curmc.op2);
		int res_reg = rp.apply_reg(curmc.result);
		mcptr++;
		if (curmc.op == BNZ)
			mips_f << "bgeq " << TREG(op1_reg) << "," << TREG(op2_reg) << "," << curmc.op1 << endl;
		else mips_f << "ble " << TREG(op1_reg) << "," << TREG(op2_reg) << "," << curmc.op1 << endl;
		break;
	}
	case LEQ: {
		bool res;
		if (ISLCHAR(curmc.op1) && ISLCHAR(curmc.op2)) {
			res = (curmc.op1[1] <= curmc.op2[1]);
			mcptr++;
			if ((curmc.op == BNZ && res) || (curmc.op == BZ && !res))
				mips_f << "j " << curmc.op1 << endl;
			break;
		}
		else if (ISLNUM(curmc.op1) && ISLNUM(curmc.op2)) {
			res = stoi(curmc.op1) <= stoi(curmc.op2);
			mcptr++;
			if ((curmc.op == BNZ && res) || (curmc.op == BZ && !res))
				mips_f << "j " << curmc.op1 << endl;
			break;
		}
		int op1_reg = rp.apply_reg(curmc.op1);
		int op2_reg = rp.apply_reg(curmc.op2);
		int res_reg = rp.apply_reg(curmc.result);
		mcptr++;
		if (curmc.op == BNZ)
			mips_f << "bleq " << TREG(op1_reg) << "," << TREG(op2_reg) << "," << curmc.op1 << endl;
		else mips_f << "bgt " << TREG(op1_reg) << "," << TREG(op2_reg) << "," << curmc.op1 << endl;
		break;
	}
	case BECOME: {
		int res_reg = rp.apply_reg(curmc.result);
		if (ISLNUM(curmc.op1)) {
			mips_f << "li " << TREG(res_reg) << "," << stoi(curmc.op1) << endl;
			break;
		}
		int op1_reg = rp.apply_reg(curmc.op1);
		mips_f << "move " << TREG(res_reg) << "," << TREG(op1_reg) << endl;
		break;
	}
	case PRINT: {
		mips_f << "li $v0,1" << endl;
		int res = rp.apply_reg(curmc.op1);
		mips_f << "move $a0," << TREG(res) << endl;
		mips_f << "syscall" << endl;
		break;
	}
	case SCAN: {
		int res_reg = rp.apply_reg(curmc.op1);
		mips_f << "li $v0,5" << endl;
		mips_f << "syscall" << endl;
		mips_f << "move " << TREG(res_reg) << ",$v0" << endl;
		break;
	}
	case SCANC: {
		int res_reg = rp.apply_reg(curmc.op1);
		mips_f << "li $v0,12" << endl;
		mips_f << "syscall" << endl;
		mips_f << "move " << TREG(res_reg) << ",$v0" << endl;
		break;
	}
	case PRINTS: {
		mips_f << "li $v0,4" << endl;
		mips_f << "la $a0,$string" << curmc.op1 << endl;
		mips_f << "syscall" << endl;
		break;
	}
	case PRINTC: {
		mips_f << "li $v0,11" << endl;
		int res = rp.apply_reg(curmc.op1);
		mips_f << "move $a0," << TREG(res) << endl;
		mips_f << "syscall" << endl;
		break;
	}
	case ARYL: {
		bool sp;
		int ary = rp.apply_reg(curmc.op1);
		int off = var2offset(curmc.op1, &sp);
		int des = rp.apply_reg(curmc.result);
		mips_f << "add " << TREG(ary) << "," << (sp ? "$sp" : GLOBAL) << "," << off << endl;
		if (ISLNUM(curmc.op2)) {
			mips_f << "lw " << TREG(des) << "," << 4 * stoi(curmc.op2) << "(" << TREG(ary) << ")" << endl;
			break;
		}
		int idx = rp.apply_reg(curmc.op2);
		mips_f << "mul " << TEMP << "," << TREG(idx) << ",4" << endl;
		mips_f << "add " << TEMP << "," << TREG(ary) << "," << TEMP << endl;
		mips_f << "lw " << TREG(des) << "," << 4 * stoi(curmc.op2) << "(" << TEMP << ")" << endl;
		break;
	}
	case ARYS: {         
		bool sp;
		int ary = rp.apply_reg(curmc.result);
		int off = var2offset(curmc.result, &sp);
		mips_f << "add " << TREG(ary) << "," << (sp ? "$sp" : GLOBAL) << "," << off << endl;
		int src = rp.apply_reg(curmc.op2);
		if (ISLNUM(curmc.op1)) {
			mips_f << "sw " << TREG(src) << "," << 4 * stoi(curmc.op1) << "(" << TREG(ary) << ")" << endl;
			break;
		}
		int idx = rp.apply_reg(curmc.op1);//申请的寄存器理论上有可能因为被出队导致寄存器号无效，但是这里只申请了三个
		mips_f << "mul " << TEMP << "," << TREG(idx) << ",4" << endl;
		mips_f << "add " << TEMP << "," << TREG(ary) << "," << TEMP << endl;
		mips_f << "sw " << TREG(src) << "," << 4 * stoi(curmc.op1) << "(" << TEMP << ")" << endl;
		break;
	}
	default:
		break;
	}
	mcptr++;
}


void function_handler(string name) {
	//init
	cur_func = GTAB.ele(name)->addr;
	rp.flush();
	memset(midvar, 0, MIDVAR_MAX);
	midnum = 0;
	//
	mcptr++;
	while (midcodes[mcptr].op != EXIT)
		content();
	mips_f << "jr" << endl;
	mcptr++;
}


/*//////////////////////////////////
*************<--存储的32个寄存器中的$fp
参数			|
常量			|->function size
变量			|
*************
32个寄存器	|->REGS_OFFSET(低地址存编号大的）
*************<--$sp
临时变量		|
*************<--$fp
//////////////////////////////////*/
void call_handler() {
	string funcname = midcodes[mcptr].op2;
	int funcsize = GTAB.ele(funcname)->size;
	int paranum = 0;
	mips_f << endl;
	while (midcodes[mcptr].op != CALL) {
		paranum++;
		string para = midcodes[mcptr].op1;
		int reg = rp.apply_reg(para);
		mips_f << "sw " << TREG(reg) << "," << -4 * paranum << "(" << STK_BOTTOM << ")" << endl;//存参数
		mcptr++;
	}
	string retvar = midcodes[mcptr].op2;
	for (int i = 0; i < 32; i++)//将寄存器压栈
		mips_f << "sw " << TREG(i) << "," << -(funcsize + (i + 1) * 4) << "(" << STK_BOTTOM << ")" << endl;
	mips_f << "sub " << "$sp," << STK_BOTTOM << "," << REGS_OFFSET + funcsize << endl;
	mips_f << "move $fp,$sp" << endl;
	mips_f << "jal " << funcname << endl;
	for (int i = 3; i < 32; i++) //将寄存器弹栈,不要写$v0
		mips_f << "lw " << TREG(i) << "," << i * 4 << "($sp)" << endl;
	if (retvar != "") {
		int ret_reg = rp.apply_reg(retvar);
		mips_f << "move " << TREG(ret_reg) << ",$v0" << endl;
	}
	mips_f << endl;
}

void header() {
	mips_f << ".data" << endl;
	for (int i = 0; i < const_strings.size(); i++)
		mips_f << "    $string" << i << ":" << " .asciiz" << " \"" << const_strings[i] << "\"" << endl;
	mips_f << ".text" << endl;
	mips_f << "j main" << endl;
}

void mips_main() {
	mips_f.open("mips.asm");
	header();
	while (mcptr < qtnry_ptr && curmc.op == SET) {
		string funcname= curmc.op1;
		mips_f << funcname << ":" << endl;
		mcptr++;
		function_handler(funcname);
	}
}