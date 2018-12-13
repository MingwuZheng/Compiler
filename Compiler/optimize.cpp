#include "compiler.h"
#include "midcode.h"

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
	delete_unnecessary_jump();

	for (int i = 0; i < (tmcnum > qtnry_ptr ? tmcnum : qtnry_ptr); i++)
		midcodes[i] = tempmcs[i];
}

void init_midcode_optimize() {
	tmcnum = qtnry_ptr;
	for (int i = 0; i < tmcnum; i++)
		tempmcs[i] = midcodes[i];
	


	
	return;
}