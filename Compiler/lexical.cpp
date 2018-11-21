#include "compiler.h"
#include"init.h"
#include "error.h"

#define LN " IN LINE " << lc
#define LETTER 0
#define NUMBER 1
#define STRING 2
#define CHARAC 3
#define LESCHR 4
#define GRTCHR 5
#define SLHCHR 6//Ð±¸Ü'/'
#define EQLCHR 7
#define EXCCHR 8//Ì¾ºÅ
#define SINGLE 9
#define UNDEFSY 10

void nextch() {
	if (!input_f.eof()) {
		ch = input_f.get();
		cc++;
		if (ch == '\n') {
			lc++;
			cc = 0;
		}
	}
	else {
		input_f.close();
		cout << "END OF FILE READED." << endl;
	}
}

int chClassify() {
	if (ISLETTER(ch))
		return LETTER;
	if (ISNUM(ch))
		return NUMBER;
	if (ch == '\'')
		return CHARAC;
	if (ch == '\"')
		return STRING;
	if (ch == '<')
		return LESCHR;
	if (ch == '>')
		return GRTCHR;
	if (ch == '/')
		return SLHCHR;
	if (ch == '=')
		return EQLCHR;
	if (ch == '!')
		return EXCCHR;
	if (ch == '+' || ch == '-' || ch == '*' || ch == '(' || ch == ')' || \
		ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == ';' || ch == ',')
		return SINGLE;
	if (ch == -1)
		return -1;
	return UNDEFSY;
}

void insymbol() {
READ:
	while (ch == ' ' || ch == '\t' || ch == '\n')
		nextch();
	switch (chClassify())
	{
	case LETTER: {
		int k = 0;
		id = "";
		while (ISLETTER(ch) || ISNUM(ch)) {
			id.append(1, ch);
			k++;
			nextch();
		}
		set<string>::iterator it;
		if ((it = key.find(id)) != key.end())
			sy = ksy[*it];
		else sy = IDENT;
		break;
	}
	case NUMBER: {
		sy = INTCON;
		num = 0;
		int k = 0;
		if (ch == '0') {
			nextch();
			if (!ISNUM(ch)) {
				k = 1;
				num = 0;
				break;
			}
			else error(ZERO_BEGIN_ERROR);
		}
		while ((ch >= '0') && (ch <= '9')) {
			num = num * 10 + (ch - '0');
			k++;
			nextch();
		}
		if (num > INT_MAX) {
			int temp;
			temp = (int)num;
			num = temp;
			error(INT_OVERFLOW_ERROR);
		}
		break;
	}
	case STRING: {
		int k = 0;
		str = "";
		nextch();
		while (ch != '\"') {
			if (ISSTRCHAR(ch)) {
				str.append(1, ch);
				k++;
			}
			else { 
				if (ch == '\n')
					error(EXPECT_DOUQUO_ERROR);
				else error(ILLEGAL_STRCH_ERROR);
				goto ERROR; 
			}
			nextch();
		}
		sy = STRINGCON;
		nextch();
		break;
	}
	case CHARAC: {
		nextch();
		if (!ISCHAR(ch))
			error(ILLEGAL_CHAR_ERROR);
		chr = ch;
		sy = CHARCON;
		nextch();
		if (ch != '\'') {
			error(EXPECT_SINQUO_ERROR);
			goto ERROR;
		}
		else nextch();
		break;
	}
	case LESCHR: {
		nextch();
		if (ch == '=') {
			sy = LEQSY;
			nextch();
		}
		else sy = LESSY;
		break;
	}
	case GRTCHR: {
		nextch();
		if (ch == '=') {
			sy = GEQSY;
			nextch();
		}
		else sy = GTRSY;
		break;
	}
	case SLHCHR: {
		nextch();
		if (ch != '*' && ch != '/')
			sy = DIVSY;
		else if (ch == '*') {
			nextch();
			do {
				while (ch != '*')
					nextch();
				nextch();
			} while (ch != '/');
			nextch();
			goto READ;
		}
		else {
			nextch();
			while (ch != '\n')
				nextch();
			nextch();
			goto READ;
		}
		break;
	}
	case EQLCHR: {
		nextch();
		if (ch == '=') {
			sy = EQLSY;
			nextch();
		}
		else sy = BECOMESY;
		break;
	}
	case EXCCHR: {
		nextch();
		if (ch == '=')
			sy = NEQSY;
		else goto ERROR;
		nextch();
		break;
	}
	case SINGLE: {
		sy = sps[ch];
		nextch();
		break;
	}
	case -1: {
		sy = END_OF_FILE;
		nextch();
		break;
	}
	default:
		error(UNDEFINED_CH_ERROR);
		nextch();
	ERROR:
		goto READ;
		break;
	}
}

