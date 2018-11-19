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
quaternary midcodes[QTNRY_MAX];

string gentempvar() {
	return "t" + to_string(tempnum++);
}

void init_midcode() {
	emit(GOTO, "main", "", "", NULL);
}

bool needtemp(qtnry_operator op) {
	if (op == ADD || op == SUB || op == MUL || op == DIV || op == EQL || op == GRT || op == LES || op == CALL)
		return true;
	return false;
}

void emit(qtnry_operator op, string op1, string op2, string result, string* temp) {
	if (needtemp(op) && result == "") {
		*temp = gentempvar();
		midcodes[qtnry_ptr].set(op, op1, op2, *temp);
	}
	else midcodes[qtnry_ptr].set(op, op1, op2, result);
	qtnry_ptr++;
}

void print_midcode(fstream &midcode_file) {
	for (int i = 0; i < qtnry_ptr; i++) {
		midcodes[i].print(midcode_file);
	}

}