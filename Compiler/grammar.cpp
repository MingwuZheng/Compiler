#include "compiler.h"
#include "error.h"
#include "lexical.h"
#include "grammar.h"

#define ISVALTYPE(x) (x == INTSY || x == CHARSY)
#define ISFUNCTYPE(x) (x == INTSY || x == CHARSY || x == VOIDSY)
#define TP(x) (x == INTSY) ? INT : ((x == VOIDSY) ? VOID : CHAR)

void program() {
	bool func = false, hasmain = false;
	symbol tp;
	string temp;
	if (sy == CONSTSY)
		constdec();
	while (ISVALTYPE(sy)) {//在同一类型中
		tp = sy;
		insymbol();
		if (sy == IDENT) {
			temp = id;
			insymbol();
			if (sy == LPT) {
				insymbol();
				func = true;
				break;
			}
			if (sy == LBK) {//数组声明
				insymbol();
				if (sy == INTCON && num > 0) {
					GTAB.insert(id, ARRAY, TP(tp), 0, num * 4, GTAB.filledsize);
				}
				else error(ILLEGAL_ARRLEN_ERROR);
				insymbol();
				if (sy == RBK) {
					insymbol();
				}
				else error(EXPECT_RBK_ERROR);
			}//单个数组声明结束
			else {//单个标识符
				GTAB.insert(id, VAR, TP(tp), 0, 4, GTAB.filledsize);
			}
			while (sy == COMMA) {
				insymbol();
				if (sy = IDENT) {
					if (sy == LBK) {//数组声明
						insymbol();
						if (sy == INTCON && num > 0) {
							GTAB.insert(id, ARRAY, TP(tp), 0, num * 4, GTAB.filledsize);
						}
						else error(ILLEGAL_ARRLEN_ERROR);
						insymbol();
						if (sy == RBK) {
							insymbol();
						}
						else error(EXPECT_RBK_ERROR);
					}//单个数组声明结束
					else {//单个标识符
						GTAB.insert(id, VAR, TP(tp), 0, 4, GTAB.filledsize);
					}
				}
				else error(EXPECT_ID_ERROR);
			}
			if (sy == SEMICOLON) {
				insymbol();
				continue;
			}
			else error(EXPECT_SEMI_ERROR);
		}//if(sy == IDENT)
		else error(EXPECT_ID_ERROR);
	}
	if (func) {
		int paranum;
		paranum = paralist();
		if (sy == RPT) {
			insymbol();
			if (sy != LBR)
				error(EXPECT_LBR_ERROR);
			compoundstatement();
			if (sy != RBR)
				error(EXPECT_RBR_ERROR);
		}
		else error(EXPECT_RPT_ERROR);
		GTAB.insert(temp, FUNCTION, TP(tp), paranum, symtabs[tabptr].filledsize + paranum * 4, tabptr);
		insymbol();
	}
	while (ISFUNCTYPE(sy)) {
		tp = sy;
		insymbol();
		if (sy == IDENT) {
			insymbol();
			if (sy == LPT) {
				insymbol();
				int paranum = paralist();
				if (sy == RPT) {
					insymbol();
					//////////////////////////////////test-skip
					if (sy == LBR) {
						insymbol();
						compoundstatement();
						if (sy == RBR) {
							GTAB.insert(id, FUNCTION, TP(tp), paranum, symtabs[tabptr].filledsize + paranum * 4, tabptr);
							insymbol();
						}
						else error(EXPECT_RBR_ERROR);
					}
					else {
						////////////////////////////
						error(EXPECT_LBR_ERROR);
						///////////////////////////
					}
				}
				else error(EXPECT_RPT_ERROR);
			}
			else error(EXPECT_LPT_ERROR);
		}
		else {
			if (sy == MAIN) {
				if (TP(tp) == VOID) {
					hasmain = true;
					insymbol();
					if (sy == LPT) {
						insymbol();
						if (sy == RPT) {
							insymbol();
							//////////////////////////////////test-skip
							if (sy == LBR) {
								insymbol();
								compoundstatement();
								if (sy == RBR) {
									GTAB.insert("main", FUNCTION, VOID, 0, symtabs[tabptr].filledsize, tabptr);
									return;
								}
								else error(EXPECT_RBR_ERROR);
							}
							else {
								////////////////////////////
								error(EXPECT_LBR_ERROR);
								///////////////////////////
							}
						}
						else error(EXPECT_RPT_ERROR);
					}
					else error(EXPECT_LPT_ERROR);
				}
				else error(REDEFINED_VAR_ERROR);
			}
			else error(EXPECT_ID_ERROR);
		}
	}
}



