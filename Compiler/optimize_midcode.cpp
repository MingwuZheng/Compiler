#include "compiler.h"
#include "midcode.h"
#include "mips.h"
#include "analyse.h"

#define CAL_CODE(x) ((x).op == ADD || (x).op == SUB || (x).op == MUL || (x).op == DIV || (x).op == NEG || (x).op == BECOME) 

vector<quaternary>mcs;
vector<int>nmcs;
extern map<int, int>pos2blk;

void delete_unnecessary_jump() {
	vector<quaternary>::iterator i, temp;
	for (i = mcs.begin(); i != mcs.end();) {
		bool delete_goto = false;
		if ((*i).op == GOTO) {
			temp = i + 1;
			string taget_label = (*i).op1;
			while ((*temp).op == SET) {
				if ((*temp).op1 == taget_label) {
					delete_goto = true;
					break;
				}
				temp++;
			}
			if (delete_goto)
				i = mcs.erase(i);
			else i++;
		}
		else i++;
	}
}

void block_front_optimize() {
	for (int i = 0; i < qtnry_ptr; i++)
		mcs.push_back(midcodes[i]);
	//here are methods
	delete_unnecessary_jump();

	//
	qtnry_ptr = mcs.size();
	for (int i = 0; i < qtnry_ptr; i++)
		midcodes[i] = mcs[i];
}



void dag_optimize(int graph_,int block_) {
#define cur_blk graphs[graph_].blocks[block_]




}


void const_propagation() {
	/*
		RET, PUSH, CALL, EXIT, ENTER,
		SET, GOTO, BNZ, BZ,
		ADD, SUB, MUL, DIV, NEG,
		EQL, NEQ, GTR, LES, GEQ, LEQ, BECOME,
		PRINT, SCAN, PRINTS, PRINTC, SCANC,
		ARYL, ARYS
	*/
#define curblk graphs[i].blocks[j]
	for (int i = 0; i < graph_ptr; i++) {
		for (int j = 0; j < graphs[i].blocknum; j++) {
			for (int k = curblk.entrance; k <= curblk.exit; k++) {
				if (CAL_CODE(midcodes[k]) && (ISLCONST(midcodes[k].op1) || midcodes[k].op1 == "") && (ISLCONST(midcodes[k].op2) || midcodes[k].op2 == "")) {
					string cvar = midcodes[k].result;
					int res;
					switch (midcodes[k].op)
					{
					case ADD: {
						res = literal2int(midcodes[k].op1) + literal2int(midcodes[k].op2);
						break;
					}
					case SUB: {
						res = literal2int(midcodes[k].op1) - literal2int(midcodes[k].op2);
						break;
					}
					case MUL: {
						res = literal2int(midcodes[k].op1) * literal2int(midcodes[k].op2);
						break;
					}
					case DIV: {
						res = literal2int(midcodes[k].op1) / literal2int(midcodes[k].op2);
						break;
					}
					case BECOME: {
						res = literal2int(midcodes[k].op1);
						break;
					}
					case NEG: {
						res = -literal2int(midcodes[k].op1);
						break;
					}
					default:
						break;
					}
					for (int l = k + 1; l <= curblk.exit; l++) {
						//if (midcodes[l].op != MUL && midcodes[l].op != DIV) {
						if (midcodes[l].op != SCAN && midcodes[l].op != SCANC) {
							if (midcodes[l].result == cvar)
								break;
							if (midcodes[l].op1 == cvar)
								midcodes[l].op1 = to_string(res);
							if (midcodes[l].op2 == cvar)
								midcodes[l].op2 = to_string(res);
							//}
						}
					}
					if (ISMIDVAR(cvar)) 
						nmcs.push_back(k);
				}
			}
		}
	}
}

void def_decrease() {

#define curblk graphs[i].blocks[j]
#define varname(x) funcname2tab(graphs[i].function).ele(x)->name
	for (int i = 0; i < graph_ptr; i++) {
		for (int j = 0; j < graphs[i].blocknum; j++) {
			for (int k = curblk.entrance; k <= curblk.exit; k++) {
				if (CAL_CODE(midcodes[k]) && !ISMIDVAR(midcodes[k].result)) {
					string var = midcodes[k].result;
					int res;
					if (GTAB.ele(var) != NULL && symtabs[i + 1].ele(var) == NULL)
						continue;
					bool delete_def = true;
					for (int l = k+1; l <= curblk.exit; l++) {
						if (midcodes[l].op1 == var || midcodes[l].op2 == var) {
							delete_def = false;
							break;
						}
					}
					if (!delete_def)continue;
					for (int outp = 0; outp < TAB_MAX; outp++) {
						if (!curblk.out[outp] && varname(outp) == var) {
							nmcs.push_back(k);
							break;
						}
					}
				}
			}
		}
	}
}
void block_behind_optimize() {
	/*
	mcs.clear();
	for (int i = 0; i < qtnry_ptr; i++)
		mcs.push_back(midcodes[i]);
	*/

	//dag_optimize(); 
	const_propagation();
	def_decrease();
	sort(nmcs.begin(), nmcs.end());
	nmcs.erase(unique(nmcs.begin(), nmcs.end()), nmcs.end());
	for (vector<int>::reverse_iterator i = nmcs.rbegin(); i != nmcs.rend(); i++) {
		for (int j = (*i); j < qtnry_ptr - 1; j++)
			midcodes[j] = midcodes[j + 1];
		qtnry_ptr--;
	}
	/*
	qtnry_ptr = mcs.size();
	for (int i = 0; i < qtnry_ptr; i++)
		midcodes[i] = mcs[i];
	*/
}