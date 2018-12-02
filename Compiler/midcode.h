#pragma once
extern int qtnry_ptr;
extern map<string, int> func_midvars;
void emit(qtnry_operator op, string op1, string op2, string result, string* temp);
void init_midcode();
void print_midcode();