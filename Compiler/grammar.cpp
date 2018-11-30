#include "compiler.h"
#include "error.h"
#include "lexical.h"
#include "grammar.h"
#include "midcode.h"

#define ISVALTYPE(x) (x == INTSY || x == CHARSY)
#define ISFUNCTYPE(x) (x == INTSY || x == CHARSY || x == VOIDSY)
#define TP(x) ((x == INTSY) ? INT : ((x == VOIDSY) ? VOID : CHAR))
#define UNMATCH(x,y) ((x == INTSY && y == CHARCON)||(x == CHARSY && y == INTCON))

#define ISCHAR(x) (x[0] == '\'')
#define CH2ASC(x) x = ((x[0] == '\'')?to_string((int)(x[1])):x)


void readsym(symbol expect, int errormsg) {
	if (sy == END_OF_FILE) {
		if (!ENABLE_EOF) {
			error(UNEXPECTED_EOF_ERROR);
		}
	}
	if (sy != expect)
		error(errormsg);
	else {
		insymbol();
	}
}

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
		readsym(IDENT, EXPECT_ID_ERROR);
		temp = id;
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
			readsym(RBK, EXPECT_RBK_ERROR);
		}//单个数组声明结束
		else {//单个标识符
			GTAB.insert(id, VAR, TP(tp), 0, 4, GTAB.filledsize);
		}
		while (sy == COMMA) {
			insymbol();
			readsym(IDENT, EXPECT_ID_ERROR);
			if (sy == LBK) {//数组声明
				insymbol();
				if (sy == INTCON && num > 0) {
					GTAB.insert(id, ARRAY, TP(tp), num, num * 4, GTAB.filledsize);
				}
				else error(ILLEGAL_ARRLEN_ERROR);
				insymbol();
				readsym(RBK, EXPECT_RBK_ERROR);
			}//单个数组声明结束
			else {//单个标识符
				GTAB.insert(id, VAR, TP(tp), 0, 4, GTAB.filledsize);
			}
		}
		readsym(SEMICOLON, EXPECT_SEMI_ERROR);
	}
	if (func) {
		//注册函数
		CTAB.glbpos = GTAB.ptr;
		GTAB.insert(temp, FUNCTION, TP(tp), paralist(), 0, tabptr);//函数的size填0，因为局部符号表有记录
		readsym(RPT, EXPECT_RPT_ERROR);
		readsym(LBR, EXPECT_LBR_ERROR);
		emit(SET, temp, "", "", NULL);
		emit(ENTER, "", "", "", NULL);
		compoundstatement();
		emit(EXIT, "", "", "", NULL);
		readsym(RBR, EXPECT_RBR_ERROR);
		tabptr++;//进入下一个函数前为其分配空间
				 //GTAB.insert(temp, FUNCTION, TP(tp), paranum, symtabs[tabptr].filledsize + paranum * 4, tabptr);
	}
	while (ISFUNCTYPE(sy)) {
		tp = sy;
		insymbol();
		if (sy == IDENT) {
			temp = id;
			insymbol();
			readsym(LPT, EXPECT_LPT_ERROR);
			CTAB.glbpos = GTAB.ptr;
			GTAB.insert(temp, FUNCTION, TP(tp), paralist(), 0, tabptr);
			readsym(RPT, EXPECT_RPT_ERROR);
			//test-skip
			readsym(LBR, EXPECT_LBR_ERROR);
			emit(SET, temp, "", "", NULL);
			emit(ENTER, "", "", "", NULL);
			compoundstatement();
			emit(EXIT, "", "", "", NULL);
			readsym(RBR, EXPECT_RBR_ERROR);
			tabptr++;
		}
		else {
			if (sy == MAIN) {
				if (TP(tp) == VOID) {
					hasmain = true;
					insymbol();
					readsym(LPT, EXPECT_LPT_ERROR);
					GTAB.insert("main", FUNCTION, VOID, 0, 0, tabptr);
					readsym(RPT, EXPECT_RPT_ERROR);
					//test-skip
					readsym(LBR, EXPECT_LBR_ERROR);
					emit(SET, "main", "", "", NULL);
					emit(ENTER, "", "", "", NULL);
					compoundstatement();
					emit(EXIT, "", "", "", NULL);
					if (sy == RBR) {
						ENABLE_EOF = true;
						insymbol();
					}
					else error(EXPECT_RBR_ERROR);
					if (input_f.is_open()) {
						error(UNEXPECTED_EOF_ERROR);
						input_f.close();
					}
					tabptr++;//应当最后一增，无实际意义
					return;
				}
				else error(REDEFINED_VAR_ERROR);
			}
			else error(EXPECT_ID_ERROR);
		}
	}
}

