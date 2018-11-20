#include "compiler.h"
#include "midcode.h"
#include "analyse.h"
#include <algorithm> 
#define BLOCKMAX 200
#define NONBLK -1
/*
enum qtnry_operator {
	RET, PUSH, CALL, EXIT, ENTER,
	SET, GOTO, BNZ, BZ,
	ADD, SUB, MUL, DIV, NEG,
	EQL, NEQ, GTR, LES, GEQ, LEQ, BECOME,
	PRINT, SCAN, PRINTS,
	ARYL, ARYS
};
*/
extern int qtnry_ptr;
map<string, int> label2pos;

class block {
public:
	int entrance;
	int next1;
	int next2;

	int prenum;
	int pres[BLOCKMAX];

	set<int> gen_pointers;
	set<int> kill_pointers;
	set<int> out_pointers;
	set<int> in_pointers;

	set<string> vars;
	set<string> use_vars;
	set<string> def_vars;
	set<string> in_vars;
	set<string> out_vars;

	block() {
		entrance = -1;
		next1 = -1;
		next2 = -1;
		prenum = 0;
	}
	void addpre(int ptr) {
		pres[prenum] = ptr;
		prenum++;
	}
};


block blocks[BLOCKMAX];

void init_block() {
	blocks[0].entrance = -1;//Èë¿Ú
	blocks[0].prenum = 0;
	blocks[0].next1 = 1;
	blocks[0].next2 = NONBLK;


}