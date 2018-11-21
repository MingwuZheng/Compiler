#include "compiler.h"
#include "midcode.h"
#include "analyse.h"
#include <algorithm> 
#define BLOCKMAX 200
#define NONBLK -1
#define IS_FUN_LABEL(x) (x[0] != '@')
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
int qtnry_num;
map<string, int> label2pos;
map<int, int>pos2blk;

class block {
public:
	
	int entrance;
	int exit;
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
		next1 = NONBLK;
		next2 = NONBLK;
		prenum = 0;
	}
	void addpre(int ptr) {
		pres[prenum] = ptr;
		prenum++;
	}
};

class flush_graph {
public:
	string function;
	block blocks[BLOCKMAX];
	//block ENDBLOCK;
	int blocknum;
	flush_graph() {	function = ""; blocknum = 0; }
	int gen_block(int, int);
};

bool is_entrance(int pos) {
	#define ISBRANCH(x) (x == RET || x == EXIT || x == GOTO || x == BNZ || x == BZ)
	//if (pos == 0)
	//	return true;反正不可能是0
	if (midcodes[pos].op == SET) 
		return true;
	if (ISBRANCH(midcodes[pos - 1].op))
		return true;
	return false;
}

int flush_graph::gen_block(int pos, int preblk) {
	int i, curblk;
	if (pos2blk.find(pos) != pos2blk.end()) {
		blocks[pos2blk[pos]].addpre(preblk);
		return;
	}
	if (preblk == NONBLK) {
		blocks[0].entrance = pos;//入口
		blocks[0].next1 = 1;
		blocks[0].next2 = NONBLK;
		blocknum++;
		gen_block(pos + 1, 0);
		return 0;
	}
	if (pos == -1) {
		pos2blk[pos] = blocknum;
		blocks[blocknum].next1 = NONBLK;
		blocks[blocknum].next2 = NONBLK;
		return blocknum++;
	}
	curblk = blocknum;
	blocknum++;
	blocks[curblk].entrance = pos;
	blocks[curblk].addpre(preblk);
	pos2blk[pos] = curblk;
	for (i = pos + 1; !is_entrance(i); i++)
		pos2blk[i] = curblk;
	blocks[curblk].exit = i - 1;
	if (midcodes[i - 1].op == BZ || midcodes[i - 1].op == BNZ) {
		blocks[curblk].next1 = gen_block(i, curblk);
		blocks[curblk].next2 = gen_block(label2pos[midcodes[i - 1].op1], curblk);
	}
	else if (midcodes[i - 1].op == GOTO)
		blocks[curblk].next1 = gen_block(label2pos[midcodes[i - 1].op1], curblk);
	else if (midcodes[i - 1].op == RET || midcodes[i - 1].op == EXIT)
		blocks[curblk].next1 = gen_block(-1, curblk);
	else blocks[curblk].next1 = gen_block(i, curblk);
	return curblk;
}

flush_graph graphs[TAB_MAX];
int graph_ptr = 0;


void init_block() {
	int blockptr = 0;
	qtnry_num = qtnry_ptr;
	
	for (int i = 0; i < qtnry_num; i++) {
		if (midcodes[i].op == SET)
			label2pos[midcodes[i].op1] = i;
	}
	for (int i = 1; i < qtnry_num; i++) {
		if (midcodes[i].op == SET && IS_FUN_LABEL(midcodes[i].op1)) {
			graphs[graph_ptr].function = midcodes[i].op1;
			graphs[graph_ptr].gen_block(i, NONBLK);
			graph_ptr++;
		}
	}

	


}