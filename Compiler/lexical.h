#pragma once

extern int lc;
extern int cc;
extern char ch;
extern long int num;
extern int lp;
extern char chr;
extern int tabptr;
extern string id;
extern string str;
extern symbol sy;

void nextline();
void insymbol();
void lexical_init();
int lexical_main();