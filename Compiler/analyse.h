#pragma once
#define BLOCKMAX 200
#define NONBLK -1
#define IS_FUN_LABEL(x) (x[0] != '$')
#define ISMIDVAR(x) (x[0] == '#')
#define MID2NUM(x) (stoi(x.erase(0)))
#define ISGLOBAL(x) (GTAB.ele(x) != NULL)
#define ISLCONST(x) (x[0] == '\'' || (((x[0] >= '0') && (x[0] <= '9')) || x[0] == '+' || x[0] == '-'))
#define var2idx(x) symtabs[GTAB.ele(function)->addr].index(x)
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

	/*
	string sreg2var[8];
	string treg2mvar[8];
	int treg;
	int sreg;
	*/

	block() {
		entrance = -1;
		next1 = NONBLK;
		next2 = NONBLK;
		prenum = 0;
		//treg = 0;
		//sreg = 0;
		for (int i = 0; i < TAB_MAX; i++) {
			use[i] = false;
			def[i] = false;
			in[i] = false;
			out[i] = false;
		}
		/*
		for (int i = 0; i < 8; i++) {
			sreg2var[i] = "";
			treg2mvar[i] = "";
		}
		*/
	}
	void addpre(int ptr) {
		pres[prenum] = ptr;
		prenum++;
	}
	/*
	void treg_alloc(string midvar) {
		for (int i = 0; i < 8; i++) {
			if (treg2mvar[i] == midvar)
				return;
		}
		if (treg < 8)
			treg2mvar[treg++] = midvar;
	}
	void sreg_alloc(string var) {
		if (sreg < 8)
			sreg2var[sreg++] = var;
	}
	*/

};

class flush_graph {
public:
	string function;
	block blocks[BLOCKMAX];
	//block ENDBLOCK;
	int blocknum;
	flush_graph() {
		function = ""; blocknum = 0; gvarnum = 0; alloced_sreg = 0;
		for (int i = 0; i < 8; i++) 
			sreg2var[i] = "";
	}
	void def_use_cal(int blkno, int mcno);
	void in_out_cal();
	int gen_block(int, int);
	set<string>global_var;
	int gvarnum;
	int alloced_sreg;
	void global_var_cal();
	string sreg2var[8];
	void alloc_sreg(string name) {
		for (int i = 0; i < alloced_sreg; i++) {
			if (sreg2var[i] == name)
				return;
		}
		if (alloced_sreg < 8)
			sreg2var[alloced_sreg++] = name;
	}
	int gvar2sreg(string gvar) {
		for (int i = 0; i < 8; i++) {
			if (sreg2var[i] == gvar)
				return i;
		}
		return - 1;
	}


};

extern flush_graph graphs[];
void init_block();
void analyse_main();