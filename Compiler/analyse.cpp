#include "compiler.h"
#include "midcode.h"
#include "analyse.h"
#include <algorithm> 
#define BLOCKMAX 200
#define NONBLK -1
#define IS_FUN_LABEL(x) (x[0] != '$')
#define ISMIDVAR(x) (x[0] == '#')
#define MID2NUM(x) (stoi(x.erase(0)))
#define ISGLOBAL(x) (GTAB.ele(x) != NULL)
#define ISLCONST(x) (x[0] == '\'' || (((x[0] >= '0') && (x[0] <= '9')) || x[0] == '+' || x[0] == '-'))

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

	set<string> vars;
	bool use[TAB_MAX];
	bool def[TAB_MAX]; 

	bool in[TAB_MAX];
	bool out[TAB_MAX];


	string sreg2var[8];
	string treg2mvar[8];
	int treg;
	int sreg;


	block() {
		entrance = -1;
		next1 = NONBLK;
		next2 = NONBLK;
		prenum = 0;
		treg = 0;
		sreg = 0;
		for (int i = 0; i < TAB_MAX; i++) {
			use[i] = false;
			def[i] = false;
			in[i] = false;
			out[i] = false;
		}
		for (int i = 0; i < 8; i++){
			sreg2var[i] = "";
			treg2mvar[i] = "";
		}
	}
	void addpre(int ptr) {
		pres[prenum] = ptr;
		prenum++;
	}
	void treg_alloc(string midvar) {
		for (int i = 0; i < 8; i++) {
			if (treg2mvar[i] == midvar)
				return;
		}
		if (treg < 8)
			treg2mvar[treg++] = midvar;
	}
	void sreg_alloc(string var){
		if (sreg < 8)
			sreg2var[sreg++] = var;
	}

};

class flush_graph {
public:
	string function;
	block blocks[BLOCKMAX];
	//block ENDBLOCK;
	int blocknum;
	flush_graph() {	function = ""; blocknum = 0; }
	void def_use_cal(int blkno, int mcno);
	void in_out_cal();
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


void flush_graph::def_use_cal(int blkno, int mcno) {
#define var2idx(x) symtabs[GTAB.ele(function)->addr].index(x)
#define ISCALOP(x) ((x==ADD)||(x==SUB)||(x==MUL)||(x==DIV))
#define ISCONDITION(x) ((x==EQL)||(x==NEQ)||(x==GTR)||(x==LES)||(x==GEQ)||(x==LEQ))
#define SETDEFUSE(part,des) do{\
		if(midcodes[mcno].##part## != "" && !ISGLOBAL(midcodes[mcno].##part##) && !ISLCONST(midcodes[mcno].##part##)){\
		if (ISMIDVAR(midcodes[mcno].##part##))blocks[blkno].treg_alloc(midcodes[mcno].##part##);\
		else if (blocks[blkno].vars.find(midcodes[mcno].##part##) == blocks[blkno].vars.end()) {\
			blocks[blkno].vars.insert(midcodes[mcno].##part##);\
			blocks[blkno].##des##[var2idx(midcodes[mcno].##part##)] = true;\
		}}\
		}while(0)

	qtnry_operator oper;
	oper = midcodes[mcno].op;
	if (ISCALOP(oper)) {
		SETDEFUSE(result, def);
		SETDEFUSE(op1, use);
		SETDEFUSE(op2, use);
	}
	else if (oper == BECOME || oper == NEG) {
		SETDEFUSE(result, def);
		SETDEFUSE(op1, use);
	}
	else if (ISCONDITION(oper)) {
		SETDEFUSE(op1, use);
		SETDEFUSE(op2, use);
	}
	else if (oper == RET || oper == SCAN || oper == SCANC) {
		SETDEFUSE(op1, def);
	}
	else if (oper == PRINT) {
		SETDEFUSE(op1, use);
	}
	else if (oper == ARYL) {
		SETDEFUSE(result, def);
		SETDEFUSE(op2, use);
	}
	else if (oper == ARYS) {
		SETDEFUSE(op1, use);
		SETDEFUSE(op2, use);
	}

}

int flush_graph::gen_block(int pos, int preblk) {
	int i, curblk;
	//如果已经建立起了块
	if (pos2blk.find(pos) != pos2blk.end()) {
		blocks[pos2blk[pos]].addpre(preblk);
		return pos2blk[pos];
	}
	//入口
	if (preblk == NONBLK) {
		blocks[0].entrance = pos;
		blocks[0].exit = pos;
		blocks[0].next1 = 1;
		blocks[0].next2 = NONBLK;
		blocknum++;
		gen_block(pos + 1, 0);
		return 0;
	}
	//出口
	if (pos == -1) {
		pos2blk[pos] = blocknum;
		blocks[blocknum].entrance = -1;
		blocks[blocknum].exit = -1;
		blocks[blocknum].next1 = NONBLK;
		blocks[blocknum].next2 = NONBLK;
		return blocknum++;
	}
	curblk = blocknum;
	blocknum++;
	blocks[curblk].entrance = pos;
	blocks[curblk].addpre(preblk);
	pos2blk[pos] = curblk;//pos一定是entrance，会导致for循环无法执行
	def_use_cal(curblk, pos);
	for (i = pos + 1; !is_entrance(i); i++) {
		pos2blk[i] = curblk;
		def_use_cal(curblk, i);
	}
	blocks[curblk].exit = i - 1;//
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

bool is_set_equal(bool* a, bool* b) {
	for (int i = 0; i < TAB_MAX; i++) {
		if (a[i] != b[i]) {
			return false;
		}
	}
	return true;
}
void set_diff(bool* a, bool* b, bool* result) {
	for (int i = 0; i < TAB_MAX; i++) {
		if (a[i] && b[i])
			result[i] = false;
		else result[i] = a[i];
	}
}
void set_union(bool* a, bool* b, bool* result) {
	for (int i = 0; i < TAB_MAX; i++) {
		result[i] = a[i] || b[i];
	}
}
void set_copy(bool* dst, bool* src) {
	for (int i = 0; i < TAB_MAX; i++) {
		dst[i] = src[i];
	}
}
void flush_graph::in_out_cal() {
	bool temp[TAB_MAX], flag = true, con;
	int i;
	while (flag) {
		flag = false;
		for (i = 0; i < blocknum; i++) {
			if (blocks[i].next2 != NONBLK) {
				set_union(blocks[blocks[i].next1].in, blocks[blocks[i].next2].in, blocks[i].out);
			}
			else if (blocks[i].next1 != NONBLK) {
				set_copy(blocks[i].out, blocks[blocks[i].next1].in);
			}
			set_diff(blocks[i].out, blocks[i].def, temp);
			set_union(temp, blocks[i].use, temp);
			if (!is_set_equal(temp, blocks[i].in)) {
				flag = true;
				set_copy(blocks[i].in, temp);
			}
		}
	}
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
	for (int i = 0; i < qtnry_num; i++) {
		if (midcodes[i].op == SET && IS_FUN_LABEL(midcodes[i].op1)) {
			graphs[graph_ptr].function = midcodes[i].op1;
			graphs[graph_ptr].gen_block(i, NONBLK);
			graphs[graph_ptr].in_out_cal();
			graph_ptr++;
		}
	}
	return;
	


}

void analyse_main() {
	init_block();

	return;
}