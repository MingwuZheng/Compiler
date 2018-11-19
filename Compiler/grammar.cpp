#include "compiler.h"
#include "error.h"
#include "lexical.h"
#include "grammar.h"
#include "midcode.h"

#define ISVALTYPE(x) (x == INTSY || x == CHARSY)
#define ISFUNCTYPE(x) (x == INTSY || x == CHARSY || x == VOIDSY)
#define TP(x) ((x == INTSY) ? INT : ((x == VOIDSY) ? VOID : CHAR))
#define UNMATCH(x,y) ((x == INTSY && y == CHARCON)||(x == CHARSY && y == INTCON))

void program() {
	bool func = false, hasmain = false;
	symbol tp;
	string temp;
	if (sy == CONSTSY) {
		tabptr = 0;//保持代码一致性，暂令tabptr=0
		constdec();
		tabptr = 1;
	}
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
					GTAB.insert(id, ARRAY, TP(tp), num, num * 4, GTAB.filledsize);
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
							GTAB.insert(id, ARRAY, TP(tp), num, num * 4, GTAB.filledsize);
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
		//注册函数
		CTAB.glbpos = GTAB.ptr;
		GTAB.insert(temp, FUNCTION, TP(tp), paralist(), 0, tabptr);//函数的size填0，因为局部符号表有记录
		if (sy == RPT) {
			insymbol();
			if (sy != LBR)
				error(EXPECT_LBR_ERROR);
			else insymbol();
			emit(SET, temp, "", "", NULL);
			emit(ENTER, "", "", "", NULL);
			compoundstatement();
			emit(EXIT, "", "", "", NULL);
			if (sy != RBR)
				error(EXPECT_RBR_ERROR);
			else { 
				tabptr++;//进入下一个函数前为其分配空间
				insymbol(); 
			}
		}
		else error(EXPECT_RPT_ERROR);

		//GTAB.insert(temp, FUNCTION, TP(tp), paranum, symtabs[tabptr].filledsize + paranum * 4, tabptr);
		
	}
	while (ISFUNCTYPE(sy)) {
		tp = sy;
		insymbol();
		if (sy == IDENT) {
			temp = id;
			insymbol();
			if (sy == LPT) {
				insymbol();
				CTAB.glbpos = GTAB.ptr;
				GTAB.insert(temp, FUNCTION, TP(tp), paralist(), 0, tabptr);
				if (sy == RPT) {
					insymbol();
					//////////////////////////////////test-skip
					if (sy == LBR) {
						insymbol();
						emit(SET, temp, "", "", NULL);
						emit(ENTER, "", "", "", NULL);
						compoundstatement();
						emit(EXIT, "", "", "", NULL);
						if (sy == RBR) {
							tabptr++;
							insymbol();
						}
						else error(EXPECT_RBR_ERROR);
					}
					else error(EXPECT_LBR_ERROR);
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
						GTAB.insert("main", FUNCTION, VOID, 0, 0, tabptr);
						if (sy == RPT) {
							insymbol();
							//////////////////////////////////test-skip
							if (sy == LBR) {
								insymbol();
								emit(SET, "main", "", "", NULL);
								emit(ENTER, "", "", "", NULL);
								compoundstatement();
								emit(EXIT, "", "", "", NULL);
								if (sy == RBR) {
									tabptr++;//应当最后一增，无实际意义
									return;
								}
								else error(EXPECT_RBR_ERROR);
							}
							else error(EXPECT_LBR_ERROR);
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

void constdec() {
	symbol tp;
	while (sy == CONSTSY) {
		insymbol();
		if (ISVALTYPE(sy)) {
			tp = sy;
			insymbol();
			if (sy == IDENT) {//read first const
				insymbol();
				if (sy == BECOMESY) {
					insymbol();
					if (UNMATCH(tp, sy))
						error(TYPE_CONFLICT_ERROR);
					CTAB.insert(id, CONST, TP(tp), (tp == CHARSY) ? chr : num, 4, CTAB.filledsize);//如果在函数内常量定义，偏移要减去参数空间
					insymbol();
				}
				else error(ILLEGAL_VARDEF_ERROR);
			}
			else error(EXPECT_ID_ERROR);
			while (sy == COMMA) {//rapidly read same-type const
				insymbol();
				if (sy == IDENT) {//read first const
					insymbol();
					if (sy == BECOMESY) {
						insymbol();
						if (UNMATCH(tp, sy))
							error(TYPE_CONFLICT_ERROR);
						CTAB.insert(id, CONST, TP(tp), (tp == CHARSY) ? chr : num, 4, CTAB.filledsize);
						insymbol();
					}
					else error(ILLEGAL_VARDEF_ERROR);
				}
				else error(EXPECT_ID_ERROR);
			}
			if (sy != SEMICOLON)
				error(EXPECT_SEMI_ERROR);
			else insymbol();//normal exit
		}
		else error(EXPECT_TYPE_ERROR);
	}
}

void vardec() {
	symbol tp;
	while (ISVALTYPE(sy)) {//在同一类型中
		tp = sy;
		insymbol();
		if (sy == IDENT) {
			insymbol();
			if (sy == LBK) {//数组声明
				insymbol();
				if (sy == INTCON && num > 0) {
					CTAB.insert(id, ARRAY, TP(tp), num, num * 4, CTAB.filledsize);
				}
				else error(ILLEGAL_ARRLEN_ERROR);
				insymbol();
				if (sy == RBK) {
					insymbol();
				}
				else error(EXPECT_RBK_ERROR);
			}//单个数组声明结束
			else {//单个标识符
				CTAB.insert(id, VAR, TP(tp), 0, 4, CTAB.filledsize);
			}
			while (sy == COMMA) {
				insymbol();
				if (sy = IDENT) {
					if (sy == LBK) {//数组声明
						insymbol();
						if (sy == INTCON && num > 0) {
							CTAB.insert(id, ARRAY, TP(tp), num, num * 4, CTAB.filledsize);
						}
						else error(ILLEGAL_ARRLEN_ERROR);
						insymbol();
						if (sy == RBK) {
							insymbol();
						}
						else error(EXPECT_RBK_ERROR);
					}//单个数组声明结束
					else {//单个标识符
						CTAB.insert(id, VAR, TP(tp), 0, 4, CTAB.filledsize);
					}
				}
				else error(EXPECT_ID_ERROR);
			}
			if (sy == SEMICOLON) {
				insymbol();//normal exit
				continue;
			}
			else error(EXPECT_SEMI_ERROR);
		}//if(sy == IDENT)
		else error(EXPECT_ID_ERROR);
	}
}

int paralist() {
	int pnum = 0;
	symbol tp;
	if (sy == RPT)
		return 0;
	if (ISVALTYPE(sy)) {
		tp = sy;
		insymbol();
		if (sy == IDENT) {
			pnum++;
			//先不在全部符号表里插参数了/////
			CTAB.insert(id, PARA, TP(tp), 0, 4, CTAB.filledsize);
			insymbol();
		}
		else error(ILLEGAL_PARALIST_ERROR);
	}
	else error(ILLEGAL_PARALIST_ERROR);
	while (sy == COMMA) {
		insymbol();
		if (ISVALTYPE(sy)) {
			tp = sy;
			insymbol();
			if (sy == IDENT) {
				pnum++;
				CTAB.insert(id, PARA, TP(tp), 0, 4, CTAB.filledsize);
				insymbol();
			}
			else error(ILLEGAL_PARALIST_ERROR);
		}
		else error(ILLEGAL_PARALIST_ERROR);
	}
	return pnum;
}

void compoundstatement() {
	if (sy == CONSTSY)
		constdec();
	if (ISVALTYPE(sy))
		vardec();
	if (sy == RBR)
		return;
	while (sy != RBR) {
		statement();
	}
}

void statement() {
	switch (sy){
		case IDENT: {//赋值语句、函数调用语句、
			if (GTAB.ele(id) != NULL && GTAB.ele(id)->idtype == FUNCTION)
				call(GTAB.index(id));
			else assignment();
			if (sy != SEMICOLON)
				error(EXPECT_SEMI_ERROR);
			else insymbol();
			break;
		}
		case LBR: {//语句列
			insymbol();
			while (sy != RBR)
				statement();
			insymbol();
			break;
		}
		case SEMICOLON: {//空语句
			insymbol();
			break;
		}
		case IFSY: {
			ifstatement();
			break;
		}
		case FORSY: {
			forstatement();
			break;
		}
		case DOSY: {
			whilestatement();
			break;
		}
		case RETURN: {
			if (sy == LPT) {
				if (GTAB.ele(CTAB.glbpos)->symtype == VOID)
					error(TYPE_CONFLICT_ERROR);
				insymbol();
				emit(RET, expression(), "", "", NULL);
				if (sy == RPT)
					insymbol();
				else error(EXPECT_RPT_ERROR);
			}
			if (sy != SEMICOLON)
				error(EXPECT_SEMI_ERROR);
			else insymbol();
			break;
		}
		case PRINTSY: {
			printstatement();
			if (sy != SEMICOLON)
				error(EXPECT_SEMI_ERROR);
			else insymbol();
			break;
		}
		case SCANSY: {
			scanstatement();
			if (sy != SEMICOLON)
				error(EXPECT_SEMI_ERROR);
			else insymbol();
			break;
		}
		default: {error(ILLEGAL_STATE_ERROR); break; }
	}
}

string call(int pos) {//优化时注意，有返回值函数调用单列一句话可能会多出无意义中间返回值变量
	string name = id;
	string returnvar;
	int paranum = 0;
	insymbol();
	if (sy == LPT) {
		insymbol();
		if (sy == RPT) {
			if (GTAB.ele(pos)->var != 0)
				error(ILLEGAL_PARALIST_ERROR);
			insymbol();
		}
		else {
			emit(PUSH, expression(), "", "", nullptr);
			paranum++;
			while (sy == COMMA) {
				emit(PUSH, expression(), "", "", nullptr);
				paranum++;
			}
			if (paranum != GTAB.ele(pos)->var)
				error(ILLEGAL_PARALIST_ERROR);
			if (sy != RPT)
				error(EXPECT_RPT_ERROR);
			else insymbol();
		}
		emit(CALL, name, "", "", &returnvar);
		return returnvar;
	}
	else error(EXPECT_LPT_ERROR);
}



void ifstatement() {

}
void whilestatement() {

}
void forstatement() {

}
void scanstatement() {

}
void printstatement() {

}
void assignment() {

}



string factor() {//＜因子＞::= ＜标识符＞｜＜标识符＞'['＜表达式＞']'｜＜整数＞|＜字符＞｜＜有返回值函数调用语句＞ | '('＜表达式＞')'
	string result;
	switch (sy) {
		case INTCON: {
			int n = num;
			insymbol();
			return to_string(n);
			break;
		}
		case CHARCON: {
			int n = chr;
			insymbol;
			return to_string(n);
			break;
		}
		case IDENT: {
			if (GTAB.ele(id)->idtype == FUNCTION) {
				if (GTAB.ele(id)->symtype == VOID) {
					error(TYPE_CONFLICT_ERROR);
				}
				return call(GTAB.index(id));
			}
			else {
				if (CTAB.ele(id) == NULL) {
					if (GTAB.ele(id) == NULL)
						error(UNDEFINED_ID_ERROR);
					else {//标识符在全局符号表里
						int index = GTAB.index(id);
						if (GTAB.ele(index)->idtype == ARRAY) {//全局数组
							insymbol();
							if (sy == LBK) {
								insymbol();
								emit(ARYL, id, expression(), "", &result);
								if (sy = RBK)
									insymbol();
								else error(EXPECT_RBK_ERROR);
								return result;
							}
							else error(EXPECT_LBK_ERROR);
						}
						else {//全局的变量、常量
							if (GTAB.ele(index)->idtype == CONST) {//全局常量
								insymbol();
								return to_string(GTAB.ele(index)->var);//常量替换
							}
							else {//全局变量
								insymbol();
								return id;
							}
						}
					}
				}
				else {//标识符在局部符号表里
					int index = CTAB.index(id);
					if (CTAB.ele(index)->idtype == ARRAY) {//局部数组
						insymbol();
						if (sy == LBK) {
							insymbol();
							emit(ARYL, id, expression(), "", &result);
							if (sy = RBK)
								insymbol();
							else error(EXPECT_RBK_ERROR);
							return result;
						}
						else error(EXPECT_LBK_ERROR);
					}
					else {//局部的变量、常量
						if (CTAB.ele(index)->idtype == CONST) {//局部常量
							insymbol();
							return to_string(CTAB.ele(index)->var);//常量替换
						}
						else {//局部变量、参数
							insymbol();
							return id;
						}
					}
				}

			}
			break;
		}
		case PLUS: {//整数标记
			insymbol();
			if (sy == INTCON) {
				insymbol();
				return to_string(num);
			}
			else error(EXPECT_INT_RROR);
			break;
		}
		case MINUS: {//整数标记
			insymbol();
			if (sy == INTCON) {
				insymbol();
				return to_string(-num);
			}
			else error(EXPECT_INT_RROR);
			break;
		}
		case LPT: {//表达式
			insymbol();
			result = expression();
			if (sy == RPT)
				insymbol();
			else error(EXPECT_RPT_ERROR);
			return result;
			break;
		}
	}
}
string term() {//＜项＞::= ＜因子＞{＜乘法运算符＞＜因子＞}
	string mid;
	mid = factor();
	while (sy == MULSY || sy == DIVSY) {
		insymbol();
		string tmp = factor();
		emit((sy == MULSY) ? MUL : DIV, mid, tmp, "", &mid);
	}
	return mid;
}
string expression() {//＜表达式＞::= ［＋｜－］＜项＞{＜加法运算符＞＜项＞}   //[+|-]只作用于第一个<项>
	int neg = 1;
	if (sy == PLUS)
		insymbol();
	else if (sy == MINUS) {
		insymbol();
		neg = -1;
	}
	string mid;
	mid = term();
	if (neg == -1)
		emit(NEG, mid, "", "", &mid);
	while (sy == PLUS || sy == MINUS) {
		insymbol();
		string tmp = term();
		emit((sy == PLUS) ? ADD : SUB, mid, tmp, "", &mid);
	}
	return mid;
}
string condition() {
	string o1, o2, result;
	o1 = expression();
	insymbol();
	switch (sy){
		case EQLSY: {
			o2 = expression();
			emit(EQL, o1, o2, "", &result);
			break;
		}
		case NEQSY: {
			o2 = expression();
			emit(NEQ, o1, o2, "", &result);
			break;
		}
		case GTRSY: {
			o2 = expression();
			emit(GTR, o1, o2, "", &result);
			break;
		}
		case GEQSY: {
			o2 = expression();
			emit(GEQ, o1, o2, "", &result);
			break;
		}
		case LESSY: {
			o2 = expression();
			emit(LES, o1, o2, "", &result);
			break;
		}
		case LEQSY: {
			o2 = expression();
			emit(LEQ, o1, o2, "", &result);
			break;
		}
		default:{
			return o1;
			break;
		}
	}
	insymbol();
	return result;
}






