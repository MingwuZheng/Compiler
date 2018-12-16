#include "compiler.h"
#include "midcode.h"
#include "analyse.h"
#include <stack>
#include <algorithm> 

extern int qtnry_ptr;
int qtnry_num;
map<string, int> label2pos;
map<int, int>pos2blk;

bool is_entrance(int pos) {
#define ISBRANCH(x) (x == RET || x == EXIT || x == GOTO || x == BNZ || x == BZ)
	//if (pos == 0)
	//	return true;反正不可能是0
	if (midcodes[pos].op == SET)
		return true;
	if (ISBRANCH(midcodes[pos - 1].op))
		return true;
	return false;
}

void flush_graph::def_use_cal(int blkno, int mcno) {
#define ISCALOP(x) ((x==ADD)||(x==SUB)||(x==MUL)||(x==DIV))
#define ISCONDITION(x) ((x==EQL)||(x==NEQ)||(x==GTR)||(x==LES)||(x==GEQ)||(x==LEQ))
#define SETDEFUSE(part,des) do{\
		if(midcodes[mcno].##part## != "" && !ISGLOBAL(midcodes[mcno].##part##) && !ISLCONST(midcodes[mcno].##part##)\
	&& !ISMIDVAR(midcodes[mcno].##part##) && blocks[blkno].vars.find(midcodes[mcno].##part##) == blocks[blkno].vars.end()){\
			blocks[blkno].vars.insert(midcodes[mcno].##part##);\
			blocks[blkno].##des##[var2idx(midcodes[mcno].##part##)] = true;}\
		}while(0)
	//将参数插入vars并置为def
	if (blkno == 1) {
		for (int i = 0; i < GTAB.ele(function)->var; i++) {
			blocks[blkno].vars.insert(funcname2tab(function).ele(i)->name);
			blocks[blkno].def[i] = true;
		}
	}
	qtnry_operator oper;
	oper = midcodes[mcno].op;
	if (ISCALOP(oper)) {
		SETDEFUSE(result, def);
		SETDEFUSE(op1, use);
		SETDEFUSE(op2, use);
	}
	else if (oper == BECOME || oper == NEG) {
		SETDEFUSE(result, def);
		SETDEFUSE(op1, use);
	}
	else if (ISCONDITION(oper)) {
		SETDEFUSE(op1, use);
		SETDEFUSE(op2, use);
	}
	else if (oper == SCAN || oper == SCANC) {
		SETDEFUSE(op1, def);
	}
	else if (oper == PRINT || oper == RET) {
		SETDEFUSE(op1, use);
	}
	else if (oper == ARYL) {
		SETDEFUSE(result, def);
		SETDEFUSE(op2, use);
	}
	else if (oper == ARYS) {
		SETDEFUSE(op1, use);
		SETDEFUSE(op2, use);
	}

}

int flush_graph::gen_block(int pos, int preblk) {
	int i, curblk;
	//如果已经建立起了块
	if (pos2blk.find(pos) != pos2blk.end()) {
		blocks[pos2blk[pos]].addpre(preblk);
		return pos2blk[pos];
	}
	//入口
	if (preblk == NONBLK) {
		blocks[0].entrance = pos;
		blocks[0].exit = pos;
		blocks[0].next1 = 1;
		blocks[0].next2 = NONBLK;
		blocknum++;
		gen_block(pos + 1, 0);
		return 0;
	}
	//出口
	if (pos == -1) {
		pos2blk[pos] = blocknum;
		blocks[blocknum].entrance = -1;
		blocks[blocknum].exit = -1;
		blocks[blocknum].next1 = NONBLK;
		blocks[blocknum].next2 = NONBLK;
		return blocknum++;
	}
	curblk = blocknum;
	blocknum++;
	blocks[curblk].entrance = pos;
	blocks[curblk].addpre(preblk);
	pos2blk[pos] = curblk;//pos一定是entrance，会导致for循环无法执行
	def_use_cal(curblk, pos);
	for (i = pos + 1; !is_entrance(i); i++) {
		pos2blk[i] = curblk;
		def_use_cal(curblk, i);
	}
	blocks[curblk].exit = i - 1;//
	if (midcodes[i - 1].op == BZ || midcodes[i - 1].op == BNZ) {
		blocks[curblk].next1 = gen_block(i, curblk);
		blocks[curblk].next2 = gen_block(label2pos[midcodes[i - 1].op1], curblk);
	}
	else if (midcodes[i - 1].op == GOTO)
		blocks[curblk].next1 = gen_block(label2pos[midcodes[i - 1].op1], curblk);
	else if (midcodes[i - 1].op == RET || midcodes[i - 1].op == EXIT)
		blocks[curblk].next1 = gen_block(-1, curblk);
	else blocks[curblk].next1 = gen_block(i, curblk);
	return curblk;
}

bool is_set_equal(bool* a, bool* b) {
	for (int i = 0; i < TAB_MAX; i++) {
		if (a[i] != b[i]) {
			return false;
		}
	}
	return true;
}
void set_diff(bool* a, bool* b, bool* result) {
	for (int i = 0; i < TAB_MAX; i++) {
		if (a[i] && b[i])
			result[i] = false;
		else result[i] = a[i];
	}
}
void set_union(bool* a, bool* b, bool* result) {
	for (int i = 0; i < TAB_MAX; i++) {
		result[i] = a[i] || b[i];
	}
}
void set_copy(bool* dst, bool* src) {
	for (int i = 0; i < TAB_MAX; i++) {
		dst[i] = src[i];
	}
}
void flush_graph::in_out_cal() {
	bool temp[TAB_MAX], flag = true, con;
	int i;
	while (flag) {
		flag = false;
		for (i = 0; i < blocknum; i++) {
			if (blocks[i].next2 != NONBLK) {
				set_union(blocks[blocks[i].next1].in, blocks[blocks[i].next2].in, blocks[i].out);
			}
			else if (blocks[i].next1 != NONBLK) {
				set_copy(blocks[i].out, blocks[blocks[i].next1].in);
			}
			set_diff(blocks[i].out, blocks[i].def, temp);
			set_union(temp, blocks[i].use, temp);
			if (!is_set_equal(temp, blocks[i].in)) {
				flag = true;
				set_copy(blocks[i].in, temp);
			}
		}
	}
	//将分配了$a1~$a3寄存器的函数参数踢出in、out集合，不参与s寄存器分配
	for (int b = 0; b < blocknum; b++) {
		for (int i = 0; i < MAX_REG_PARA(function); i++) {
			blocks[b].in[i] = false;
			blocks[b].out[i] = false;
		}
	}
}

bool conflict_graph[TAB_MAX][TAB_MAX];
bool available_index[TAB_MAX];
bool vardic[TAB_MAX];
stack<int> vertexs;
int degrees[TAB_MAX];
void remove_vertex(int number) {
	degrees[number] = 0;
	for (int j = 0; j < TAB_MAX; j++) {
		if (conflict_graph[number][j])
			degrees[j]--;
	}
	available_index[number] = false;
	vertexs.push(number);
}

void flush_graph::global_var_cal() {
#define varname(x) funcname2tab(function).ele(x)->name
	//初始化
	for (int i = 0; i < TAB_MAX; i++) {
		for (int j = 0; j < TAB_MAX; j++)
			conflict_graph[i][j] = false;
	}
	for (int j = 0; j < TAB_MAX; j++)
		available_index[j] = false;
	//构建冲突图
	//默认in集合内冲突
	for (int i = 0; i < blocknum; i++) {//遍历基本块
		for (int j = 0; j < TAB_MAX; j++) {//遍历变量
			if (blocks[i].in[j]) {
				global_var.insert(varname(j));
				for (int k = j + 1; k < TAB_MAX; k++) {
					if (blocks[i].in[k]) {
						conflict_graph[j][k] = true;
						conflict_graph[k][j] = true;
					}
				}
			}
		}
	}
	//def内每个变量和in集合冲突
	for (int i = 0; i < blocknum; i++) {//遍历基本块
		for (int j = 0; j < TAB_MAX; j++) {//遍历变量
			if (blocks[i].def[j] && j >= MAX_REG_PARA(function)) {
				global_var.insert(varname(j));
				for (int k = 0; k < TAB_MAX; k++) {
					if (blocks[i].in[k] && k != j) {
						conflict_graph[j][k] = true;
						conflict_graph[k][j] = true;
					}
				}
			}
		}
	}
	//登记待分配块全局变量
	for (int i = 0; i < TAB_MAX; i++) {
		if (global_var.find(varname(i)) != global_var.end()) {
			available_index[i] = true;
			vardic[i] = true;
		}
	}
	//计算度数
	for (int i = 0; i < TAB_MAX; i++) {
		if (vardic[i]) {
			int degree = 0;
			for (int j = 0; j < TAB_MAX; j++)
				degree += conflict_graph[i][j];
			degrees[i] = degree;
		}
	}
	//按算法移走节点
	bool loop_continue = false;
	do {
		loop_continue = false;
		bool flag = false;
		do {
			flag = false;
			for (int i = 0; i < TAB_MAX; i++) {//找到第一个连接边数目小于SREG_NUM的节点
				if (available_index[i] && degrees[i] < SREG_NUM) {
					flag = true;
					remove_vertex(i);
				}
			}
		} while (flag);
		for (int i = 0; i < TAB_MAX; i++) {
			if (available_index[i]) {
				loop_continue = true;
				var2sreg[varname(i)] = -1;
				degrees[i] = 0;
				for (int j = 0; j < TAB_MAX; j++) {
					if (conflict_graph[i][j])
						degrees[j]--;
				}
				available_index[i] = false;
				break;
			}
		}
	} while (loop_continue);
	//着色
	while (!vertexs.empty()) {
		int varnum = vertexs.top();
		for (int color = 0; color < 8; color++) {
			//判断能否按照color着色
			bool colorable = true;
			for (int j = 0; j < TAB_MAX; j++) {
				if (vardic[j] && conflict_graph[varnum][j] && var2sreg.find(varname(j)) != var2sreg.end() && var2sreg[varname(j)] == color) {
					colorable = false;
					break;
				}
			}
			if (colorable) {
				var2sreg[varname(varnum)] = color;
				break;
			}
			else continue;
		}
		vertexs.pop();
	}
	//把剩余寄存器标记为不分配
	set<string>::iterator iter = global_var.begin();
	while (iter != global_var.end()) {
		if (var2sreg.find(*iter) == var2sreg.end())
			var2sreg[*iter] = -1;
		iter++;
	}
	
	//类似引用计数的分配方案，把跨块变量分配全局寄存器
	//for (int i = 0; i < blocknum; i++) {
	//	for (int j = 0; j < TAB_MAX; j++) {
	//		if (blocks[i].in[j]) {
	//			global_var.insert(symtabs[GTAB.ele(function)->addr].ele(j)->name);
	//			alloc_sreg(symtabs[GTAB.ele(function)->addr].ele(j)->name);
	//		}
	//	}
	//}

}

flush_graph graphs[TAB_MAX];
int graph_ptr = 0;

void init_block() {
	int blockptr = 0;
	qtnry_num = qtnry_ptr;

	for (int i = 0; i < qtnry_num; i++) {
		if (midcodes[i].op == SET)
			label2pos[midcodes[i].op1] = i;
	}
	for (int i = 0; i < qtnry_num; i++) {
		if (midcodes[i].op == SET && IS_FUN_LABEL(midcodes[i].op1)) {
			graphs[graph_ptr].function = midcodes[i].op1;
			graphs[graph_ptr].gen_block(i, NONBLK);
			graphs[graph_ptr].in_out_cal();
			graphs[graph_ptr].global_var_cal();
			graph_ptr++;
		}
	}
	return;
}

void analyse_main() {
	init_block();

	return;
}