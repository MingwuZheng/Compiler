#include "compiler.h"

class quaternary {
public:
	qtnry_operator op;
	string op1;
	string op2;
	string result;
	quaternary() {op1 = "";op2 = "";op = SET;}
	void set(qtnry_operator op,string op1,string op2, string result) {
		this->op = op;
		this->op1 = op1;
		this->op2 = op2;
		this->result = result;
	}
	void print(fstream &midcode_file) {
		/////////////////
	}
};

int qtnry_ptr = 0;
int tempnum = 1;
int labelnum = 1;
quaternary midcodes[QTNRY_MAX];

string gentempvar() {
	return "t" + to_string(tempnum++);
}
string genlabel() {
	return "label" + to_string(labelnum++);
}


bool needtemp(qtnry_operator op) {
	if (op == ADD || op == SUB || op == MUL || op == DIV || op == NEG || \
		op == EQL || op == GTR || op == LES || op == CALL || op == ARYL || op == NEQ || op == GEQ || op == LEQ)
		return true;
	return false;
}
bool needlabel(qtnry_operator op) {
	if (op == BZ || op == BNZ || op == GOTO || op == SET)
		return true;
	return false;
}
void emit(qtnry_operator op, string op1, string op2, string result, string* temp) {
	if (needtemp(op) && result == "") {
		if (temp)
			*temp = gentempvar();
		midcodes[qtnry_ptr].set(op, op1, op2, *temp);
	}
	else if (needlabel(op) && op1 == "") {
		if (temp)
			*temp = genlabel();
		midcodes[qtnry_ptr].set(op, *temp, op2, result);
	}
	else midcodes[qtnry_ptr].set(op, op1, op2, result);
	qtnry_ptr++;
}

void print_midcode(fstream &midcode_file) {
	for (int i = 0; i < qtnry_ptr; i++) {
		midcodes[i].print(midcode_file);
	}
}

void init_midcode() {
	emit(GOTO, "main", "", "", NULL);
}