#include "compiler.h"
#include "midcode.h"
#include "analyse.h"
#include "mips.h"



extern int graph_ptr;
fstream mips_f;
int cur_func;//记得更新
int midvar[MIDVAR_MAX];
int midnum = 0;//记得函数退出清空
int mcptr = 0;
bool calling = false;

int var2offset(string var, bool *sp);
void call_handler();
void emit_mips(int, string, string, string, string);
class reg_pool {
#define queue2var(x) reg2var[queue[x]]
public:
	bool reg[TREG_NUM];
	string reg2var[TREG_NUM];
	int queue[TREG_NUM];
	int varnum;

	reg_pool() {
		varnum = 0;
		for (int i = 0; i < TREG_NUM; i++) {
			reg[i] = true;
			queue[i] = -1;
			reg2var[i] = "";
		}
	}
	void flush() {
		varnum = 0;
		for (int i = 0; i < TREG_NUM; i++) {
			reg[i] = true;
			queue[i] = -1;
			reg2var[i] = "";
		}
	}
	int var2reg(string var) {
		for (int i = 0; i < TREG_NUM; i++) {
			if (reg2var[i] == var)
				return i;
		}
		return -1;
	}
	int reg2queue(int reg) {
		for (int i = 0; i < TREG_NUM; i++) {
			if (queue[i] == reg)
				return i;
		}
		return -1;
	}
	int ralloc() {
		for (int i = 0; i < TREG_NUM; i++) {
			if (reg[i] == true) {
				reg[i] = false;
				return i;
			}
		}
		return -1;
	}
	int dequeue(string name) {
		//if (name == "") {//默认弹出队首
		bool sp;
		int off = var2offset(queue2var(0), &sp);
		emit_mips(3, "sw", TREG(queue[0]), to_string(off), (sp ? "$sp" : GLOBAL));//踢出一个变量会导致之前取得的号码不再能用
		reg[queue[0]] = true;
		queue2var(0) = "";
		for (int i = 0; i < varnum - 1; i++)
			queue[i] = queue[i + 1];
		varnum--;
		return varnum;
		//}
	}
	int inqueue(string name) {
		if (varnum < TREG_NUM) {
			int r = ralloc();
			queue[varnum++] = r;
			reg2var[r] = name;
			return r;
		}
		else {
			int i = dequeue("");
			queue[i] = ralloc();
			queue2var(i) = name;
			varnum++;
			return queue[i];
		}
	}
	void toend(int reg) {
		int i = 0;
		int index = reg2queue(reg);
		for (i = index; i < varnum - 1; i++)
			queue[i] = queue[i + 1];
		queue[i] = reg;
	}
	string apply_reg(string name, bool needlw) {
		bool sp;
		int sreg;
		if (ISLNUM(name)) {
			emit_mips(2, "li", TEMP, name, "");
			return TEMP;
		}
		else if (ISLCHAR(name)) {
			int ascii = name[1];
			emit_mips(2, "li", TEMP, to_string(ascii), "");
			return TEMP;
		}
		int off = var2offset(name, &sp);
		for (int i = 0; i < MAX_REG_PARA(ACTAB.glbpos); i++) {
			if (name == ACTAB.ele(i)->name)
				return "$a" + to_string(i + 1);
		}
		if (ISSVAR(name)) {
			if ((sreg = curgraph.gvar2sreg(name)) == -1) {
				if (needlw)
					emit_mips(3, "lw", TEMP, to_string(off), (sp ? "$sp" : GLOBAL));
				return TEMP;
			}
			else return SREG(sreg);
		}
		if (ACTAB.ele(name) == NULL && ISGLOBAL(name)) {//防止局部和全局变量同名的变量覆盖
			if (needlw) {
				bool nul;
				int off = var2offset(name, &nul);
				emit_mips(3, "lw", TEMP, to_string(off), GLOBAL);
			}
			return TEMP;
		}
		int r = var2reg(name);
		if (r != -1) {
			toend(r);
			return TREG(r);
		}
		else {
			int reg = inqueue(name);
			if (needlw) {
				bool sp;
				int off = var2offset(name, &sp);
				emit_mips(3, "lw", TREG(reg), to_string(off), (sp ? "$sp" : GLOBAL));
			}
			return TREG(reg);
		}
	}
};

reg_pool rp;
vector<mips_code>mipscodes;

