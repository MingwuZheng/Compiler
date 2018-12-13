#include "compiler.h"
#include "midcode.h"
#include "analyse.h"
#define TREG_NUM 9 //$t9���ڻ���
#define MIDVAR_MAX 4000
#define REGS_OFFSET 32*4//ջ��Ĭ�ϴ�32���Ĵ���
#define STK_BOTTOM "$fp"//ջ�׼Ĵ��� $v1 ���3\$fp
#define GLOBAL "$gp"//����Ϊ��0��ʼ��ȫ�ֱ���
#define TEMP "$t9"
#define TEMP_ "$v1"
#define TREG(x) ("$t" + to_string(x))
#define SREG(x) ("$s" + to_string(x))


#define ISLNUM(x) (((x[0] >= '0') && (x[0] <= '9')) || x[0] == '+' || x[0] == '-')
#define ISLCHAR(x) (x[0] == '\'')
#define ISSVAR(x) (graphs[cur_func - 1].global_var.find(x) != graphs[cur_func - 1].global_var.end())
#define IS_UNALLOC_SVAR(x) (ISSVAR(x) && curgraph.gvar2sreg(x) == -1)

#define ACTAB symtabs[cur_func]
#define curmc midcodes[mcptr]
#define curgraph graphs[cur_func - 1]
fstream mips_f;

int cur_func;//�ǵø���
int midvar[MIDVAR_MAX];
int midnum = 0;//�ǵú����˳����

int mcptr = 0;

int var2offset(string var, bool *sp);
void call_handler();

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
		if (name == "") {//Ĭ�ϵ�������
			bool sp;
			int off = var2offset(queue2var(0), &sp);
			mips_f << "sw " << TREG(queue[0]) << "," << off << "(" << (sp ? "$sp" : GLOBAL) << ")" << endl;//�߳�һ�������ᵼ��֮ǰȡ�õĺ��벻������
			reg[queue[0]] = true;
			queue2var(0) = "";
			for (int i = 0; i < varnum - 1; i++)
				queue[i] = queue[i + 1];	
			varnum--;
			return varnum;
		}
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
			mips_f << "li " << TEMP << "," << name << endl;
			return TEMP;
		}
		else if (ISLCHAR(name)) {
			int ascii = name[1];
			mips_f << "li " << TEMP << "," << ascii << endl;
			return TEMP;
		}
		int off = var2offset(name, &sp);
		if (ISSVAR(name)) {
			if ((sreg = curgraph.gvar2sreg(name)) == -1 ) {
				if (needlw)
					mips_f << "lw " << TEMP << "," << off << "(" << (sp ? "$sp" : GLOBAL) << ")" << endl;
				return TEMP;
			}
			else return SREG(sreg);
		}
		if (ACTAB.ele(name) == NULL && ISGLOBAL(name)) {//��ֹ�ֲ���ȫ�ֱ���ͬ���ı�������
			if (needlw) {
				bool nul;
				int off = var2offset(name, &nul);
				mips_f << "lw " << TEMP << "," << off << "(" << GLOBAL << ")" << endl;
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
				mips_f << "lw " << TREG(reg) << "," << off << "(" << (sp ? "$sp" : GLOBAL) << ")" << endl;
			}
			return TREG(reg);
		}
	}
};
reg_pool rp;

void exit_main() {
	mips_f << "li $v0,10" << endl;
	mips_f << "syscall" << endl;
}

//�����м�����ǵõǼ�
int var2offset(string var, bool *sp) {

	if (var[0] == '#') {
		*sp = true;
		int index;
		string temp = var;
		temp.erase(temp.begin());
		index = stoi(temp);
		if (midvar[index] == 0) {//�½��м����
			midnum++;
			midvar[index] = midnum;
			//mips_f << "sub $fp,$fp,4" << endl;
			return  -4 * midnum;
		}
		else return  -4 * midvar[index];
	}
	if (ACTAB.ele(var) != NULL) {//��ʶ���ھֲ����ű���
		*sp = true;
		return REGS_OFFSET + ACTAB.filledsize - ACTAB.ele(var)->addr - 4;
	}
	else {//��ʶ����ȫ�ַ��ű���
		*sp = false;
		return GTAB.ele(var)->addr;
	}
}

