#include "compiler.h"
#include "midcode.h"
#include "mips.h"
#include "analyse.h"


vector<quaternary>mcs;

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


void const_propagation(int graph_, int block_) {
#define cur_blk graphs[graph_].blocks[block_]



}


void block_behind_optimize() {
	mcs.clear();
	for (int i = 0; i < qtnry_ptr; i++)
		mcs.push_back(midcodes[i]);


	for (int i = 0; i < graph_ptr; i++) {
		for (int j = 0; j < graphs[graph_ptr].blocknum; j++)
			dag_optimize(i, j);
	}

	for (int i = 0; i < graph_ptr; i++) {
		for (int j = 0; j < graphs[graph_ptr].blocknum; j++)
			const_propagation(i, j);
	}

	qtnry_ptr = mcs.size();
	for (int i = 0; i < qtnry_ptr; i++)
		midcodes[i] = mcs[i];
}