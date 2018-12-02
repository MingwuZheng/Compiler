#include "compiler.h"

map<qtnry_operator, string> op_print;

void quaternary::print(fstream &midcode_file) {
	midcode_file << op_print[this->op] << " " << this->op1 << " " << this->op2 << " " << this->result << endl;
}
int qtnry_ptr = 0;
int tempnum = 1;
int labelnum = 1;
quaternary midcodes[QTNRY_MAX];
string gentempvar() {
	return "#" + to_string(tempnum++);
}
string genlabel() {
	return "$LABEL" + to_string(labelnum++);
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
	if (op == ENTER)
		tempnum = 1;
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
void print_midcode() {
	fstream midcode_file("midcode.txt");
	for (int i = 0; i < qtnry_ptr; i++)
		midcodes[i].print(midcode_file);
}

void init_midcode()
{
	op_print[RET] = "RET";
	op_print[PUSH] = "PUSH";
	op_print[CALL] = "CALL";
	op_print[EXIT] = "EXIT";
	op_print[ENTER] = "ENTER";
	op_print[SET] = "SET";
	op_print[GOTO] = "GOTO";
	op_print[BNZ] = "BNZ";
	op_print[BZ] = "BZ";
	op_print[ADD] = "ADD";
	op_print[SUB] = "SUB";
	op_print[MUL] = "MUL";
	op_print[DIV] = "DIV";
	op_print[NEG] = "NEG";
	op_print[EQL] = "EQL";
	op_print[NEQ] = "NEQ";
	op_print[GTR] = "GTR";
	op_print[LES] = "LES";
	op_print[GEQ] = "GEQ";
	op_print[LEQ] = "LEQ";
	op_print[BECOME] = "BECOME";
	op_print[PRINT] = "PRINT";
	op_print[SCAN] = "SCAN";
	op_print[PRINTS] = "PRINTS";
	op_print[PRINTC] = "PRINTC";
	op_print[ARYL] = "ARYL";
	op_print[ARYS] = "ARYS";
	op_print[SCANC] = "SCANC";
	//emit(GOTO, "main", "", "", NULL);
}