/*//////////////////////////////////
*************<--�洢��32���Ĵ����е�$fp
����			|
����			|->function size
����			|
*************
32���Ĵ���	|->REGS_OFFSET(�͵�ַ���Ŵ�ģ�
*************<--$sp
��ʱ����		|
*************<--$fp
//////////////////////////////////*/
void call_handler() {
	string funcname = (midcodes[mcptr].op == CALL) ? midcodes[mcptr].op1 : midcodes[mcptr].op2;
	int funcsize = symtabs[GTAB.ele(funcname)->addr].filledsize;
	int paranum = 0;
	mips_f << endl;
	while (midcodes[mcptr].op != CALL) {
		paranum++;
		string para = midcodes[mcptr].op1;
		string reg = rp.apply_reg(para, 1);
		mips_f << "sw " << reg << "," << -4 * paranum << "($fp)" << endl;//�����
		mcptr++;
	}
	string retvar = midcodes[mcptr].result;
	for (int i = 8; i < 16; i++) {//��$t0~$t7����ļĴ���ѹջ
		if (!rp.reg[i - 8])
			mips_f << "sw $" << i << "," << -(funcsize + (i + 1) * 4) << "($fp)" << endl;
	}
	for (int i = 16; i < 24; i++) {//��$s0~$s7����ļĴ���ѹջ
		if(curgraph.sreg2var[i-16] != "")
			mips_f << "sw $" << i << "," << -(funcsize + (i + 1) * 4) << "($fp)" << endl;
	}
	if (!rp.reg[8])
		mips_f << "sw $24," << -(funcsize + (24 + 1) * 4) << "($fp)" << endl;
	//for (int i = 29; i < 32; i++) //ѹ$sp,$fp,$ra
		//mips_f << "sw $" << i << "," << -(funcsize + (i + 1) * 4) << "($fp)" << endl;
	mips_f << "sw $ra," << -(funcsize + (31 + 1) * 4) << "($fp)" << endl;//��ѹsp��fp
	//��תǰ����$sp��$fp��Ϊ��������ռ�
	mips_f << "sub " << "$sp,$fp," << REGS_OFFSET + funcsize << endl;
	mips_f << "sub " << "$fp,$sp," << 4 * func_midvars[funcname] << endl;
	//��ת
	mips_f << "jal " << funcname << endl;
	//��ͨ�üĴ�������
	for (int i = 8; i < 16; i++) {//��$t0~$t7����ļĴ�����ջ
		if (!rp.reg[i - 8])
			mips_f << "lw $" << i << "," << (31 - i) * 4 << "($sp)" << endl;
	}
	for (int i = 16; i < 24; i++) {//��$s0~$s7����ļĴ�����ջ
		if (curgraph.sreg2var[i - 16] != "")
			mips_f << "lw $" << i << "," << (31 - i) * 4 << "($sp)" << endl;
	}
	if (!rp.reg[8])
		mips_f << "lw $24," << (31 - 24) * 4 << "($sp)" << endl;
	//mips_f << "lw $fp," << (31 - 30) * 4 << "($sp)" << endl;
	mips_f << "lw $ra," << (31 - 31) * 4 << "($sp)" << endl;

	//ֱ�Ӽ��㷵�غ�ԭ$sp��$fpֵ
	mips_f << "add $fp,$fp," << REGS_OFFSET + funcsize + 4 * func_midvars[funcname] << endl;
	mips_f << "add $sp,$sp," << REGS_OFFSET + funcsize + 4 * func_midvars[GTAB.ele(ACTAB.glbpos)->name] << endl;

	if (retvar != "") {
		string ret_reg = rp.apply_reg(retvar, 0);
		mips_f << "move " << ret_reg << ",$v0" << endl;
	}
	mips_f << endl;
}

