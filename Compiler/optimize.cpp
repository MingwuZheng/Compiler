#include "compiler.h"
#include "midcode.h"
#include "mips.h"
#include "analyse.h"


quaternary tempmcs[QTNRY_MAX];
int tmcnum;

void delete_mc(int pos) {
	for (int i = pos; i < tmcnum - 1; i++)
		tempmcs[i] = tempmcs[i + 1];
	tmcnum--;
}

void insert_mc(int pos, quaternary* mc) {
	for (int i = tmcnum; i != pos; i--)
		tempmcs[i] = tempmcs[i - 1];
	tempmcs[pos] = *mc;
	tmcnum++;
}

void delete_unnecessary_jump() {
	for (int i = 0; i < tmcnum; i++) {
		if (tempmcs[i].op == GOTO) {
			int jpos = i;
			string taget_label = tempmcs[jpos].op1;
			i++;
			while (tempmcs[i].op == SET) {
				if (tempmcs[i].op1 == taget_label) {
					delete_mc(jpos);
					break;
				}
				i++;
			}
			i--;
		}
	}
}

void block_front_optimize() {
	tmcnum = qtnry_ptr;
	for (int i = 0; i < tmcnum; i++)
		tempmcs[i] = midcodes[i];
	//here are methods
	delete_unnecessary_jump();

	//
	qtnry_ptr = tmcnum;
	for (int i = 0; i < tmcnum; i++)
		midcodes[i] = tempmcs[i];
}

int filled_mc = 0;
void dag_optimize(int graph_,int block_) {
#define cur_blk graphs[graph_].blocks[block_]




}

void block_behind_optimize() {

	for (int i = 0; i < graph_ptr; i++) {
		for (int j = 0; j < graphs[graph_ptr].blocknum; j++)
			dag_optimize(i, j);
	}

	qtnry_ptr = filled_mc;
	for (int i = 0; i < filled_mc; i++)
		midcodes[i] = tempmcs[i];
}