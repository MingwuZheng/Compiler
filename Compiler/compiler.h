#pragma once
#include<ostream>
#include<iostream>
#include<string>
#include<fstream>
#include<cassert>
#include<set>
#include<map>
#include<iomanip>

#define ISNUM(x)		((x >= '0') && (x <= '9'))
#define ISLETTER(x)		(((x >= 'a') && (x <= 'z')) || ((x >= 'A') && (x <= 'Z')) || (x == '_'))
#define ISADD(x)		((x == '+') || (x == '-'))
#define ISMUL(x)		((x == '*') || (x == '/'))
#define ISCHAR(x)		(ISADD(x) || ISMUL(x) || ISLETTER(x) || ISNUM(x))
#define ISSTRCHAR(x)	(x == 32 || x == 33 || ((x >= 35) && (x <= 126)))

#define INT_MAX 4294967295
#define TAB_MAX 100

#define GTAB symtabs[0]
#define CTAB symtabs[tabptr]

using namespace std;
//全局常量
enum symbol {
	INTCON, CHARCON, STRINGCON, CONSTSY, IDENT,
	PLUS, MINUS, MUL, DIV, EQL, NEQ, GTR, GEQ, LSS, LEQ,
	LPT, RPT, LBK, RBK, LBR, RBR, COMMA, SEMICOLON, BECOME,
	IFSY, WHILESY, FORSY, DOSY, ELSESY, MAIN, RETURN, INTSY, CHARSY, VOIDSY,
	PRINTSY, SCANSY
};
enum symType {
	INT, CHAR, VOID
};
enum idType {
	CONST, VAR, ARRAY, FUNCTION, PARA
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
	int ptr;
	int filledsize;
	symbolEle symbols[TAB_MAX];
	symTab() { ptr = 0; filledsize = 0; memset(symbols, 0, sizeof(symbolEle)); }
	void insert(string name, idType idtype, symType symtype, int var, int size, int addr);
	symbolEle *ele(int);
	symbolEle *ele(string);
	//void change(int, int);
};

// 全局变量
extern fstream f;
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
extern symTab symtabs[TAB_MAX];
