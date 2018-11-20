#include "compiler.h"
#include "error.h"
#include "lexical.h"
#include "grammar.h"
#include "midcode.h"

#define ISVALTYPE(x) (x == INTSY || x == CHARSY)
#define ISFUNCTYPE(x) (x == INTSY || x == CHARSY || x == VOIDSY)
#define TP(x) ((x == INTSY) ? INT : ((x == VOIDSY) ? VOID : CHAR))
#define UNMATCH(x,y) ((x == INTSY && y == CHARCON)||(x == CHARSY && y == INTCON))


void readsym(symbol expect, int errormsg) {
	if (sy != expect)
		error(errormsg);
	else insymbol();
}

void program() {
	bool func = false, hasmain = false;
	symbol tp;
	string temp;
	if (sy == CONSTSY) {
		tabptr = 0;//���ִ���һ���ԣ�����tabptr=0
		constdec();
		tabptr = 1;
	}
	while (ISVALTYPE(sy)) {//��ͬһ������
		tp = sy;
		insymbol();
		readsym(IDENT, EXPECT_ID_ERROR);
		temp = id;
		if (sy == LPT) {
			insymbol();
			func = true;
			break;
		}
		if (sy == LBK) {//��������
			insymbol();
			if (sy == INTCON && num > 0) {
				GTAB.insert(id, ARRAY, TP(tp), num, num * 4, GTAB.filledsize);
			}
			else error(ILLEGAL_ARRLEN_ERROR);
			insymbol();
			readsym(RBK, EXPECT_RBK_ERROR);
		}//����������������
		else {//������ʶ��
			GTAB.insert(id, VAR, TP(tp), 0, 4, GTAB.filledsize);
		}
		while (sy == COMMA) {
			insymbol();
			readsym(IDENT, EXPECT_ID_ERROR);
			if (sy == LBK) {//��������
				insymbol();
				if (sy == INTCON && num > 0) {
					GTAB.insert(id, ARRAY, TP(tp), num, num * 4, GTAB.filledsize);
				}
				else error(ILLEGAL_ARRLEN_ERROR);
				insymbol();
				readsym(RBK, EXPECT_RBK_ERROR);
			}//����������������
			else {//������ʶ��
				GTAB.insert(id, VAR, TP(tp), 0, 4, GTAB.filledsize);
			}
		}
		readsym(SEMICOLON, EXPECT_SEMI_ERROR);
	}
	if (func) {
		//ע�ắ��
		CTAB.glbpos = GTAB.ptr;
		GTAB.insert(temp, FUNCTION, TP(tp), paralist(), 0, tabptr);//������size��0����Ϊ�ֲ����ű��м�¼
		readsym(RPT, EXPECT_RPT_ERROR);
		readsym(LBR, EXPECT_LBR_ERROR);
		emit(SET, temp, "", "", NULL);
		emit(ENTER, "", "", "", NULL);
		compoundstatement();
		emit(EXIT, "", "", "", NULL);
		readsym(RBR, EXPECT_RBR_ERROR);
		tabptr++;//������һ������ǰΪ�����ռ�
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
					readsym(RBR, EXPECT_RBR_ERROR);
					tabptr++;//Ӧ�����һ������ʵ������
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
	while (sy == CONSTSY) {
		insymbol();
		if (ISVALTYPE(sy)) {
			tp = sy;
			insymbol();
			readsym(IDENT, EXPECT_ID_ERROR);
			readsym(BECOMESY, ILLEGAL_VARDEF_ERROR);
			if (UNMATCH(tp, sy))
				error(TYPE_CONFLICT_ERROR);
			CTAB.insert(id, CONST, TP(tp), (tp == CHARSY) ? chr : num, 4, CTAB.filledsize);//����ں����ڳ������壬ƫ��Ҫ��ȥ�����ռ�
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
	while (ISVALTYPE(sy)) {//��ͬһ������
		tp = sy;
		insymbol();
		readsym(IDENT, EXPECT_ID_ERROR);
		if (sy == LBK) {//��������
			insymbol();
			if (sy == INTCON && num > 0) {
				CTAB.insert(id, ARRAY, TP(tp), num, num * 4, CTAB.filledsize);
			}
			else error(ILLEGAL_ARRLEN_ERROR);
			insymbol();
			readsym(RBK, EXPECT_RBK_ERROR);
		}//����������������
		else {//������ʶ��
			CTAB.insert(id, VAR, TP(tp), 0, 4, CTAB.filledsize);
		}
		while (sy == COMMA) {
			insymbol();
			readsym(IDENT, EXPECT_ID_ERROR);
			if (sy == LBK) {//��������
				insymbol();
				if (sy == INTCON && num > 0) {
					CTAB.insert(id, ARRAY, TP(tp), num, num * 4, CTAB.filledsize);
				}
				else error(ILLEGAL_ARRLEN_ERROR);
				insymbol();
				readsym(RBK, EXPECT_RBK_ERROR);
			}//����������������
			else {//������ʶ��
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
		//�Ȳ���ȫ�����ű���������/////
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
	switch (sy){
		case IDENT: {//��ֵ��䡢����������䡢
			if (GTAB.ele(id) != NULL && GTAB.ele(id)->idtype == FUNCTION)
				call(GTAB.index(id));
			else assignment();
			readsym(SEMICOLON, EXPECT_SEMI_ERROR);
			break;
		}
		case LBR: {//�����
			insymbol();
			while (sy != RBR)
				statement();
			insymbol();
			break;
		}
		case SEMICOLON: {//�����
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
				readsym(RPT, EXPECT_RPT_ERROR);
			}
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
		default: {error(ILLEGAL_STATE_ERROR); break; }
	}
}

string call(int pos) {//�Ż�ʱע�⣬�з���ֵ�������õ���һ�仰���ܻ����������м䷵��ֵ����
	string name = id;
	string returnvar;
	int paranum = 0;
	insymbol();
	readsym(LPT, EXPECT_LPT_ERROR);
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
		readsym(RPT, EXPECT_RPT_ERROR);
	}
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
	int neg = 0;
	readsym(LPT, EXPECT_LPT_ERROR);
	readsym(IDENT, EXPECT_ID_ERROR);
	loopvar = id;
	readsym(BECOMESY, EXPECT_BECOME_ERROR);
	initvar = expression();
	emit(BECOME, initvar, "", loopvar, NULL);//��ʼ��ѭ������
	readsym(SEMICOLON, EXPECT_SEMI_ERROR);
	emit(SET, "", "", "", &loopbegin);//ѭ����ʼ
	conditionvar = condition();
	emit(BZ, "", conditionvar, "", &loopend);//������������β
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
	readsym(INTCON, EXPECT_INT_ERROR);
	step = to_string(num);
	readsym(RPT, EXPECT_RPT_ERROR);
	statement();//ѭ������
	emit(neg ? SUB : ADD, loopvar, step, loopvar, NULL);//ѭ�������������Լ���
	emit(GOTO, loopbegin, "", "", NULL);//����ѭ����ʼ
	emit(SET, loopend, "", "", NULL);//ѭ����β
}

void scanstatement() {
	readsym(LPT, EXPECT_LPT_ERROR);
	readsym(IDENT, EXPECT_ID_ERROR);
	emit(SCAN, id, "", "", NULL);
	while (sy == COMMA) {
		readsym(IDENT, EXPECT_ID_ERROR);
		emit(SCAN, id, "", "", NULL);
	}
	readsym(RPT, EXPECT_RPT_ERROR);
}

void printstatement() {
	int strptr = -1;
	readsym(LPT, EXPECT_LPT_ERROR);
	if (sy == IDENT)
		emit(PRINT, id, "", "", NULL);
	else {
		readsym(STRINGCON, ILLEGAL_PARALIST_ERROR);
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
		if (sy == COMMA) {
			readsym(IDENT, EXPECT_ID_ERROR);
			emit(PRINT, id, "", "", NULL);
		}
	}
	readsym(RPT, EXPECT_RPT_ERROR);
}

void assignment() {
	string expvar, aryindex, idname;
	readsym(IDENT, EXPECT_ID_ERROR);
	idname = id;
	if (CTAB.ele(id) == NULL) {
		if (GTAB.ele(id) == NULL)
			error(UNDEFINED_ID_ERROR);
		else {//��ʶ����ȫ�ַ��ű���
			int index = GTAB.index(id);
			if (GTAB.ele(index)->idtype == ARRAY) {//ȫ������
				insymbol();
				readsym(LBK, EXPECT_LBK_ERROR);
				aryindex = expression();
				readsym(RBK, EXPECT_RBK_ERROR);
				readsym(BECOMESY, EXPECT_BECOME_ERROR);
				expvar = expression();
				emit(ARYS, aryindex, expvar, idname, NULL);
			}
			else {//ȫ�ֵı���������
				if (GTAB.ele(index)->idtype == CONST) {//ȫ�ֳ���
					error(TYPE_CONFLICT_ERROR);
					insymbol;
				}
				else {//ȫ�ֱ���
					insymbol();
					readsym(BECOMESY, EXPECT_BECOME_ERROR);
					expvar = expression();
					emit(BECOME, expvar, "", idname, NULL);
				}
			}
		}
	}
	else {//��ʶ���ھֲ����ű���
		int index = CTAB.index(id);
		if (CTAB.ele(index)->idtype == ARRAY) {//�ֲ�����
			insymbol();
			readsym(LBK, EXPECT_LBK_ERROR);
			aryindex = expression();
			readsym(RBK, EXPECT_RBK_ERROR);
			readsym(BECOMESY, EXPECT_BECOME_ERROR);
			expvar = expression();
			emit(ARYS, aryindex, expvar, idname, NULL);
		}
		else {//�ֲ��ı���������
			if (CTAB.ele(index)->idtype == CONST) {//�ֲ�����
				error(TYPE_CONFLICT_ERROR);
				insymbol;
			}
			else {//�ֲ�����������
				insymbol();
				readsym(BECOMESY, EXPECT_BECOME_ERROR);
				expvar = expression();
				emit(BECOME, expvar, "", idname, NULL);
			}
		}
	}
}

string factor() {//�����ӣ�::= ����ʶ����������ʶ����'['�����ʽ��']'����������|���ַ��������з���ֵ����������䣾 | '('�����ʽ��')'
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
					else {//��ʶ����ȫ�ַ��ű���
						int index = GTAB.index(id);
						if (GTAB.ele(index)->idtype == ARRAY) {//ȫ������
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
						else {//ȫ�ֵı���������
							if (GTAB.ele(index)->idtype == CONST) {//ȫ�ֳ���
								insymbol();
								return to_string(GTAB.ele(index)->var);//�����滻
							}
							else {//ȫ�ֱ���
								insymbol();
								return id;
							}
						}
					}
				}
				else {//��ʶ���ھֲ����ű���
					int index = CTAB.index(id);
					if (CTAB.ele(index)->idtype == ARRAY) {//�ֲ�����
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
					else {//�ֲ��ı���������
						if (CTAB.ele(index)->idtype == CONST) {//�ֲ�����
							insymbol();
							return to_string(CTAB.ele(index)->var);//�����滻
						}
						else {//�ֲ�����������
							insymbol();
							return id;
						}
					}
				}

			}
			break;
		}
		case PLUS: {//�������
			insymbol();
			if (sy == INTCON) {
				insymbol();
				return to_string(num);
			}
			else error(EXPECT_INT_ERROR);
			break;
		}
		case MINUS: {//�������
			insymbol();
			if (sy == INTCON) {
				insymbol();
				return to_string(-num);
			}
			else error(EXPECT_INT_ERROR);
			break;
		}
		case LPT: {//���ʽ
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

string term() {//���::= �����ӣ�{���˷�������������ӣ�}
	string mid;
	mid = factor();
	while (sy == MULSY || sy == DIVSY) {
		insymbol();
		string tmp = factor();
		emit((sy == MULSY) ? MUL : DIV, mid, tmp, "", &mid);
	}
	return mid;
}

string expression() {//�����ʽ��::= �ۣ������ݣ��{���ӷ�����������}   //[+|-]ֻ�����ڵ�һ��<��>
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






