#pragma once
#define BLOCKMAX 2000
#define SREG_NUM 8

#define NONBLK -1
#define IS_FUN_LABEL(x) (x[0] != '$')
#define ISMIDVAR(x) (x[0] == '#')
#define MID2NUM(x) (stoi(x.erase(0)))
#define ISGLOBAL(x) (GTAB.ele(x) != NULL)
#define ISLCONST(x) (x[0] == '\'' || (((x[0] >= '0') && (x[0] <= '9')) || x[0] == '+' || x[0] == '-'))
#define var2idx(x) symtabs[GTAB.ele(function)->addr].index(x) //function是flush_graph类的成员
class block {
public:
	int entrance;
	int exit;
	int next1;
	int next2;

	int prenum;
	int pres[BLOCKMAX];

	vector<string> vars;
	bool use[TAB_MAX];
	bool def[TAB_MAX];

	bool in[TAB_MAX];
	bool out[TAB_MAX];

	block() {
		entrance = -1;
		next1 = NONBLK;
		next2 = NONBLK;
		prenum = 0;
		for (int i = 0; i < TAB_MAX; i++) {
			use[i] = false;
			def[i] = false;
			in[i] = false;
			out[i] = false;
		}
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
	flush_graph() {
		function = ""; blocknum = 0; gvarnum = 0;
	}
	int gen_block(int, int);

	set<string>global_var;
	int gvarnum;
	void def_use_cal(int blkno, int mcno);
	void in_out_cal();
	void global_var_cal();
	//string sreg2var[SREG_NUM];
	map<string, int>var2sreg;//只包含块全局变量
	//int alloced_sreg;
	/*void alloc_sreg(string name, int sregnum) {
		var2sreg[name] = sregnum;
	}*/
	bool alloced(int sregnum) {
		map<string, int>::iterator iter = var2sreg.begin();
		while (iter != var2sreg.end()) {
			if (iter->second == sregnum)
				return true;
			iter++;
		}
		return false;
	}
	int gvar2sreg(string gvar) {
		return var2sreg[gvar];
	}
};

extern flush_graph graphs[];
extern int graph_ptr;
void init_block();
void analyse_main();