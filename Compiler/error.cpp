#include "compiler.h"
#define ETC 0
#define FATAL (errorcode == 30|| \
			   errorcode == ETC)
void error(int errorcode) {
	map<int, string> errorTab;
	{
		errorTab[1] = "ZERO_BEGIN_ERROR";
		errorTab[2] = "ILLEGAL_STRCH_ERROR";
		errorTab[3] = "ILLEGAL_CHAR_ERROR";
		errorTab[4] = "ILLEGAL_STATE_ERROR";
		errorTab[5] = "ILLEGAL_ARRLEN_ERROR";
		errorTab[6] = "ILLEGAL_FACTOR_ERROR";
		errorTab[7] = "ILLEGAL_FORLOOP_ERROR";
		errorTab[8] = "ILLEGAL_PARALIST_ERROR";
		errorTab[9] = "ILLEGAL_VARDEF_ERROR";
		errorTab[10] = "EXPECT_SINQUO_ERROR";
		errorTab[11] = "EXPECT_DOUQUO_ERROR";
		errorTab[12] = "EXPECT_LPT_ERROR";
		errorTab[13] = "EXPECT_RPT_ERROR";
		errorTab[14] = "EXPECT_RBK_ERROR";
		errorTab[15] = "EXPECT_LBR_ERROR";
		errorTab[16] = "EXPECT_RBR_ERROR";
		errorTab[17] = "EXPECT_SEMI_ERROR";
		errorTab[18] = "EXPECT_TYPE_ERROR";
		errorTab[19] = "EXPECT_INT_RROR";
		errorTab[20] = "EXPECT_CHAR_ERROR";
		errorTab[21] = "EXPECT_CONDITION_ERROR";
		errorTab[22] = "EXPECT_WHILE_ERROR";
		errorTab[23] = "EXPECT_RETURN_ERROR";
		errorTab[24] = "EXPECT_MAIN_ERROR";
		errorTab[25] = "UNDEFINED_ID_ERROR";
		errorTab[26] = "UNDEFINED_CH_ERROR";
		errorTab[27] = "REDEFINED_VAR_ERROR";
		errorTab[28] = "TYPE_CONFLICT_ERROR";
		errorTab[29] = "ARRAY_OVERFLOW_ERROR";
		errorTab[30] = "SYMTAB_OVERFLOW_ERROR";
		errorTab[31] = "INT_OVERFLOW_ERROR";
		errorTab[32] = "DIV_ZERO_ERROR";
		
		errorTab[33] = "EXPECT_ID_ERROR";
		errorTab[34] = "EXPECT_LBK_ERROR";
	}
	cout << errorTab[errorcode] << " in line " << lc << ",column " << cc << endl;
	if (FATAL)
		exit(0);
}