void content(string funcname) {
	switch (curmc.op)
	{
	case RET: {
		if (curmc.op1 != "") {
			string reg = rp.apply_reg(curmc.op1, 1);
			mips_f << "move " << "$v0," << reg << endl;
		}
		if(funcname!="main")
			mips_f << "jr $ra" << endl;
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
		mips_f << curmc.op1 << ":" << endl;
		break;
	}
	case GOTO: {
		mips_f << "j " << curmc.op1 << endl;
		break;
	}
	case ADD: {
		int res;
		string res_reg = rp.apply_reg(curmc.result, 0);//���������Ϊ����������ȫ�ֱ�������ȫ�ֱ���
		if (ISLNUM(curmc.op1) && ISLNUM(curmc.op2)) {//�����ϲ��Ż�
			res = stoi(curmc.op1) + stoi(curmc.op2);
			mips_f << "li " << res_reg << "," << res << endl;
			break;
		}
		if (ISLNUM(curmc.op1)) {
			string op2_reg = rp.apply_reg(curmc.op2, 1);
			mips_f << "addi " << res_reg << "," << op2_reg << "," << curmc.op1 << endl;
		}
		else if (ISLNUM(curmc.op2)) {
			string op1_reg = rp.apply_reg(curmc.op1, 1);
			mips_f << "addi " << res_reg << "," << op1_reg << "," << curmc.op2 << endl;
		}
		else {
			string op1_reg = rp.apply_reg(curmc.op1, 1);
			if (op1_reg == TEMP)
				mips_f << "move " << TEMP_ << "," << op1_reg << endl;
			string op2_reg = rp.apply_reg(curmc.op2, 1);
			mips_f << "add " << res_reg << "," << ((op1_reg == TEMP) ? TEMP_ : op1_reg) << "," << op2_reg << endl;
		}
		break;
	}
	case SUB: {
		int res;
		string res_reg = rp.apply_reg(curmc.result, 0);
		if (ISLNUM(curmc.op1) && ISLNUM(curmc.op2)) {//�����ϲ��Ż�
			res = stoi(curmc.op1) - stoi(curmc.op2);
			mips_f << "li " << res_reg << "," << res << endl;
			break;
		}
		string op1_reg = rp.apply_reg(curmc.op1, 1);
		if (op1_reg == TEMP)
			mips_f << "move " << TEMP_ << "," << op1_reg << endl;
		string op2_reg = rp.apply_reg(curmc.op2, 1);
		mips_f << "sub " << res_reg << "," << ((op1_reg == TEMP) ? TEMP_ : op1_reg) << "," << op2_reg << endl;
		break;
	}
	case MUL: {
		int res;
		string res_reg = rp.apply_reg(curmc.result, 0);
		if (ISLNUM(curmc.op1) && ISLNUM(curmc.op2)) {//�����ϲ��Ż�
			res = stoi(curmc.op1) * stoi(curmc.op2);
			mips_f << "li " << res_reg << "," << res << endl;
			break;
		}
		string op1_reg = rp.apply_reg(curmc.op1, 1);
		if (op1_reg == TEMP)
			mips_f << "move " << TEMP_ << "," << op1_reg << endl;
		string op2_reg = rp.apply_reg(curmc.op2, 1);
		mips_f << "mul " << res_reg << "," << ((op1_reg == TEMP) ? TEMP_ : op1_reg) << "," << op2_reg << endl;
		break;
	}
	case DIV: {
		int res;
		string res_reg = rp.apply_reg(curmc.result, 0);
		if (ISLNUM(curmc.op1) && ISLNUM(curmc.op2)) {//�����ϲ��Ż�
			res = stoi(curmc.op1) / stoi(curmc.op2);
			mips_f << "li " << res_reg << "," << res << endl;
			break;
		}
		string op1_reg = rp.apply_reg(curmc.op1, 1);
		if (op1_reg == TEMP)
			mips_f << "move " << TEMP_ << "," << op1_reg << endl;
		string op2_reg = rp.apply_reg(curmc.op2, 1);
		mips_f << "div " << res_reg << "," << ((op1_reg == TEMP) ? TEMP_ : op1_reg) << "," << op2_reg << endl;
		break;
	}
	case NEG: {
		string res_reg = rp.apply_reg(curmc.result,0);
		if (ISLNUM(curmc.op1)) 
			mips_f << "li " << res_reg << "," << -stoi(curmc.op1) << endl;
		else {
			string op1_reg = rp.apply_reg(curmc.op1, 1);
			mips_f << "sub " << res_reg << ",$0," << op1_reg << endl;
		}
		if (ISGLOBAL(curmc.result) || IS_UNALLOC_SVAR(curmc.result)) {
			bool sp;
			int off = var2offset(curmc.result, &sp);
			mips_f << "sw " << res_reg << "," << off << "(" << (sp ? "$sp" : GLOBAL) << ")" << endl;
		}
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
		string op1_reg = rp.apply_reg(curmc.op1,1);
		if (op1_reg == TEMP)
			mips_f << "move " << TEMP_ << "," << op1_reg << endl;
		string op2_reg = rp.apply_reg(curmc.op2,1);
		mcptr++;
		if (curmc.op == BNZ)
			mips_f << "beq " << ((op1_reg == TEMP) ? TEMP_ : op1_reg) << "," << op2_reg << "," << curmc.op1 << endl;
		else mips_f << "bne " << ((op1_reg == TEMP) ? TEMP_ : op1_reg) << "," << op2_reg << "," << curmc.op1 << endl;
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
		string op1_reg = rp.apply_reg(curmc.op1,1);
		if (op1_reg == TEMP)
			mips_f << "move " << TEMP_ << "," << op1_reg << endl;
		string op2_reg = rp.apply_reg(curmc.op2,1);
		mcptr++;
		if (curmc.op == BNZ)
			mips_f << "bne " << ((op1_reg == TEMP) ? TEMP_ : op1_reg) << "," << op2_reg << "," << curmc.op1 << endl;
		else mips_f << "beq " << ((op1_reg == TEMP) ? TEMP_ : op1_reg) << "," << op2_reg << "," << curmc.op1 << endl;
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
		string op1_reg = rp.apply_reg(curmc.op1, 1);
		if (op1_reg == TEMP)
			mips_f << "move " << TEMP_ << "," << op1_reg << endl;
		string op2_reg = rp.apply_reg(curmc.op2, 1);
		mcptr++;
		if (curmc.op == BNZ)
			mips_f << "bgt " << ((op1_reg == TEMP) ? TEMP_ : op1_reg) << "," << op2_reg << "," << curmc.op1 << endl;
		else mips_f << "ble " << ((op1_reg == TEMP) ? TEMP_ : op1_reg) << "," << op2_reg << "," << curmc.op1 << endl;
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
		string op1_reg = rp.apply_reg(curmc.op1, 1);
		if (op1_reg == TEMP)
			mips_f << "move " << TEMP_ << "," << op1_reg << endl;
		string op2_reg = rp.apply_reg(curmc.op2, 1);
		mcptr++;
		if (curmc.op == BNZ)
			mips_f << "blt " << ((op1_reg == TEMP) ? TEMP_ : op1_reg) << "," << op2_reg << "," << curmc.op1 << endl;
		else mips_f << "bge " << ((op1_reg == TEMP) ? TEMP_ : op1_reg) << "," << op2_reg << "," << curmc.op1 << endl;
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
		string op1_reg = rp.apply_reg(curmc.op1, 1);
		if (op1_reg == TEMP)
			mips_f << "move " << TEMP_ << "," << op1_reg << endl;
		string op2_reg = rp.apply_reg(curmc.op2, 1);
		mcptr++;
		if (curmc.op == BNZ)
			mips_f << "bge " << ((op1_reg == TEMP) ? TEMP_ : op1_reg) << "," << op2_reg << "," << curmc.op1 << endl;
		else mips_f << "blt " << ((op1_reg == TEMP) ? TEMP_ : op1_reg) << "," << op2_reg << "," << curmc.op1 << endl;
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
		string op1_reg = rp.apply_reg(curmc.op1, 1);
		if (op1_reg == TEMP)
			mips_f << "move " << TEMP_ << "," << op1_reg << endl;
		string op2_reg = rp.apply_reg(curmc.op2, 1);
		mcptr++;
		if (curmc.op == BNZ)
			mips_f << "ble " << ((op1_reg == TEMP) ? TEMP_ : op1_reg) << "," << op2_reg << "," << curmc.op1 << endl;
		else mips_f << "bgt " << ((op1_reg == TEMP) ? TEMP_ : op1_reg) << "," << op2_reg << "," << curmc.op1 << endl;
		break;
	}
	case BECOME: {
		string res_reg = rp.apply_reg(curmc.result,0);
		if (ISLNUM(curmc.op1))
			mips_f << "li " << res_reg << "," << stoi(curmc.op1) << endl;
		else if (ISLCHAR(curmc.op1))
			mips_f << "li " << res_reg << "," << (int)curmc.op1[1] << endl;
		else {
			string op1_reg = rp.apply_reg(curmc.op1, 1);//�����п��ܲ�������TEMP�����������Ǹ�ֵ����������
			mips_f << "move " << res_reg << "," << op1_reg << endl;
		}
		if (ISGLOBAL(curmc.result) || IS_UNALLOC_SVAR(curmc.result)) {
			bool sp;
			int off = var2offset(curmc.result, &sp);
			mips_f << "sw " << res_reg << "," << off << "(" << (sp ? "$sp" : GLOBAL) << ")" << endl;
		}
		break;
	}
	case PRINT: {
		mips_f << "li $v0,1" << endl;
		string res_reg = rp.apply_reg(curmc.op1, 1);
		mips_f << "move $a0," << res_reg << endl;
		mips_f << "syscall" << endl;
		break;
	}
	case SCAN: {
		string res_reg = rp.apply_reg(curmc.op1, 0);
		mips_f << "li $v0,5" << endl;
		mips_f << "syscall" << endl;
		mips_f << "move " << res_reg << ",$v0" << endl;
		if (ISGLOBAL(curmc.op1) || IS_UNALLOC_SVAR(curmc.op1)) {
			bool sp;
			int off = var2offset(curmc.op1, &sp);
			mips_f << "sw " << res_reg << "," << off << "(" << (sp ? "$sp" : GLOBAL) << ")" << endl;
		}
		break;
	}
	case SCANC: {
		string res_reg = rp.apply_reg(curmc.op1, 0);
		mips_f << "li $v0,12" << endl;
		mips_f << "syscall" << endl;
		mips_f << "move " << res_reg << ",$v0" << endl;
		if (ISGLOBAL(curmc.op1) || IS_UNALLOC_SVAR(curmc.op1)) {
			bool sp;
			int off = var2offset(curmc.op1, &sp);
			mips_f << "sw " << res_reg << "," << off << "(" << (sp ? "$sp" : GLOBAL) << ")" << endl;
		}
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
		string res = rp.apply_reg(curmc.op1, 1);
		mips_f << "move $a0," << res << endl;
		mips_f << "syscall" << endl;
		break;
	}
	case ARYL: {
		bool sp;
		int off = var2offset(curmc.op1, &sp);
		string des = rp.apply_reg(curmc.result, 0);
		mips_f << "add " << TEMP_ << "," << (sp ? "$sp" : GLOBAL) << "," << off << endl;
		if (ISLNUM(curmc.op2)) 
			mips_f << "lw " << des << "," << 4 * stoi(curmc.op2) << "(" << TEMP_ << ")" << endl;
		else {
			string idx = rp.apply_reg(curmc.op2, 1);
			mips_f << "sll " << TEMP << "," << idx << ",2" << endl;
			mips_f << "add " << TEMP << "," << TEMP_ << "," << TEMP << endl;
			mips_f << "lw " << des << "," << "0(" << TEMP << ")" << endl;
		}
		if (ISGLOBAL(curmc.result) || IS_UNALLOC_SVAR(curmc.result)) {
			bool sp;
			int off = var2offset(curmc.result, &sp);
			mips_f << "sw " << des << "," << off << "(" << (sp ? "$sp" : GLOBAL) << ")" << endl;
		}
		break;
	}
	case ARYS: {         
		bool sp; 
		int off = var2offset(curmc.result, &sp);
		mips_f << "add " << TEMP_ << "," << (sp ? "$sp" : GLOBAL) << "," << off << endl;
		if (ISLNUM(curmc.op1)) {
			string src = rp.apply_reg(curmc.op2, 1);
			mips_f << "sw " << src << "," << 4 * stoi(curmc.op1) << "(" << TEMP_ << ")" << endl;
			break;
		}
		string idx = rp.apply_reg(curmc.op1, 1);
		mips_f << "sll " << TEMP << "," << idx << ",2" << endl;
		mips_f << "add " << TEMP_ << "," << TEMP_ << "," << TEMP << endl;
		string src = rp.apply_reg(curmc.op2,1);//����ļĴ����������п�����Ϊ�����ӵ��¼Ĵ�������Ч����������ֻ����������
		mips_f << "sw " << src << "," << "0(" << TEMP_ << ")" << endl;


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
	for (int i = 0; i < GTAB.ele(name)->var; i++) {//Ϊ������ȫ�ּĴ����Ĳ�������ֵ
		int para_sreg;
		if (ISSVAR(ACTAB.ele(i)->name) && (para_sreg=curgraph.gvar2sreg(ACTAB.ele(i)->name)) != -1) {
			bool sp;
			int off = var2offset(ACTAB.ele(i)->name, &sp);
			mips_f << "lw " << SREG(para_sreg) << "," << off << "($sp)" << endl;
		}
	}
	while (midcodes[mcptr].op != EXIT) {
		for (int i = 0; i < curgraph.blocknum; i++) {//�����һ��������Ŀ�ʼ����ռĴ�����
			if (mcptr == curgraph.blocks[i].entrance)
				rp.flush();
		}
		content(name);
	}
	if (name != "main")
		mips_f << "jr $ra" << endl;
	else exit_main();
	mcptr++;
}


string transform(string a) {
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == '\\') {
			a.insert(i, 1, '\\');
			i++;
		}
	}
	return a;
}
void header() {
	mips_f << ".data" << endl;
	for (int i = 0; i < const_strings.size(); i++)
		mips_f << "    $string" << i << ":" << " .asciiz" << " \"" << transform(const_strings[i]) << "\"" << endl;
	mips_f << ".text" << endl;
	int mainsize = symtabs[GTAB.ele("main")->addr].filledsize;
	mips_f << "    sub " << "$sp,$sp," << REGS_OFFSET + mainsize << endl;
	mips_f << "    move $fp,$sp" << endl;
	mips_f << "    sub " << "$fp,$fp" << "," << 4 * func_midvars["main"] << endl;
	mips_f << "    j main" << endl;
}

void mips_main() {
	mips_f.open("mips.asm", ios::out);
	header();
	while (mcptr < qtnry_ptr && curmc.op == SET) {
		string funcname= curmc.op1;
		mips_f << endl;
		mips_f << funcname << ":" << endl;
		mips_f << endl;
		mcptr++;
		function_handler(funcname);
	}
	mips_f.close();
}