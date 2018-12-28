#pragma once
#include<ostream>
#include<iostream>
#include<string>
#include<fstream>
#include<cassert>
#include<set>
#include<map>
#include<iomanip>
#include<vector>
#include <iterator>


#define ISLNUM(x) (((x[0] >= '0') && (x[0] <= '9')) || x[0] == '+' || x[0] == '-')
#define ISLCHAR(x) (x[0] == '\'')
#define ISLITERAL(x) (ISLNUM(x) || ISLCHAR(x))

#define INTEGER_MAX 4294967295
#define TAB_MAX 100
#define QTNRY_MAX 40000
#define MIDVAR_MAX 4000

#define STRONG_TYPE 0
#define SAFE_MODE 0//move向前合并、复制传播
#define FAST_MODE 0//左需求（参数和计算）

#define GTAB symtabs[0]
#define CTAB symtabs[tabptr]
#define funcname2tab(x) symtabs[GTAB.ele(x)->addr]
#define MAX_REG_PARA(function) ((GTAB.ele(function)->var) < 3 ? GTAB.ele(function)->var : 3)

using namespace std;
//全局常量
enum symbol {
	INTCON, CHARCON, STRINGCON, CONSTSY, IDENT,
	PLUS, MINUS, MULSY, DIVSY, EQLSY, NEQSY, GTRSY, GEQSY, LESSY, LEQSY,
	LPT, RPT, LBK, RBK, LBR, RBR, COMMA, SEMICOLON, BECOMESY,
	IFSY, WHILESY, FORSY, DOSY, ELSESY, MAIN, RETURN, INTSY, CHARSY, VOIDSY,
	PRINTSY, SCANSY,
	END_OF_FILE
};
enum symType {
	INT, CHAR, VOID
};
enum idType {
	CONST, VAR, ARRAY, FUNCTION, PARA
};
enum qtnry_operator {
	RET, PUSH, CALL, EXIT, ENTER,
	SET, GOTO, BNZ, BZ,
	ADD, SUB, MUL, DIV, NEG,
	EQL, NEQ, GTR, LES, GEQ, LEQ, BECOME,
	PRINT, SCAN, PRINTS, PRINTC, SCANC,
	ARYL, ARYS
};
typedef struct symbolEle {
	string name;
	idType idtype;
	symType symtype;
	int var;
	int size;
	int addr;
}symbolEle;

//声明
class symTab {
public:
	int glbpos;
	int ptr;
	int filledsize;
	symbolEle symbols[TAB_MAX];
	symTab() { glbpos = -1; ptr = 0; filledsize = 0; }
	void insert(string name, idType idtype, symType symtype, int var, int size, int addr);
	symbolEle *ele(int);
	symbolEle *ele(string);
	int index(string x);
	//void change(int, int);
};
class quaternary {
public:
	qtnry_operator op;
	string op1;
	string op2;
	string result;
	quaternary() { op1 = ""; op2 = ""; op = SET; }
	void set(qtnry_operator op, string op1, string op2, string result) {
		this->op = op;
		this->op1 = op1;
		this->op2 = op2;
		this->result = result;
	}
	void print(fstream &midcode_file);
};
// 全局变量
extern bool ENABLE_EOF;
extern fstream input_f;

extern map<char, symbol> sps;//单字
extern map<string, symbol> ksy;//关键字符号映射
extern set<string> key;//关键字
extern symTab symtabs[];
extern vector<string> const_strings;
extern quaternary midcodes[];