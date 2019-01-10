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

map<char, symbol> sps;//单字
map<string, symbol> ksy;//关键字符号映射
set<string> key;//关键字
vector<string> const_strings;//常量字符串

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
#define DEFAULT_INPUT 0
	if (DEFAULT_INPUT) {
		char f_name[100] = { 0 };
		cin >> f_name;
		input_f.open(f_name, ios::in);
		if (input_f.is_open() == false) {
			cout << "Not a valid filename!" << endl;
			return 0;
		}
	}
	else {
		char f_name[100] = "sdy.txt";
		input_f.open(f_name, ios::in);
		if (input_f.is_open() == false) {
			cout << "Not a valid filename!" << endl;
			return 0;
		}
	}
	
	fstream midcode_file("midcode.txt", ios::out | ios::trunc);
	fstream midcode_file_opt("midcode_opt.txt", ios::out | ios::trunc);
	fstream mips_file("mips.asm", ios::out | ios::trunc);
	fstream mips_file_opt("mips_opt.asm", ios::out | ios::trunc);
	init();
	init_midcode();
	lexical_init();
	program();
	if (ERROR_HAPPENED) {
		cout << endl << "Program terminates without code generation." << endl;
		return 0;
	}
	print_midcode(midcode_file);
	block_front_optimize();
	analyse_main();
	block_behind_optimize();
	print_midcode(midcode_file_opt);
	mips_main();
	print_mipscode(mips_file);
	mips_optimize();
	print_mipscode(mips_file_opt);
	midcode_file.close();
	midcode_file_opt.close();
	mips_file.close();
	mips_file_opt.close();
	return 0; 

}
