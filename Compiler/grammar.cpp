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
		tabptr = 0;//���ִ���һ���ԣ�����tabptr=0
		constdec();
		tabptr = 1;
	}
	while (ISVALTYPE(sy)) {//��ͬһ������
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
			if (sy == LBK) {//��������
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
			}//����������������
			else {//������ʶ��
				GTAB.insert(id, VAR, TP(tp), 0, 4, GTAB.filledsize);
			}
			while (sy == COMMA) {
				insymbol();
				if (sy = IDENT) {
					if (sy == LBK) {//��������
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
					}//����������������
					else {//������ʶ��
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

void constdec() {
	symbol tp;
	while (sy == CONSTSY) {
		insymbol();
		if (ISVALTYPE(sy)) {
			tp = sy;
			insymbol();
			if (sy == IDENT) {//read first const
				insymbol();
				if (sy == BECOME) {
					insymbol();
					if (UNMATCH(tp, sy))
						error(TYPE_CONFLICT_ERROR);
					CTAB.insert(id, CONST, TP(tp), (tp == CHARSY) ? chr : num, 4, CTAB.filledsize);
					insymbol();
				}
				else error(ILLEGAL_VARDEF_ERROR);
			}
			else error(EXPECT_ID_ERROR);
			while (sy == COMMA) {//raapidly read same-type const
				insymbol();
				if (sy == IDENT) {//read first const
					insymbol();
					if (sy == BECOME) {
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
	while (ISVALTYPE(sy)) {//��ͬһ������
		tp = sy;
		insymbol();
		if (sy == IDENT) {
			insymbol();
			if (sy == LBK) {//��������
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
			}//����������������
			else {//������ʶ��
				CTAB.insert(id, VAR, TP(tp), 0, 4, CTAB.filledsize);
			}
			while (sy == COMMA) {
				insymbol();
				if (sy = IDENT) {
					if (sy == LBK) {//��������
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
					}//����������������
					else {//������ʶ��
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
	#define paraEle GTAB.symbols[GTAB.ptr+pnum]
	int pnum = 0;
	symbol tp;
	if (sy == RPT)
		return 0;
	if (ISVALTYPE(sy)) {
		tp = sy;
		insymbol();
		if (sy == IDENT) {
			pnum++;
			paraEle.addr = 4 * (pnum - 1);
			paraEle.idtype = PARA;
			paraEle.name = id;
			paraEle.size = 4;
			paraEle.symtype = TP(tp);
			paraEle.var = 0;
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
				paraEle.addr = 4 * (pnum - 1);
				paraEle.idtype = PARA;
				paraEle.name = id;
				paraEle.size = 4;
				paraEle.symtype = TP(tp);
				paraEle.var = 0;
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
		case IDENT: {//��ֵ��䡢����������䡢
			if (GTAB.ele(id) != NULL && GTAB.ele(id)->idtype == FUNCTION)
				call(GTAB.index(id));
			else assignment();
			if (sy != SEMICOLON)
				error(EXPECT_SEMI_ERROR);
			else insymbol();
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
			///////////��Ԫʽ////////////



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

string call(int pos) {//�Ż�ʱע�⣬�з���ֵ�������õ���һ�仰���ܻ����������м䷵��ֵ����
	string name = id;
	string returnvar;
	int paranum = 0;
	insymbol();
	if (sy == LPT) {
		insymbol();
		if (sy == RPT) {
			if (GTAB.ele(name)->var != 0)
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
			if (paranum != GTAB.ele(name)->var)
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