void exit_main() {
	emit_mips(2, "li", "$v0", "10", "");
	emit_mips(0, "syscall", "", "", "");
}

//读到中间变量记得登记
int var2offset(string var, bool *sp) {

	if (var[0] == '#') {
		*sp = true;
		int index;
		string temp = var;
		temp.erase(temp.begin());
		index = stoi(temp);
		if (midvar[index] == 0) {//新建中间变量
			midnum++;
			midvar[index] = midnum;
			return  -4 * midnum;
		}
		else return  -4 * midvar[index];
	}
	if (ACTAB.ele(var) != NULL) {//标识符在局部符号表里
		*sp = true;
		return REGS_OFFSET + ACTAB.filledsize - ACTAB.ele(var)->addr - 4;
	}
	else {//标识符在全局符号表里
		*sp = false;
		return GTAB.ele(var)->addr;
	}
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
	string funcname = (midcodes[mcptr].op == CALL) ? midcodes[mcptr].op1 : midcodes[mcptr].op2;
	int funcsize = symtabs[GTAB.ele(funcname)->addr].filledsize;
	calling = true;
	for (int i = 5; i < 5 + MAX_REG_PARA(ACTAB.glbpos); i++)//将$a1~$a3分配的寄存器压栈
		emit_mips(3, "sw", "$a" + to_string(i - 4), to_string(-(funcsize + (i + 1) * 4)), "$fp");
	for (int i = 8; i < 16; i++) {//将$t0~$t7分配的寄存器压栈
		if (!rp.reg[i - 8])
			emit_mips(3, "sw", "$t" + to_string(i-8), to_string(-(funcsize + (i + 1) * 4)), "$fp");
	}
	for (int i = 16; i < 24; i++) {//将$s0~$s7分配的寄存器压栈
		if (curgraph.alloced(i - 16))
			emit_mips(3, "sw", "$s" + to_string(i - 16), to_string(-(funcsize + (i + 1) * 4)), "$fp");
	}
	if (!rp.reg[8])
		emit_mips(3, "sw", "$t8", to_string(-(funcsize + (24 + 1) * 4)), "$fp");
	emit_mips(3, "sw", "$ra", to_string(-(funcsize + (31 + 1) * 4)), "$fp");//不压sp和fp
	//传参,注意！这里一定是事先算好的中间变量进行的压栈，不会出现f(a+1,a+2)调用时a是母函数参数，从而$a1=$a1+1,$a2=$a1+2
	int paranum = 0;
	while (midcodes[mcptr].op != CALL) {
		paranum++;
		string reg = rp.apply_reg(midcodes[mcptr].op1, 1);
		if (paranum <= 3) {
			emit_mips(2, "move", "$a" + to_string(paranum), reg, "");
		}
		else {
			//计算要调用函数的流图下标
			string paraname = funcname2tab(funcname).ele(paranum - 1)->name;
			for (int i = 0; i < graph_ptr; i++) {
				if (graphs[i].function == funcname) {
					if (graphs[i].var2sreg.find(paraname) != graphs[i].var2sreg.end() && graphs[i].var2sreg[paraname] != -1)
						emit_mips(2, "move", SREG(graphs[i].var2sreg[paraname]), reg, "");
					else emit_mips(3, "sw", reg, to_string(-4 * paranum), "$fp");//存参数
					break;
				}
			}
		}
		mcptr++;
	}
	string retvar = midcodes[mcptr].result;
	//跳转前处理$sp、$fp，为函数申请空间
	emit_mips(3, "subu", "$sp", "$fp", to_string(REGS_OFFSET + funcsize));
	emit_mips(3, "subu", "$fp", "$sp", to_string(4 * func_midvars[funcname]));
	//跳转
	emit_mips(1, "jal", (funcname == "main") ? "main" : "func_" + funcname, "", "");
	//将通用寄存器弹出
	for (int i = 5; i < 5 + MAX_REG_PARA(ACTAB.glbpos); i++) {//将$a1~$a3分配的寄存器弹栈
		emit_mips(3, "lw", "$a" + to_string(i - 4), to_string((31 - i) * 4), "$sp");
	}
	for (int i = 8; i < 16; i++) {//将$t0~$t7分配的寄存器弹栈
		if (!rp.reg[i - 8])
			emit_mips(3, "lw", "$t" + to_string(i - 8), to_string((31 - i) * 4), "$sp");
	}
	for (int i = 16; i < 24; i++) {//将$s0~$s7分配的寄存器弹栈
		if (curgraph.alloced(i - 16))
			emit_mips(3, "lw", "$s" + to_string(i - 16), to_string((31 - i) * 4), "$sp");
	}
	if (!rp.reg[8])
		emit_mips(3, "lw", "$t8", to_string((31 - 24) * 4), "$sp");
	emit_mips(3, "lw", "$ra", "0", "$sp");
	calling = false;
	//直接计算返回后原$sp、$fp值
	emit_mips(3, "addiu", "$fp", "$fp", to_string(REGS_OFFSET + funcsize + 4 * func_midvars[funcname]));
	emit_mips(3, "addiu", "$sp", "$sp", to_string(REGS_OFFSET + funcsize + 4 * func_midvars[GTAB.ele(ACTAB.glbpos)->name]));

	if (retvar != "") {
		string ret_reg = rp.apply_reg(retvar, 0);
		emit_mips(2, "move", ret_reg, "$v0", "");
	}
	//mips_f << endl;
}