void constdec() {
	symbol tp;
	string name;
	while (sy == CONSTSY) {
		insymbol();
		if (ISVALTYPE(sy)) {
			tp = sy;
			insymbol();
			readsym(IDENT, EXPECT_ID_ERROR);
			readsym(BECOMESY, ILLEGAL_VARDEF_ERROR);
			if (sy == PLUS || sy == MINUS) {
				insymbol();
				num = (sy == MINUS) ? -num : num;
			}
			if (UNMATCH(tp, sy))
				error(TYPE_CONFLICT_ERROR);
			CTAB.insert(id, CONST, TP(tp), (tp == CHARSY) ? chr : num, 4, CTAB.filledsize);//如果在函数内常量定义，偏移要减去参数空间
			insymbol();
			while (sy == COMMA) {//rapidly read same-type const
				insymbol();
				readsym(IDENT, EXPECT_ID_ERROR);
				readsym(BECOMESY, ILLEGAL_VARDEF_ERROR);
				if (UNMATCH(tp, sy))
					error(TYPE_CONFLICT_ERROR);
				CTAB.insert(id, CONST, TP(tp), (tp == CHARSY) ? chr : num, 4, CTAB.filledsize);
				insymbol();
			}
			readsym(SEMICOLON, EXPECT_SEMI_ERROR);//normal exit
		}
		else error(EXPECT_TYPE_ERROR);
	}
}

