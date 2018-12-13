#include "compiler.h"
#include "init.h"
#include "lexical.h"
#include "error.h"
#include "grammar.h"
#include "midcode.h"
#include "analyse.h"
#include "mips.h"
#include "optimize.h"

fstream input_f;
bool ENABLE_EOF = false;
int lc = 1;
int cc = 1;
char ch;
long int num;//�������ͳ���
int lp;
char chr;//�����ַ�����
int tabptr = 1;
string id;
string str;
symbol sy;
map<char, symbol> sps;//����
map<string, symbol> ksy;//�ؼ��ַ���ӳ��
set<string> key;//�ؼ���
vector<string> const_strings;//�����ַ���

void symTab::insert(string name, idType idtype, symType symtype, int var, int size, int addr) {
	for (int i = 0; i < ptr;i++) {
		if (symbols[i].name == name) {
			error(REDEFINED_VAR_ERROR);
			return;
		}
	}
	symbols[ptr].name = name;
	symbols[ptr].idtype = idtype;
	symbols[ptr].symtype = symtype;
	symbols[ptr].var = var;
	symbols[ptr].addr = addr;
	if (ptr == TAB_MAX - 1)
		error(SYMTAB_OVERFLOW_ERROR);
	ptr++;
	filledsize += size;
}
symbolEle * symTab::ele(int x) {
	return &symbols[x];
}
symbolEle * symTab::ele(string x) {
	for (int i = 0; i < ptr; i++) {
		if (symbols[i].name == x)
			return &symbols[i];
	}
	return NULL;
}
int symTab::index(string x) {
	for (int i = 0; i < ptr; i++) {
		if (symbols[i].name == x)
			return i;
	}
	return -1;
}
symTab symtabs[TAB_MAX];



int main() {


	
	char f_name[100] = { 0 };
	cin >> f_name;
	input_f.open(f_name, ios::in);
	if (input_f.is_open() == false) {
		cout << "Not a valid filename!" << endl;
		return 0;
	}
	
	/*
	char f_name[100] = "sdy.txt";
	input_f.open(f_name, ios::in);
	if (input_f.is_open() == false) {
		cout << "Not a valid filename!" << endl;
		return 0;
	}
	
	*/


	init();
	init_midcode();
	lexical_init();
	program();
	print_midcode();
	midcode_optimize();
	analyse_main();
	mips_main();
	return 0;

}
