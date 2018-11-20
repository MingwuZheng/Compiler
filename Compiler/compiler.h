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

#define ISNUM(x)		((x >= '0') && (x <= '9'))
#define ISLETTER(x)		(((x >= 'a') && (x <= 'z')) || ((x >= 'A') && (x <= 'Z')) || (x == '_'))
#define ISADD(x)		((x == '+') || (x == '-'))
#define ISMUL(x)		((x == '*') || (x == '/'))
#define ISCHAR(x)		(ISADD(x) || ISMUL(x) || ISLETTER(x) || ISNUM(x))
#define ISSTRCHAR(x)	(x == 32 || x == 33 || ((x >= 35) && (x <= 126)))

#define INT_MAX 4294967295
#define TAB_MAX 100
#define QTNRY_MAX 1000

#define GTAB symtabs[0]
#define CTAB symtabs[tabptr]

using namespace std;
//全局常量
enum symbol {
	INTCON, CHARCON, STRINGCON, CONSTSY, IDENT,
	PLUS, MINUS, MULSY, DIVSY, EQLSY, NEQSY, GTRSY, GEQSY, LESSY, LEQSY,
	LPT, RPT, LBK, RBK, LBR, RBR, COMMA, SEMICOLON, BECOMESY,
	IFSY, WHILESY, FORSY, DOSY, ELSESY, MAIN, RETURN, INTSY, CHARSY, VOIDSY,
	PRINTSY, SCANSY
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
	PRINT, SCAN, PRINTS,
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
extern fstream input_f;
extern int lc;
extern int cc;
extern char ch;
extern long int num;
extern int lp;
extern char chr;
extern int tabptr;
extern string id;
extern string str;
extern symbol sy;
extern map<char, symbol> sps;//单字
extern map<string, symbol> ksy;//关键字符号映射
extern set<string> key;//关键字
extern symTab symtabs[];
extern vector<string> const_strings;
extern quaternary midcodes[];