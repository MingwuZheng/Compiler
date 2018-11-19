#include "compiler.h"

void init() {
	sps['+'] = PLUS;
	sps['-'] = MINUS;
	sps['*'] = MUL;
	sps['('] = LPT;
	sps[')'] = RPT;
	sps['['] = LBK;
	sps[']'] = RBK;
	sps['{'] = LBR;
	sps['}'] = RBR;
	sps[';'] = SEMICOLON;
	sps[','] = COMMA;

	string mainsy = "main";
	string ifsy = "if";
	string elsesy = "else";
	string dosy = "do";
	string whilesy = "while";
	string forsy = "for";
	string returnsy = "return";
	string constsy = "const";
	string intsy = "int";
	string charsy = "char";
	string voidsy = "void";
	string printsy = "printf";
	string scansy = "scanf";

	key.insert(mainsy);
	key.insert(ifsy);
	key.insert(elsesy);
	key.insert(dosy);
	key.insert(whilesy);
	key.insert(forsy);
	key.insert(returnsy);
	key.insert(constsy);
	key.insert(intsy);
	key.insert(charsy);
	key.insert(voidsy);
	key.insert(printsy);
	key.insert(scansy);


	ksy[mainsy] = MAIN;
	ksy[ifsy] = IFSY;
	ksy[elsesy] = ELSESY;
	ksy[dosy] = DOSY;
	ksy[whilesy] = WHILESY;
	ksy[forsy] = FORSY;
	ksy[returnsy] = RETURN;
	ksy[constsy] = CONSTSY;
	ksy[intsy] = INTSY;
	ksy[charsy] = CHARSY;
	ksy[voidsy] = VOIDSY;
	ksy[printsy] = PRINTSY;
	ksy[scansy] = SCANSY;
}