#pragma once
#define TREG_NUM 9 //$t9���ڻ���
#define REGS_OFFSET 32*4//ջ��Ĭ�ϴ�32���Ĵ���
#define STK_BOTTOM "$fp"//ջ�׼Ĵ��� $v1 ���3\$fp
#define GLOBAL "$gp"//����Ϊ��0��ʼ��ȫ�ֱ���
#define TEMP "$t9"
#define TEMP_ "$v1"
#define TREG(x) ("$t" + to_string(x))
#define SREG(x) ("$s" + to_string(x))

#define ISSVAR(x) (graphs[cur_func - 1].global_var.find(x) != graphs[cur_func - 1].global_var.end())
#define IS_UNALLOC_SVAR(x) (ISSVAR(x) && curgraph.gvar2sreg(x) == -1)

#define ACTAB symtabs[cur_func]
#define curmc midcodes[mcptr]
#define curgraph graphs[cur_func - 1]

class mips_code
{
public:
	int paranum;
	string op;
	string op1, op2, op3;
	bool calling;
	mips_code(int paranum, string op, string op1, string op2, string op3, bool calling) {
		this->paranum = paranum; this->op = op; this->op1 = op1; this->op2 = op2; this->op3 = op3; this->calling = calling;
	}
};
void mips_main();
void print_mipscode();