void content(string funcname) {
	switch (curmc.op)
	{
	case RET: {
		if (curmc.op1 != "") {
			string reg = rp.apply_reg(curmc.op1, 1);
			emit_mips(2, "move", "$v0", reg, "");
		}
		if (funcname != "main")
			emit_mips(1, "jr", "$ra", "", "");
		else exit_main();
		break;
	}
	case PUSH: {
		call_handler();
		break;
	}
	case CALL: {
		call_handler();
		break;
	}
	case SET: {
		emit_mips(0, curmc.op1, "", "", "");
		break;
	}
	case GOTO: {
		emit_mips(1, "j", curmc.op1, "", "");
		break;
	}
	case ADD: {
		int res;
		string res_reg = rp.apply_reg(curmc.result, 0);//结果不可能为常数、代码全局变量、块全局变量
		if (ISLNUM(curmc.op1) && ISLNUM(curmc.op2)) {//常量合并优化
			res = stoi(curmc.op1) + stoi(curmc.op2);
			emit_mips(2, "li", res_reg, to_string(res), "");
			break;
		}
		if (ISLNUM(curmc.op1)) {
			string op2_reg = rp.apply_reg(curmc.op2, 1);
			emit_mips(3, "addiu", res_reg, op2_reg, curmc.op1);
		}
		else if (ISLNUM(curmc.op2)) {
			string op1_reg = rp.apply_reg(curmc.op1, 1);
			emit_mips(3, "addiu", res_reg, op1_reg, curmc.op2);
		}
		else {
			string op1_reg = rp.apply_reg(curmc.op1, 1);
			if (op1_reg == TEMP)
				emit_mips(2, "move", TEMP_, op1_reg, "");
			string op2_reg = rp.apply_reg(curmc.op2, 1);
			emit_mips(3, "addu", res_reg, ((op1_reg == TEMP) ? TEMP_ : op1_reg), op2_reg);
		}
		break;
	}
	case SUB: {
		int res;
		string res_reg = rp.apply_reg(curmc.result, 0);
		if (ISLNUM(curmc.op1) && ISLNUM(curmc.op2)) {//常量合并优化
			res = stoi(curmc.op1) - stoi(curmc.op2);
			emit_mips(2, "li", res_reg, to_string(res), "");
			break;
		}
		string op1_reg = rp.apply_reg(curmc.op1, 1);
		if (op1_reg == TEMP)
			emit_mips(2, "move", TEMP_, op1_reg, "");
		string op2_reg = rp.apply_reg(curmc.op2, 1);
		emit_mips(3, "subu", res_reg, ((op1_reg == TEMP) ? TEMP_ : op1_reg), op2_reg);
		break;
	}
	case MUL: {
		int res;
		string res_reg = rp.apply_reg(curmc.result, 0);
		if (ISLNUM(curmc.op1) && ISLNUM(curmc.op2)) {//常量合并优化
			res = stoi(curmc.op1) * stoi(curmc.op2);
			emit_mips(2, "li", res_reg, to_string(res), "");
			break;
		}
		string op1_reg = rp.apply_reg(curmc.op1, 1);
		if (op1_reg == TEMP)
			emit_mips(2, "move", TEMP_, op1_reg, "");
		string op2_reg = rp.apply_reg(curmc.op2, 1);
		emit_mips(3, "mul", res_reg, ((op1_reg == TEMP) ? TEMP_ : op1_reg), op2_reg);
		break;
	}
	case DIV: {
		int res;
		string res_reg = rp.apply_reg(curmc.result, 0);
		if (ISLNUM(curmc.op1) && ISLNUM(curmc.op2)) {//常量合并优化
			res = stoi(curmc.op1) / stoi(curmc.op2);
			emit_mips(2, "li", res_reg, to_string(res), "");
			break;
		}
		string op1_reg = rp.apply_reg(curmc.op1, 1);
		if (op1_reg == TEMP)
			emit_mips(2, "move", TEMP_, op1_reg, "");
		string op2_reg = rp.apply_reg(curmc.op2, 1);
		emit_mips(3, "div", res_reg, ((op1_reg == TEMP) ? TEMP_ : op1_reg), op2_reg);
		break;
	}
	case NEG: {
		string res_reg = rp.apply_reg(curmc.result, 0);
		if (ISLNUM(curmc.op1))
			emit_mips(2, "li", res_reg, to_string(-stoi(curmc.op1)), "");
		else {
			string op1_reg = rp.apply_reg(curmc.op1, 1);
			emit_mips(3, "subu", res_reg, "$0", op1_reg);
		}
		if (ISGLOBAL(curmc.result) || IS_UNALLOC_SVAR(curmc.result)) {
			bool sp;
			int off = var2offset(curmc.result, &sp);
			emit_mips(3, "sw", res_reg, to_string(off), (sp ? "$sp" : GLOBAL));
		}
		break;
	}
	case EQL: {
		bool res;
		if (ISLCHAR(curmc.op1) && ISLCHAR(curmc.op2)) {
			res = (curmc.op1[1] == curmc.op2[1]);
			mcptr++;
			if ((curmc.op == BNZ && res) || (curmc.op == BZ && !res))
				emit_mips(1, "j", curmc.op1, "", "");
			break;
		}
		else if (ISLNUM(curmc.op1) && ISLNUM(curmc.op2)) {
			res = stoi(curmc.op1) == stoi(curmc.op2);
			mcptr++;
			if ((curmc.op == BNZ && res) || (curmc.op == BZ && !res))
				emit_mips(1, "j", curmc.op1, "", "");
			break;
		}
		string op1_reg = rp.apply_reg(curmc.op1, 1);
		if (op1_reg == TEMP)
			emit_mips(2, "move", TEMP_, op1_reg, "");
		string op2_reg = rp.apply_reg(curmc.op2, 1);
		mcptr++;
		if (curmc.op == BNZ)
			emit_mips(3, "beq", ((op1_reg == TEMP) ? TEMP_ : op1_reg), op2_reg, curmc.op1);
		else emit_mips(3, "bne", ((op1_reg == TEMP) ? TEMP_ : op1_reg), op2_reg, curmc.op1);
		break;
	}
	case NEQ: {
		bool res;
		if (ISLCHAR(curmc.op1) && ISLCHAR(curmc.op2)) {
			res = (curmc.op1[1] != curmc.op2[1]);
			mcptr++;
			if ((curmc.op == BNZ && res) || (curmc.op == BZ && !res))
				emit_mips(1, "j", curmc.op1, "", "");
			break;
		}
		else if (ISLNUM(curmc.op1) && ISLNUM(curmc.op2)) {
			res = stoi(curmc.op1) != stoi(curmc.op2);
			mcptr++;
			if ((curmc.op == BNZ && res) || (curmc.op == BZ && !res))
				emit_mips(1, "j", curmc.op1, "", "");
			break;
		}
		string op1_reg = rp.apply_reg(curmc.op1, 1);
		if (op1_reg == TEMP)
			emit_mips(2, "move", TEMP_, op1_reg, "");
		string op2_reg = rp.apply_reg(curmc.op2, 1);
		mcptr++;
		if (curmc.op == BNZ)
			emit_mips(3, "bne", ((op1_reg == TEMP) ? TEMP_ : op1_reg), op2_reg, curmc.op1);
		else emit_mips(3, "beq", ((op1_reg == TEMP) ? TEMP_ : op1_reg), op2_reg, curmc.op1);
		break;
	}
	case GTR: {
		bool res;
		if (ISLCHAR(curmc.op1) && ISLCHAR(curmc.op2)) {
			res = (curmc.op1[1] > curmc.op2[1]);
			mcptr++;
			if ((curmc.op == BNZ && res) || (curmc.op == BZ && !res))
				emit_mips(1, "j", curmc.op1, "", "");
			break;
		}
		else if (ISLNUM(curmc.op1) && ISLNUM(curmc.op2)) {
			res = stoi(curmc.op1) > stoi(curmc.op2);
			mcptr++;
			if ((curmc.op == BNZ && res) || (curmc.op == BZ && !res))
				emit_mips(1, "j", curmc.op1, "", "");
			break;
		}
		string op1_reg = rp.apply_reg(curmc.op1, 1);
		if (op1_reg == TEMP)
			emit_mips(2, "move", TEMP_, op1_reg, "");
		string op2_reg = rp.apply_reg(curmc.op2, 1);
		mcptr++;
		if (curmc.op == BNZ)
			emit_mips(3, "bgt", ((op1_reg == TEMP) ? TEMP_ : op1_reg), op2_reg, curmc.op1);
		else emit_mips(3, "ble", ((op1_reg == TEMP) ? TEMP_ : op1_reg), op2_reg, curmc.op1);
		break;
	}
	case LES: {
		bool res;
		if (ISLCHAR(curmc.op1) && ISLCHAR(curmc.op2)) {
			res = (curmc.op1[1] < curmc.op2[1]);
			mcptr++;
			if ((curmc.op == BNZ && res) || (curmc.op == BZ && !res))
				emit_mips(1, "j", curmc.op1, "", "");
			break;
		}
		else if (ISLNUM(curmc.op1) && ISLNUM(curmc.op2)) {
			res = stoi(curmc.op1) < stoi(curmc.op2);
			mcptr++;
			if ((curmc.op == BNZ && res) || (curmc.op == BZ && !res))
				emit_mips(1, "j", curmc.op1, "", "");
			break;
		}
		string op1_reg = rp.apply_reg(curmc.op1, 1);
		if (op1_reg == TEMP)
			emit_mips(2, "move", TEMP_, op1_reg, "");
		string op2_reg = rp.apply_reg(curmc.op2, 1);
		mcptr++;
		if (curmc.op == BNZ)
			emit_mips(3, "blt", ((op1_reg == TEMP) ? TEMP_ : op1_reg), op2_reg, curmc.op1);
		else emit_mips(3, "bge", ((op1_reg == TEMP) ? TEMP_ : op1_reg), op2_reg, curmc.op1);
		break;
	}
	case GEQ: {
		bool res;
		if (ISLCHAR(curmc.op1) && ISLCHAR(curmc.op2)) {
			res = (curmc.op1[1] >= curmc.op2[1]);
			mcptr++;
			if ((curmc.op == BNZ && res) || (curmc.op == BZ && !res))
				emit_mips(1, "j", curmc.op1, "", "");
			break;
		}
		else if (ISLNUM(curmc.op1) && ISLNUM(curmc.op2)) {
			res = stoi(curmc.op1) >= stoi(curmc.op2);
			mcptr++;
			if ((curmc.op == BNZ && res) || (curmc.op == BZ && !res))
				emit_mips(1, "j", curmc.op1, "", "");
			break;
		}
		string op1_reg = rp.apply_reg(curmc.op1, 1);
		if (op1_reg == TEMP)
			emit_mips(2, "move", TEMP_, op1_reg, "");
		string op2_reg = rp.apply_reg(curmc.op2, 1);
		mcptr++;
		if (curmc.op == BNZ)
			emit_mips(3, "bge", ((op1_reg == TEMP) ? TEMP_ : op1_reg), op2_reg, curmc.op1);
		else emit_mips(3, "blt", ((op1_reg == TEMP) ? TEMP_ : op1_reg), op2_reg, curmc.op1);
		break;
	}
	case LEQ: {
		bool res;
		if (ISLCHAR(curmc.op1) && ISLCHAR(curmc.op2)) {
			res = (curmc.op1[1] <= curmc.op2[1]);
			mcptr++;
			if ((curmc.op == BNZ && res) || (curmc.op == BZ && !res))
				emit_mips(1, "j", curmc.op1, "", "");
			break;
		}
		else if (ISLNUM(curmc.op1) && ISLNUM(curmc.op2)) {
			res = stoi(curmc.op1) <= stoi(curmc.op2);
			mcptr++;
			if ((curmc.op == BNZ && res) || (curmc.op == BZ && !res))
				emit_mips(1, "j", curmc.op1, "", "");
			break;
		}
		string op1_reg = rp.apply_reg(curmc.op1, 1);
		if (op1_reg == TEMP)
			emit_mips(2, "move", TEMP_, op1_reg, "");
		string op2_reg = rp.apply_reg(curmc.op2, 1);
		mcptr++;
		if (curmc.op == BNZ)
			emit_mips(3, "ble", ((op1_reg == TEMP) ? TEMP_ : op1_reg), op2_reg, curmc.op1);
		else emit_mips(3, "bgt", ((op1_reg == TEMP) ? TEMP_ : op1_reg), op2_reg, curmc.op1);
		break;
	}
	case BECOME: {
		string res_reg = rp.apply_reg(curmc.result, 0);
		if (ISLNUM(curmc.op1))
			emit_mips(2, "li", res_reg, curmc.op1, "");
		else if (ISLCHAR(curmc.op1))
			emit_mips(2, "li", res_reg, to_string((int)curmc.op1[1]), "");
		else {
			string op1_reg = rp.apply_reg(curmc.op1, 1);//这里有可能产生复用TEMP，但是由于是赋值，所以无视
			emit_mips(2, "move", res_reg, op1_reg, "");
		}
		if (ISGLOBAL(curmc.result) || IS_UNALLOC_SVAR(curmc.result)) {
			bool sp;
			int off = var2offset(curmc.result, &sp);
			emit_mips(3, "sw", res_reg, to_string(off), (sp ? "$sp" : GLOBAL));
		}
		break;
	}
	case PRINT: {
		emit_mips(2, "li", "$v0", "1", "");
		string res_reg = rp.apply_reg(curmc.op1, 1);
		emit_mips(2, "move", "$a0", res_reg, "");
		emit_mips(0, "syscall", "", "", "");
		break;
	}
	case SCAN: {
		string res_reg = rp.apply_reg(curmc.op1, 0);
		emit_mips(2, "li", "$v0", "5", "");
		emit_mips(0, "syscall", "", "", "");
		emit_mips(2, "move", res_reg, "$v0", "");
		if (ISGLOBAL(curmc.op1) || IS_UNALLOC_SVAR(curmc.op1)) {
			bool sp;
			int off = var2offset(curmc.op1, &sp);
			emit_mips(3, "sw", res_reg, to_string(off), (sp ? "$sp" : GLOBAL));
		}
		break;
	}
	case SCANC: {
		string res_reg = rp.apply_reg(curmc.op1, 0);
		emit_mips(2, "li", "$v0", "12", "");
		emit_mips(0, "syscall", "", "", "");
		emit_mips(2, "move", res_reg, "$v0", "");
		if (ISGLOBAL(curmc.op1) || IS_UNALLOC_SVAR(curmc.op1)) {
			bool sp;
			int off = var2offset(curmc.op1, &sp);
			emit_mips(3, "sw", res_reg, to_string(off), (sp ? "$sp" : GLOBAL));
		}
		break;
	}
	case PRINTS: {
		emit_mips(2, "li", "$v0", "4", "");
		emit_mips(2, "la", "$a0", "$string" + curmc.op1, "");
		emit_mips(0, "syscall", "", "", "");
		break;
	}
	case PRINTC: {
		emit_mips(2, "li", "$v0", "11", "");
		string res = rp.apply_reg(curmc.op1, 1);
		emit_mips(2, "move", "$a0", res, "");
		emit_mips(0, "syscall", "", "", "");
		break;
	}
	case ARYL: {
		bool sp;
		int off = var2offset(curmc.op1, &sp);
		string des = rp.apply_reg(curmc.result, 0);		
		if (ISLNUM(curmc.op2))
			emit_mips(3, "lw", des, to_string(4 * stoi(curmc.op2) + off), (sp ? "$sp" : GLOBAL));
		else {
			emit_mips(3, "addiu", TEMP_, (sp ? "$sp" : GLOBAL), to_string(off));
			string idx = rp.apply_reg(curmc.op2, 1);
			emit_mips(3, "sll", TEMP, idx, "2");
			emit_mips(3, "addu", TEMP, TEMP_, TEMP);
			emit_mips(3, "lw", des, "0", TEMP);
		}
		if (ISGLOBAL(curmc.result) || IS_UNALLOC_SVAR(curmc.result)) {
			bool sp;
			int off = var2offset(curmc.result, &sp);
			emit_mips(3, "sw", des, to_string(off), (sp ? "$sp" : GLOBAL));
		}
		break;
	}
	case ARYS: {
		bool sp;
		int off = var2offset(curmc.result, &sp);
		emit_mips(3, "addiu", TEMP_, (sp ? "$sp" : GLOBAL), to_string(off));
		if (ISLNUM(curmc.op1)) {
			string src = rp.apply_reg(curmc.op2, 1);
			emit_mips(3, "sw", src, to_string(4 * stoi(curmc.op1)), TEMP_);
			break;
		}
		string idx = rp.apply_reg(curmc.op1, 1);
		emit_mips(3, "sll", TEMP, idx, "2");
		emit_mips(3, "addu", TEMP_, TEMP_, TEMP);
		string src = rp.apply_reg(curmc.op2, 1);//申请的寄存器理论上有可能因为被出队导致寄存器号无效，但是这里只申请了三个
		emit_mips(3, "sw", src, "0", TEMP_);
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
	/*
	for (int i = 0; i < GTAB.ele(name)->var; i++) {//为分配了全局寄存器的参数赋初值
		int para_sreg;
		if (ISSVAR(ACTAB.ele(i)->name) && (para_sreg=curgraph.gvar2sreg(ACTAB.ele(i)->name)) != -1) {
			bool sp;
			int off = var2offset(ACTAB.ele(i)->name, &sp);
			emit_mips(3, "lw", SREG(para_sreg), to_string(off), "$sp");
		}
	}
	*/
	while (midcodes[mcptr].op != EXIT) {
		for (int i = 0; i < curgraph.blocknum; i++) {//如果是一个基本块的开始，清空寄存器池
			if (mcptr == curgraph.blocks[i].entrance)
				rp.flush();
		}
		content(name);
	}
	if (name != "main")
		emit_mips(1, "jr", "$ra", "", "");
	else exit_main();
	mcptr++;
}

string transform(string a) {
	for (int i = 0; i < (int)a.size(); i++) {
		if (a[i] == '\\') {
			a.insert(i, 1, '\\');
			i++;
		}
	}
	return a;
}
void header() {
	mips_f << ".data" << endl;
	for (int i = 0; i < (int)const_strings.size(); i++)
		mips_f << "    $string" << i << ":" << " .asciiz" << " \"" << transform(const_strings[i]) << "\"" << endl;
	mips_f << ".text" << endl;
	int mainsize = symtabs[GTAB.ele("main")->addr].filledsize;
	mips_f << "    subu " << "$sp,$sp," << REGS_OFFSET + mainsize << endl;
	mips_f << "    subu " << "$fp,$sp" << "," << 4 * func_midvars["main"] << endl;
	mips_f << "    j main" << endl;
}


void emit_mips(int paranum, string op, string op1, string op2, string op3) {
	mips_code *mp;
	mp = new mips_code(paranum, op, op1, op2, op3, calling);	
	mipscodes.push_back(*mp);
}

void print_mipscode() {
	vector<mips_code>::iterator iter = mipscodes.begin();
	while (iter != mipscodes.end()) {
		if (iter->op == "syscall") 
			mips_f << iter->op << endl;
		else if (iter->op == "sw" || iter->op == "lw") 
			mips_f << iter->op + " " + iter->op1 + "," + iter->op2 + "(" + iter->op3 + ")" << endl;
		else {
			switch (iter->paranum) {
			case 0: {
				mips_f << iter->op + ":" << endl;
				break;
			}
			case 1: {
				mips_f << iter->op + " " + iter->op1 << endl;
				break;
			}
			case 2: {
				mips_f << iter->op + " " + iter->op1 + "," + iter->op2 << endl;
				break;
			}
			case 3: {
				mips_f << iter->op + " " + iter->op1 + "," + iter->op2 + "," + iter->op3 << endl;
				break;
			}
			default:break;
			}
		}
		iter++;
	}
	mips_f.close();
}

void mips_main() {
	mips_f.open("mips.asm", ios::out | ios::trunc);
	header();
	while (mcptr < qtnry_ptr && curmc.op == SET) {
		string funcname= curmc.op1;
		emit_mips(0, (funcname == "main") ? "main" : "func_" + funcname, "", "", "");
		mcptr++;
		function_handler(funcname);
	}
}