void lexical_init() {
	nextch();
	insymbol();
}

int lexical_main() {
	int count = 1;
	char f_name[100] = { 0 };
	cin >> f_name;
	input_f.open(f_name, ios::in);
	if (input_f.is_open() == false) {
		cout << "Not a valid filename!" << endl;
		return 0;
	}
	init();
	nextch();
	while (true) {
		insymbol();
		cout << left << setw(4) << count;
		count++;
		switch (sy) {
		case INTCON:
		{cout << left << setw(10) << "INTCON " << num << endl; break; }
		case CHARCON:
		{cout << left << setw(10) << "CHARCON " << chr << endl; break; }
		case STRINGCON:
		{cout << left << setw(10) << "STRINGCON " << str << endl; break; }
		case CONSTSY:
		{cout << left << setw(10) << "CONSTSY " << "const" << endl; break; }
		case IDENT:
		{cout << left << setw(10) << "IDENT " << id << endl; break; }
		case PLUS:
		{cout << left << setw(10) << "PLUS " << '+' << endl; break; }
		case MINUS:
		{cout << left << setw(10) << "MINUS " << '-' << endl; break; }
		case MULSY:
		{cout << left << setw(10) << "MULSY " << '*' << endl; break; }
		case DIVSY:
		{cout << left << setw(10) << "DIVSY " << '/' << endl; break; }
		case EQLSY:
		{cout << left << setw(10) << "EQLSY " << "==" << endl; break; }
		case NEQSY:
		{cout << left << setw(10) << "NEQSY " << "!=" << endl; break; }
		case GTRSY:
		{cout << left << setw(10) << "GTRSY " << ">" << endl; break; }
		case GEQSY:
		{cout << left << setw(10) << "GRQ " << ">=" << endl; break; }
		case LESSY:
		{cout << left << setw(10) << "LESSY " << "<" << endl; break; }
		case LEQSY:
		{cout << left << setw(10) << "LEQSY " << "<=" << endl; break; }
		case LPT:
		{cout << left << setw(10) << "LPT " << '(' << endl; break; }
		case RPT:
		{cout << left << setw(10) << "RPT " << ')' << endl; break; }
		case LBK:
		{cout << left << setw(10) << "LBK " << '[' << endl; break; }
		case RBK:
		{cout << left << setw(10) << "RBK " << ']' << endl; break; }
		case LBR:
		{cout << left << setw(10) << "LBR " << '{' << endl; break; }
		case RBR:
		{cout << left << setw(10) << "RBR " << '}' << endl; break; }
		case COMMA:
		{cout << left << setw(10) << "COMMA " << ',' << endl; break; }
		case SEMICOLON:
		{cout << left << setw(10) << "SEMICOLON " << ';' << endl; break; }
		case BECOMESY:
		{cout << left << setw(10) << "BECOMESY " << '=' << endl; break; }
		case IFSY:
		{cout << left << setw(10) << "IFSY " << "if" << endl; break; }
		case WHILESY:
		{cout << left << setw(10) << "WHILESY " << "while" << endl; break; }
		case FORSY:
		{cout << left << setw(10) << "FORSY " << "for" << endl; break; }
		case DOSY:
		{cout << left << setw(10) << "DOSY " << "do" << endl; break; }
		case ELSESY:
		{cout << left << setw(10) << "ELSESY " << "else" << endl; break; }
		case INTSY:
		{cout << left << setw(10) << "INTSY " << "int" << endl; break; }
		case CHARSY:
		{cout << left << setw(10) << "CHARSY " << "char" << endl; break; }
		case VOIDSY:
		{cout << left << setw(10) << "VOIDSY " << "void" << endl; break; }
		case MAIN:
		{cout << left << setw(10) << "MAIN " << "main" << endl; break; }
		case RETURN:
		{cout << left << setw(10) << "RETURN " << "return" << endl; break; }
		case SCANSY:
		{cout << left << setw(10) << "SCANSY " << "scanf" << endl; break; }
		case PRINTSY:
		{cout << left << setw(10) << "PRINTSY " << "printf" << endl; break; }

		default: {cout << "Something bad happened." << endl; break; }
		}
	}
}