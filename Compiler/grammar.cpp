#include "compiler.h"
#include "error.h"
#include "lexical.h"
#include "grammar.h"
#include "midcode.h"

#define SEMI_FOLLOW(x) ((x)==IDENT||(x)==RBR||(x)==LBR||(x)==CHARSY||(x)==INTSY||(x)==VOIDSY||(x)==RETURN||\
						(x)==SCANSY||(x)==PRINTSY||(x)==CONSTSY||(x)==FORSY||(x)==DOSY||(x)==IFSY||(x)==ELSESY||(x)==SEMICOLON)
#define ISVALTYPE(x) (x == INTSY || x == CHARSY)
#define ISFUNCTYPE(x) (x == INTSY || x == CHARSY || x == VOIDSY)
#define TP(x) ((x == INTSY) ? INT : ((x == VOIDSY) ? VOID : CHAR))
#define UNMATCH(x,y) ((x == INTSY && y == CHARCON)||(x == CHARSY && y == INTCON))
#define CH2ASC(x) x = ((x[0] == '\'')?to_string((int)(x[1])):x)

bool RETURNED = false;

int literal2int(string literal_con) {
	if (ISLNUM(literal_con))
		return stoi(literal_con);
	else return (int)literal_con[1];
}

void readsym(symbol expect, int errormsg) {
	if (sy != expect) {
		if (expect == SEMICOLON) {
			if (SEMI_FOLLOW(sy))
				error(errormsg);
			else {
				if (!ERROR_HAPPENED)
					error(errormsg);
				nextline();
				insymbol();
			}
		}
		else error(errormsg);
	}
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
		if (TP(tp) != VOID && !RETURNED)
			error(EXPECT_RETURN_ERROR);
		RETURNED = false;
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
			if (TP(tp) != VOID && !RETURNED)
				error(EXPECT_RETURN_ERROR);
			RETURNED = false;
			tabptr++;
		}
		else {
			if (sy == MAIN) {
				if (TP(tp) == VOID) {
					hasmain = true;
					insymbol();
					readsym(LPT, EXPECT_LPT_ERROR);
					CTAB.glbpos = GTAB.ptr;
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
	string name;
	while (sy == CONSTSY) {
		insymbol();
		if (!ISVALTYPE(sy)) {
			error(EXPECT_TYPE_ERROR);
			nextline();
			insymbol();
			continue;
		}
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
		CTAB.insert(id, CONST, TP(tp), (tp == CHARSY) ? chr : num, 4, CTAB.filledsize);//����ں����ڳ������壬ƫ��Ҫ��ȥ�����ռ�
		insymbol();
		while (sy == COMMA) {//rapidly read same-type const
			insymbol();
			readsym(IDENT, EXPECT_ID_ERROR);
			readsym(BECOMESY, ILLEGAL_VARDEF_ERROR);
			if (sy == PLUS || sy == MINUS) {
				insymbol();
				num = (sy == MINUS) ? -num : num;
			}
			if (UNMATCH(tp, sy))
				error(TYPE_CONFLICT_ERROR);
			CTAB.insert(id, CONST, TP(tp), (tp == CHARSY) ? chr : num, 4, CTAB.filledsize);
			insymbol();
		}
		readsym(SEMICOLON, EXPECT_SEMI_ERROR);//normal exit
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
			if (sy == MINUS) insymbol();
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
				if (sy == MINUS) insymbol();
				insymbol();
				readsym(RBK, EXPECT_RBK_ERROR);
			}//����������������
			else CTAB.insert(id, VAR, TP(tp), 0, 4, CTAB.filledsize); //������ʶ��
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
		insymbol();
		if (sy != SEMICOLON) {
			if (GTAB.ele(CTAB.glbpos)->symtype == VOID)
				error(TYPE_CONFLICT_ERROR);
			readsym(LPT, EXPECT_LPT_ERROR);
			bool isch;
			string expr= expression(&isch);
			if (isch != (GTAB.ele(CTAB.glbpos)->symtype == CHAR))
				error(TYPE_CONFLICT_ERROR);
			emit(RET, expr, "", "", NULL);
			readsym(RPT, EXPECT_RPT_ERROR);
		}
		else emit(RET, "", "", "", NULL);
		readsym(SEMICOLON, EXPECT_SEMI_ERROR);
		RETURNED = true;
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
		while (sy != SEMICOLON)
			insymbol();
		statement();
		break;
	}
	}
}