void vardec() {
	symbol tp;
	while (ISVALTYPE(sy)) {//在同一类型中
		tp = sy;
		insymbol();
		readsym(IDENT, EXPECT_ID_ERROR);
		if (sy == LBK) {//数组声明
			insymbol();
			if (sy == INTCON && num > 0) {
				CTAB.insert(id, ARRAY, TP(tp), num, num * 4, CTAB.filledsize);
			}
			else error(ILLEGAL_ARRLEN_ERROR);
			insymbol();
			readsym(RBK, EXPECT_RBK_ERROR);
		}//单个数组声明结束
		else {//单个标识符
			CTAB.insert(id, VAR, TP(tp), 0, 4, CTAB.filledsize);
		}
		while (sy == COMMA) {
			insymbol();
			readsym(IDENT, EXPECT_ID_ERROR);
			if (sy == LBK) {//数组声明
				insymbol();
				if (sy == INTCON && num > 0) {
					CTAB.insert(id, ARRAY, TP(tp), num, num * 4, CTAB.filledsize);
				}
				else error(ILLEGAL_ARRLEN_ERROR);
				insymbol();
				readsym(RBK, EXPECT_RBK_ERROR);
			}//单个数组声明结束
			else {//单个标识符
				CTAB.insert(id, VAR, TP(tp), 0, 4, CTAB.filledsize);
			}
		}
		readsym(SEMICOLON, EXPECT_SEMI_ERROR);
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
		readsym(IDENT, EXPECT_ID_ERROR);
		pnum++;
		//先不在全部符号表里插参数了/////
		CTAB.insert(id, PARA, TP(tp), 0, 4, CTAB.filledsize);
	}
	else error(ILLEGAL_PARALIST_ERROR);
	while (sy == COMMA) {
		insymbol();
		if (ISVALTYPE(sy)) {
			tp = sy;
			insymbol();
			readsym(IDENT, EXPECT_ID_ERROR);
			pnum++;
			CTAB.insert(id, PARA, TP(tp), 0, 4, CTAB.filledsize);
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
	switch (sy) {
	case IDENT: {//赋值语句、函数调用语句、
		if (GTAB.ele(id) != NULL && GTAB.ele(id)->idtype == FUNCTION)
			call(GTAB.index(id));
		else assignment();
		readsym(SEMICOLON, EXPECT_SEMI_ERROR);
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
		insymbol();
		if (sy == LPT) {
			if (GTAB.ele(CTAB.glbpos)->symtype == VOID)
				error(TYPE_CONFLICT_ERROR);
			insymbol();
			bool isch;
			string expr= expression(&isch);
			if (isch && GTAB.ele(CTAB.glbpos)->symtype != CHAR)
				error(TYPE_CONFLICT_ERROR);
			emit(RET, expr, "", "", NULL);
			readsym(RPT, EXPECT_RPT_ERROR);
		}
		else emit(RET, "", "", "", NULL);
		readsym(SEMICOLON, EXPECT_SEMI_ERROR);
		break;
	}
	case PRINTSY: {
		printstatement();
		readsym(SEMICOLON, EXPECT_SEMI_ERROR);
		break;
	}
	case SCANSY: {
		scanstatement();
		readsym(SEMICOLON, EXPECT_SEMI_ERROR);
		break;
	}
	default: {
		error(ILLEGAL_STATE_ERROR);
		while (sy != SEMICOLON) {
			insymbol();
		}
		statement();
		break;
	}
	}
}

string call(int pos) {//优化时注意，有返回值函数调用单列一句话可能会多出无意义中间返回值变量
	string name = id;
	string returnvar;
	string parastk[TAB_MAX];
	int paranum = 0, pstk = 0;
	insymbol();
	readsym(LPT, EXPECT_LPT_ERROR);
	if (sy == RPT) {
		if (GTAB.ele(pos)->var != 0)
			error(ILLEGAL_PARALIST_ERROR);
		insymbol();
	}
	else {
		bool temp;
		int func_stab = GTAB.ele(pos)->addr;	
		parastk[pstk] = expression(&temp);
		if (temp != ((symtabs[func_stab]).ele(pstk++)->symtype == CHAR))
			error(TYPE_CONFLICT_ERROR);
		//emit(PUSH, expression(), name, "", nullptr);
		paranum++;
		while (sy == COMMA) {
			insymbol();
			parastk[pstk] = expression(&temp);
			if (temp != ((symtabs[func_stab]).ele(pstk++)->symtype == CHAR))
				error(TYPE_CONFLICT_ERROR);
			paranum++;
		}
		if (paranum != GTAB.ele(pos)->var)
			error(ILLEGAL_PARALIST_ERROR);
		readsym(RPT, EXPECT_RPT_ERROR);
	}
	for (int i = 0; i < pstk; i++)
		emit(PUSH, parastk[i], name, "", NULL);
	emit(CALL, name, "", "", &returnvar);
	return returnvar;
}



void ifstatement() {
	string ifbranch;
	string elselabel;
	string endlabel;
	insymbol();
	readsym(LPT, EXPECT_LPT_ERROR);
	ifbranch = condition();
	readsym(RPT, EXPECT_RPT_ERROR);
	emit(BZ, "", ifbranch, "", &elselabel);
	statement();
	emit(GOTO, "", "", "", &endlabel);
	emit(SET, elselabel, "", "", NULL);
	if (sy == ELSESY) {
		insymbol();
		statement();
	}
	emit(SET, endlabel, "", "", NULL);
}

void whilestatement() {
	string loopcondition;
	string dobegin;
	insymbol();
	emit(SET, "", "", "", &dobegin);
	statement();
	readsym(WHILESY, EXPECT_WHILE_ERROR);
	readsym(LPT, EXPECT_LPT_ERROR);
	loopcondition = condition();
	emit(BNZ, dobegin, loopcondition, "", NULL);
	readsym(RPT, EXPECT_RPT_ERROR);
}

void forstatement() {
	string initvar, loopvar, conditionvar, loopbegin, loopend, step;
	bool temp;
	int neg = 0;
	insymbol();
	readsym(LPT, EXPECT_LPT_ERROR);
	readsym(IDENT, EXPECT_ID_ERROR);
	loopvar = id;
	readsym(BECOMESY, EXPECT_BECOME_ERROR);
	initvar = expression(&temp);
	if (temp)error(TYPE_CONFLICT_ERROR);
	emit(BECOME, initvar, "", loopvar, NULL);//初始化循环变量
	readsym(SEMICOLON, EXPECT_SEMI_ERROR);
	emit(SET, "", "", "", &loopbegin);//循环开始
	conditionvar = condition();
	emit(BZ, "", conditionvar, "", &loopend);//不满足跳到结尾
	readsym(SEMICOLON, EXPECT_SEMI_ERROR);
	readsym(IDENT, EXPECT_ID_ERROR);
	loopvar = id;
	readsym(BECOMESY, EXPECT_BECOME_ERROR);
	readsym(IDENT, EXPECT_ID_ERROR);
	if (loopvar != id)
		error(ILLEGAL_FORLOOP_ERROR);
	if (sy == MINUS)
		neg = 1;
	else if (sy != PLUS)
		error(ILLEGAL_FORLOOP_ERROR);
	insymbol();
	readsym(INTCON, EXPECT_INT_ERROR);
	step = to_string(num);
	readsym(RPT, EXPECT_RPT_ERROR);
	statement();//循环内容
	emit(neg ? SUB : ADD, loopvar, step, loopvar, NULL);//循环变量自增（自减）
	emit(GOTO, loopbegin, "", "", NULL);//跳到循环开始
	emit(SET, loopend, "", "", NULL);//循环结尾
}

void scanstatement() {
	insymbol();
	readsym(LPT, EXPECT_LPT_ERROR);
	readsym(IDENT, EXPECT_ID_ERROR);
	if (CTAB.ele(id) == NULL) {
		if (GTAB.ele(id) == NULL)
			error(UNDEFINED_ID_ERROR);
		else {//标识符在全局符号表里
			int index = GTAB.index(id);
			if (GTAB.ele(index)->idtype == ARRAY|| \
				GTAB.ele(index)->idtype == CONST || \
				GTAB.ele(index)->idtype == FUNCTION) {//全局数组、常量、函数
				error(TYPE_CONFLICT_ERROR);
			}
			else emit(GTAB.ele(index)->symtype == CHAR ? SCANC : SCAN, id, "", "", NULL);//全局的变量
		}
	}
	else {//标识符在局部符号表里
		int index = CTAB.index(id);
		if (CTAB.ele(index)->idtype == ARRAY|| \
			CTAB.ele(index)->idtype == CONST || \
			CTAB.ele(index)->idtype == PARA) {//局部数组、常量、参数
			error(TYPE_CONFLICT_ERROR);
		}
		else emit(CTAB.ele(index)->symtype == CHAR ? SCANC : SCAN, id, "", "", NULL);//局部的变量
	}
	while (sy == COMMA) {
		insymbol();
		readsym(IDENT, EXPECT_ID_ERROR);
		if (CTAB.ele(id) == NULL) {
			if (GTAB.ele(id) == NULL)
				error(UNDEFINED_ID_ERROR);
			else {//标识符在全局符号表里
				int index = GTAB.index(id);
				if (GTAB.ele(index)->idtype == ARRAY || \
					GTAB.ele(index)->idtype == CONST || \
					GTAB.ele(index)->idtype == FUNCTION) {//全局数组、常量、函数
					error(TYPE_CONFLICT_ERROR);
				}
				else emit(GTAB.ele(index)->symtype == CHAR ? SCANC : SCAN, id, "", "", NULL);//全局的变量
			}
		}
		else {//标识符在局部符号表里
			int index = CTAB.index(id);
			if (CTAB.ele(index)->idtype == ARRAY || \
				CTAB.ele(index)->idtype == CONST || \
				CTAB.ele(index)->idtype == PARA) {//局部数组、常量、参数
				error(TYPE_CONFLICT_ERROR);
			}
			else emit(CTAB.ele(index)->symtype == CHAR ? SCANC : SCAN, id, "", "", NULL);//局部的变量
		}
	}
	readsym(RPT, EXPECT_RPT_ERROR);
}

void printstatement() {
	int strptr = -1;
	bool temp;
	insymbol();
	readsym(LPT, EXPECT_LPT_ERROR);
	if (sy == STRINGCON) {
		//readsym(STRINGCON, ILLEGAL_PARALIST_ERROR);
		for (int i = 0; i < const_strings.size(); i++) {
			if (const_strings[i] == str) {
				strptr = i;
				break;
			}
		}
		if (strptr == -1) {
			strptr = const_strings.size();
			const_strings.push_back(str);
		}
		emit(PRINTS, to_string(strptr), "", "", NULL);
		insymbol();
		if (sy == COMMA) {
			insymbol();
			string content = expression(&temp);
			emit(temp ? PRINTC : PRINT, content, "", "", NULL);
		}
	}
	else if (sy != RPT) {
		string content = expression(&temp);
		emit(temp ? PRINTC : PRINT, content, "", "", NULL);
	}
	else error(ILLEGAL_PARALIST_ERROR);
	readsym(RPT, EXPECT_RPT_ERROR);
}

void assignment() {//只有一次计算的表达式赋值（i=i+1）会生成不必要的中间变量，要优化
	string expvar, aryindex, idname;
	bool temp;
	readsym(IDENT, EXPECT_ID_ERROR);
	idname = id;
	if (CTAB.ele(id) == NULL) {
		if (GTAB.ele(id) == NULL)
			error(UNDEFINED_ID_ERROR);
		else {//标识符在全局符号表里
			int index = GTAB.index(id);
			if (GTAB.ele(index)->idtype == ARRAY) {//全局数组
				readsym(LBK, EXPECT_LBK_ERROR);
				aryindex = expression(&temp);
				if (temp)error(TYPE_CONFLICT_ERROR);
				readsym(RBK, EXPECT_RBK_ERROR);
				readsym(BECOMESY, EXPECT_BECOME_ERROR);
				expvar = expression(&temp);
				if ((GTAB.ele(index)->symtype == CHAR) != temp)error(TYPE_CONFLICT_ERROR);
				emit(ARYS, aryindex, expvar, idname, NULL);
			}
			else {//全局的变量、常量
				if (GTAB.ele(index)->idtype == CONST || GTAB.ele(index)->idtype == FUNCTION) {//全局常量、函数
					error(TYPE_CONFLICT_ERROR);
					insymbol();
				}
				else {//全局变量
					readsym(BECOMESY, EXPECT_BECOME_ERROR);
					expvar = expression(&temp);
					if ((GTAB.ele(index)->symtype == CHAR) != temp)error(TYPE_CONFLICT_ERROR);
					emit(BECOME, expvar, "", idname, NULL);
				}
			}
		}
	}
	else {//标识符在局部符号表里
		int index = CTAB.index(id);
		if (CTAB.ele(index)->idtype == ARRAY) {//局部数组
			readsym(LBK, EXPECT_LBK_ERROR);
			aryindex = expression(&temp);
			if (temp)error(TYPE_CONFLICT_ERROR);
			readsym(RBK, EXPECT_RBK_ERROR);
			readsym(BECOMESY, EXPECT_BECOME_ERROR);
			expvar = expression(&temp);
			if ((CTAB.ele(index)->symtype == CHAR) != temp)error(TYPE_CONFLICT_ERROR);
			emit(ARYS, aryindex, expvar, idname, NULL);
		}
		else {//局部的变量、常量
			if (CTAB.ele(index)->idtype == CONST || CTAB.ele(index)->idtype == PARA) {//局部常量、参数
				error(TYPE_CONFLICT_ERROR);
				insymbol();
			}
			else {//局部变量
				readsym(BECOMESY, EXPECT_BECOME_ERROR);
				expvar = expression(&temp);
				if ((CTAB.ele(index)->symtype == CHAR) != temp)error(TYPE_CONFLICT_ERROR);
				emit(BECOME, expvar, "", idname, NULL);
			}
		}
	}
}

string factor(bool *isch) {//＜因子＞::= ＜标识符＞｜＜标识符＞'['＜表达式＞']'｜＜整数＞|＜字符＞｜＜有返回值函数调用语句＞ | '('＜表达式＞')'
	string result;
	*isch = false;
	switch (sy) {
	case INTCON: {
		int n = num;
		insymbol();
		return to_string(n);
		break;
	}
	case CHARCON: {
		insymbol();
		string temp_str = "\'";
		temp_str = temp_str + chr + temp_str;
		*isch = true;
		return temp_str;
		break;
	}
	case IDENT: {
		if (GTAB.ele(id) != NULL && GTAB.ele(id)->idtype == FUNCTION) {
			if (GTAB.ele(id)->symtype == VOID) {
				error(TYPE_CONFLICT_ERROR);
			}
			if (GTAB.ele(id)->symtype == CHAR)
				*isch = true;
			return call(GTAB.index(id));
		}
		else {
			if (CTAB.ele(id) == NULL) {
				if (GTAB.ele(id) == NULL)
					error(UNDEFINED_ID_ERROR);
				else {//标识符在全局符号表里
					if (GTAB.ele(id)->symtype == CHAR)
						*isch = true;
					int index = GTAB.index(id);
					if (GTAB.ele(index)->idtype == ARRAY) {//全局数组
						insymbol();
						if (sy == LBK) {
							insymbol();
							bool temp;
							string expr = expression(&temp);
							if (temp)error(TYPE_CONFLICT_ERROR);
							emit(ARYL, GTAB.ele(index)->name, expr, "", &result);
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
				if (CTAB.ele(id)->symtype == CHAR)
					*isch = true;
				int index = CTAB.index(id);
				if (CTAB.ele(index)->idtype == ARRAY) {//局部数组
					insymbol();
					if (sy == LBK) {
						insymbol();
						bool temp;
						string expr = expression(&temp);
						if (temp)error(TYPE_CONFLICT_ERROR);
						emit(ARYL, CTAB.ele(index)->name, expr, "", &result);
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
		else error(EXPECT_INT_ERROR);
		break;
	}
	case MINUS: {//整数标记
		insymbol();
		if (sy == INTCON) {
			insymbol();
			return to_string(-num);
		}
		else error(EXPECT_INT_ERROR);
		break;
	}
	case LPT: {//表达式
		insymbol();
		bool temp;
		result = expression(&temp);
		CH2ASC(result);
		if (sy == RPT)
			insymbol();
		else error(EXPECT_RPT_ERROR);
		return result;
		break;
	}
	default: {
		error(ILLEGAL_FACTOR_ERROR);
		return "";
		break;
	}
	}
}

string term(bool *isch) {//＜项＞::= ＜因子＞{＜乘法运算符＞＜因子＞}
	string mid;
	*isch = true;
	bool temp;
	mid = factor(&temp);
	if (!temp)*isch = false;
	while (sy == MULSY || sy == DIVSY) {
		*isch = false;
		insymbol();
		string tmp = factor(&temp);
		CH2ASC(mid);
		CH2ASC(tmp);
		emit((sy == MULSY) ? MUL : DIV, mid, tmp, "", &mid);
	}
	return mid;
}

string expression(bool* isch) {//＜表达式＞::= ［＋｜－］＜项＞{＜加法运算符＞＜项＞}   //[+|-]只作用于第一个<项>
	int neg = 1;
	bool temp;
	*isch = true;
	if (sy == PLUS) {
		*isch = false;
		insymbol();
	}
	else if (sy == MINUS) {
		*isch = false;
		insymbol();
		neg = -1;
	}
	string mid;
	mid = term(&temp);
	if (!temp)*isch = false;
	if (neg == -1) {
		CH2ASC(mid);
		*isch = false;
		emit(NEG, mid, "", "", &mid);
	}
	while (sy == PLUS || sy == MINUS) {
		*isch = false;
		symbol addop = sy;
		insymbol();
		string tmp = term(&temp);
		CH2ASC(mid);
		CH2ASC(tmp);
		emit((addop == PLUS) ? ADD : SUB, mid, tmp, "", &mid);
	}
	return mid;
}

string condition() {
#define ADAPT if(isch_o1 && isch_o2) \
				 {CH2ASC(o1);CH2ASC(o2);} \
			  else if(isch_o1 || isch_o2) \
				 {error(TYPE_CONFLICT_ERROR);CH2ASC(o1);CH2ASC(o2);}
	string o1, o2, result;
	bool isch_o1, isch_o2;
	o1 = expression(&isch_o1);
	switch (sy) {
	case EQLSY: {
		insymbol();
		o2 = expression(&isch_o2);
		ADAPT
		emit(EQL, o1, o2, "", &result);
		break;
	}
	case NEQSY: {
		insymbol();
		o2 = expression(&isch_o2);
		ADAPT
		emit(NEQ, o1, o2, "", &result);
		break;
	}
	case GTRSY: {
		insymbol();
		o2 = expression(&isch_o2);
		ADAPT
		emit(GTR, o1, o2, "", &result);
		break;
	}
	case GEQSY: {
		insymbol();
		o2 = expression(&isch_o2);
		ADAPT
		emit(GEQ, o1, o2, "", &result);
		break;
	}
	case LESSY: {
		insymbol();
		o2 = expression(&isch_o2);
		ADAPT
		emit(LES, o1, o2, "", &result);
		break;
	}
	case LEQSY: {
		insymbol();
		o2 = expression(&isch_o2);
		ADAPT
		emit(LEQ, o1, o2, "", &result);
		break;
	}
	default: {
		if (isch_o1) {
			error(TYPE_CONFLICT_ERROR);
			CH2ASC(o1);
		}
		CH2ASC(o1);
		emit(NEQ, o1, "0", "", &result);
		break;
	}
	}
	return result;
}