string call(int pos) {//�Ż�ʱע�⣬�з���ֵ�������õ���һ�仰���ܻ����������м䷵��ֵ����
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
		string stkmid;
		int func_stab = GTAB.ele(pos)->addr;	
		/*
		if (FAST_MODE)parastk[pstk] = expression(&temp);
		else {
			emit(ADD, expression(&temp), "0", "", &stkmid);
			parastk[pstk] = stkmid;
		}
		*/
		parastk[pstk] = expression(&temp);
		if (temp != ((symtabs[func_stab]).ele(pstk++)->symtype == CHAR) && STRONG_TYPE)
			error(TYPE_CONFLICT_ERROR);
		//emit(PUSH, expression(), name, "", nullptr);
		paranum++;
		while (sy == COMMA) {
			insymbol();
			/*
			if(FAST_MODE)parastk[pstk] = expression(&temp);
			else {
				emit(ADD, expression(&temp), "0", "", &stkmid);
				parastk[pstk] = stkmid;
			}
			*/
			parastk[pstk] = expression(&temp);
			if (temp != ((symtabs[func_stab]).ele(pstk++)->symtype == CHAR) && STRONG_TYPE)
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
	if (temp && STRONG_TYPE)error(TYPE_CONFLICT_ERROR);
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
	insymbol();
	readsym(INTCON, EXPECT_INT_ERROR);
	step = to_string(num);
	readsym(RPT, EXPECT_RPT_ERROR);
	statement();//ѭ������
	///////////////////////
	string looptemp;
	emit(neg ? SUB : ADD, loopvar, step, "", &looptemp);//ѭ�������������Լ���
	emit(BECOME, looptemp, "", loopvar, NULL);
	emit(GOTO, loopbegin, "", "", NULL);//����ѭ����ʼ
	emit(SET, loopend, "", "", NULL);//ѭ����β
}

void scanstatement() {
	insymbol();
	readsym(LPT, EXPECT_LPT_ERROR);
	readsym(IDENT, EXPECT_ID_ERROR);
	if (CTAB.ele(id) == NULL) {
		if (GTAB.ele(id) == NULL)
			error(UNDEFINED_ID_ERROR);
		else {//��ʶ����ȫ�ַ��ű���
			int index = GTAB.index(id);
			if (GTAB.ele(index)->idtype == ARRAY|| \
				GTAB.ele(index)->idtype == CONST || \
				GTAB.ele(index)->idtype == FUNCTION) {//ȫ�����顢����������
				error(TYPE_CONFLICT_ERROR);
			}
			else emit(GTAB.ele(index)->symtype == CHAR ? SCANC : SCAN, id, "", "", NULL);//ȫ�ֵı���
		}
	}
	else {//��ʶ���ھֲ����ű���
		int index = CTAB.index(id);
		if (CTAB.ele(index)->idtype == ARRAY|| \
			CTAB.ele(index)->idtype == CONST || \
			CTAB.ele(index)->idtype == PARA) {//�ֲ����顢����������
			error(TYPE_CONFLICT_ERROR);
		}
		else emit(CTAB.ele(index)->symtype == CHAR ? SCANC : SCAN, id, "", "", NULL);//�ֲ��ı���
	}
	while (sy == COMMA) {
		insymbol();
		readsym(IDENT, EXPECT_ID_ERROR);
		if (CTAB.ele(id) == NULL) {
			if (GTAB.ele(id) == NULL)
				error(UNDEFINED_ID_ERROR);
			else {//��ʶ����ȫ�ַ��ű���
				int index = GTAB.index(id);
				if (GTAB.ele(index)->idtype == ARRAY || \
					GTAB.ele(index)->idtype == CONST || \
					GTAB.ele(index)->idtype == FUNCTION) {//ȫ�����顢����������
					error(TYPE_CONFLICT_ERROR);
				}
				else emit(GTAB.ele(index)->symtype == CHAR ? SCANC : SCAN, id, "", "", NULL);//ȫ�ֵı���
			}
		}
		else {//��ʶ���ھֲ����ű���
			int index = CTAB.index(id);
			if (CTAB.ele(index)->idtype == ARRAY || \
				CTAB.ele(index)->idtype == CONST || \
				CTAB.ele(index)->idtype == PARA) {//�ֲ����顢����������
				error(TYPE_CONFLICT_ERROR);
			}
			else emit(CTAB.ele(index)->symtype == CHAR ? SCANC : SCAN, id, "", "", NULL);//�ֲ��ı���
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

void assignment() {//ֻ��һ�μ���ı��ʽ��ֵ��i=i+1�������ɲ���Ҫ���м������Ҫ�Ż�
	string expvar, aryindex, idname;
	bool temp;
	readsym(IDENT, EXPECT_ID_ERROR);
	idname = id;
	if (CTAB.ele(id) == NULL) {
		if (GTAB.ele(id) == NULL)
			error(UNDEFINED_ID_ERROR);
		else {//��ʶ����ȫ�ַ��ű���
			int index = GTAB.index(id);
			if (GTAB.ele(index)->idtype == ARRAY) {//ȫ������
				readsym(LBK, EXPECT_LBK_ERROR);
				aryindex = expression(&temp);
				if (temp)error(TYPE_CONFLICT_ERROR);
				if (ISLNUM(aryindex)) {
					int index_var = literal2int(aryindex);
					if (!(index_var >= 0 && index_var < GTAB.ele(index)->var))
						error(ILLEGAL_ARRLEN_ERROR);
				}
				readsym(RBK, EXPECT_RBK_ERROR);
				readsym(BECOMESY, EXPECT_BECOME_ERROR);
				expvar = expression(&temp);
				if ((GTAB.ele(index)->symtype == CHAR) != temp)error(TYPE_CONFLICT_ERROR);
				emit(ARYS, aryindex, expvar, idname, NULL);
			}
			else {//ȫ�ֵı���������
				if (GTAB.ele(index)->idtype == CONST || GTAB.ele(index)->idtype == FUNCTION) {//ȫ�ֳ���������
					error(TYPE_CONFLICT_ERROR);
					insymbol();
				}
				else {//ȫ�ֱ���
					readsym(BECOMESY, EXPECT_BECOME_ERROR);
					expvar = expression(&temp);
					if ((GTAB.ele(index)->symtype == CHAR) != temp)error(TYPE_CONFLICT_ERROR);
					emit(BECOME, expvar, "", idname, NULL);
				}
			}
		}
	}
	else {//��ʶ���ھֲ����ű���
		int index = CTAB.index(id);
		if (CTAB.ele(index)->idtype == ARRAY) {//�ֲ�����
			readsym(LBK, EXPECT_LBK_ERROR);
			aryindex = expression(&temp);
			if (temp)error(TYPE_CONFLICT_ERROR);
			if (ISLNUM(aryindex)) {
				int index_var = literal2int(aryindex);
				if (!(index_var >= 0 && index_var < CTAB.ele(index)->var))
					error(ILLEGAL_ARRLEN_ERROR);
			}
			readsym(RBK, EXPECT_RBK_ERROR);
			readsym(BECOMESY, EXPECT_BECOME_ERROR);
			expvar = expression(&temp);
			if ((CTAB.ele(index)->symtype == CHAR) != temp)error(TYPE_CONFLICT_ERROR);
			emit(ARYS, aryindex, expvar, idname, NULL);
		}
		else {//�ֲ��ı���������
			//if (CTAB.ele(index)->idtype == CONST || CTAB.ele(index)->idtype == PARA) {//�ֲ�����������
			if (CTAB.ele(index)->idtype == CONST) {//�ֲ�����
				error(TYPE_CONFLICT_ERROR);
				insymbol();
			}
			else {//�ֲ�����
				readsym(BECOMESY, EXPECT_BECOME_ERROR);
				expvar = expression(&temp);
				if ((CTAB.ele(index)->symtype == CHAR) != temp)error(TYPE_CONFLICT_ERROR);
				emit(BECOME, expvar, "", idname, NULL);
			}
		}
	}
}

string factor(bool *isch) {//�����ӣ�::= ����ʶ����������ʶ����'['�����ʽ��']'����������|���ַ��������з���ֵ����������䣾 | '('�����ʽ��')'
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
				if (GTAB.ele(id) == NULL) {
					error(UNDEFINED_ID_ERROR);
					insymbol();
					return id;
				}
				else {//��ʶ����ȫ�ַ��ű���
					if (GTAB.ele(id)->symtype == CHAR)
						*isch = true;
					int index = GTAB.index(id);
					if (GTAB.ele(index)->idtype == ARRAY) {//ȫ������
						insymbol();
						if (sy == LBK) {
							insymbol();
							bool temp;
							string expr = expression(&temp);
							if (temp)error(TYPE_CONFLICT_ERROR);
							if (ISLNUM(expr)) {
								int index_var = literal2int(expr);
								if (!(index_var >= 0 && index_var < GTAB.ele(index)->var))
									error(ILLEGAL_ARRLEN_ERROR);
							}
							emit(ARYL, GTAB.ele(index)->name, expr, "", &result);
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
						else {//ȫ�ֱ���,����Ϊ��ʵ��x+add()����һ����Ҫ���zz������ֻ�ܰ�ȫ�ֱ������м�����ȴ���
							if(!FAST_MODE)emit(BECOME, id, "", "", &result);
							else result = id;
							insymbol();
							return result;
						}
					}
				}
			}
			else {//��ʶ���ھֲ����ű���
				if (CTAB.ele(id)->symtype == CHAR)
					*isch = true;
				int index = CTAB.index(id);
				if (CTAB.ele(index)->idtype == ARRAY) {//�ֲ�����
					insymbol();
					if (sy == LBK) {
						insymbol();
						bool temp;
						string expr = expression(&temp);
						if (temp)error(TYPE_CONFLICT_ERROR);
						if (ISLNUM(expr)) {
							int index_var = literal2int(expr);
							if (!(index_var >= 0 && index_var < CTAB.ele(index)->var))
								error(ILLEGAL_ARRLEN_ERROR);
						}
						emit(ARYL, CTAB.ele(index)->name, expr, "", &result);
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
	error(ILLEGAL_FACTOR_ERROR);
	return "";
}

string term(bool *isch) {//���::= �����ӣ�{���˷�������������ӣ�}
	string mid;
	*isch = true;
	bool temp;
	mid = factor(&temp);
	if (!temp)*isch = false;
	while (sy == MULSY || sy == DIVSY) {
		symbol t = sy;
		*isch = false;
		insymbol();
		string tmp = factor(&temp);
		CH2ASC(mid);
		CH2ASC(tmp);
		if (ISLITERAL(mid) && ISLITERAL(tmp)) {
			int a = literal2int(mid), b = literal2int(tmp);
			mid = to_string((t == MULSY) ? a * b : a / b);
		}
		else emit((t == MULSY) ? MUL : DIV, mid, tmp, "", &mid);
	}
	return mid;
}

string expression(bool* isch) {//�����ʽ��::= �ۣ������ݣ��{���ӷ�����������}   //[+|-]ֻ�����ڵ�һ��<��>
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
		if (ISLITERAL(mid))
			mid = to_string(-literal2int(mid));
		else emit(NEG, mid, "", "", &mid);
	}
	while (sy == PLUS || sy == MINUS) {
		*isch = false;
		symbol addop = sy;
		insymbol();
		string tmp = term(&temp);
		CH2ASC(mid);
		CH2ASC(tmp);
		if (ISLITERAL(mid) && ISLITERAL(tmp)) {
			int a = literal2int(mid), b = literal2int(tmp);
			mid = to_string((addop ==  PLUS) ? a + b : a - b);
		}
		else emit((addop == PLUS) ? ADD : SUB, mid, tmp, "", &mid);
	}
	return mid;
}

string condition() {
	/*
#define ADAPT do{if(isch_o1 && isch_o2) \
				 {CH2ASC(o1);CH2ASC(o2);} \
				 else if(STRONG_TYPE && (isch_o1 || isch_o2)) \
				 {error(TYPE_CONFLICT_ERROR);CH2ASC(o1);CH2ASC(o2);}}while(0)
*/
#define ADAPT do{if(STRONG_TYPE && (isch_o1 || isch_o2)) \
				 {error(TYPE_CONFLICT_ERROR);CH2ASC(o1);CH2ASC(o2);}}while(0)

	string o1, o2, result;
	bool isch_o1, isch_o2;
	o1 = expression(&isch_o1);
	switch (sy) {
	case EQLSY: {
		insymbol();
		o2 = expression(&isch_o2);
		ADAPT;
		emit(EQL, o1, o2, "", &result);
		break;
	}
	case NEQSY: {
		insymbol();
		o2 = expression(&isch_o2);
		ADAPT;
		emit(NEQ, o1, o2, "", &result);
		break;
	}
	case GTRSY: {
		insymbol();
		o2 = expression(&isch_o2);
		ADAPT;
		emit(GTR, o1, o2, "", &result);
		break;
	}
	case GEQSY: {
		insymbol();
		o2 = expression(&isch_o2);
		ADAPT;
		emit(GEQ, o1, o2, "", &result);
		break;
	}
	case LESSY: {
		insymbol();
		o2 = expression(&isch_o2);
		ADAPT;
		emit(LES, o1, o2, "", &result);
		break;
	}
	case LEQSY: {
		insymbol();
		o2 = expression(&isch_o2);
		ADAPT;
		emit(LEQ, o1, o2, "", &result);
		break;
	}
	default: {
		if (isch_o1 && STRONG_TYPE)
			error(TYPE_CONFLICT_ERROR);
		CH2ASC(o1);
		emit(NEQ, o1, "0", "", &result);
		break;
	}
	}
	return result;
}






