#include <stdio.h>

#define N 8
#define WPAWN 'g'
#define WKING 'G'
#define BPAWN 'b'
#define BKING 'B'

#ifndef LEAF_DEPTH
#define LEAF_DEPTH 8
#endif
#define STK_SIZE (LEAF_DEPTH + 1)

struct position {
	char board[32];
	int nc;
	char *child_ptr;
};

struct board_position {
	char board[8][8];
};

struct node {
	struct board_position pos;
	int k;
	int l;
	int nc;
	int it;
	char child[4];
};
int leftUp(char pos[][N], int i, int j) 
{
	if (pos[i][j] == BPAWN || i <= 0 || j <= 0) {
		return 0;
	}

	if (pos[i - 1][j - 1] == '-') {
		pos[i - 1][j - 1] = pos[i][j];
		pos[i][j] = '-';
		if (pos[i - 1][j - 1] == WPAWN && i - 1 == 0) {
			pos[i - 1][j - 1] = WKING;
		}
							
		return 1;
	}
	
	return 0;
}

int rightUp(char pos[][N], int i, int j) 
{
	if (pos[i][j] == BPAWN || i <= 0 || j >= N - 1) {
		return 0;
	}
	if (pos[i - 1][j + 1] == '-') {
		pos[i - 1][j + 1] = pos[i][j];
		pos[i][j] = '-';	
		if (pos[i - 1][j + 1] == WPAWN && i - 1 == 0) {
			pos[i - 1][j + 1] = WKING;
		}

		return 1;
	}
	
	return 0;
}

int leftDown(char pos[][N], int i, int j) 
{
	if (pos[i][j] == WPAWN || i >= N - 1 || j <= 0) {
		return 0;
	}
	if (pos[i + 1][j - 1] == '-') {
		pos[i + 1][j - 1] = pos[i][j];
		pos[i][j] = '-';
		if (pos[i + 1][j - 1] == BPAWN && i + 1 == N - 1) {
			pos[i + 1][j - 1] = BKING;
		}

		return 1;
	}

	return 0;
}

int rightDown(char pos[][N], int i, int j) 
{
	if (pos[i][j] == WPAWN || i >= N - 1 || j >= N - 1) {
		return 0;
	}
	if (pos[i + 1][j + 1] == '-') {
		pos[i + 1][j + 1] = pos[i][j];
		pos[i][j] = '-';
		if (pos[i + 1][j + 1] == BPAWN && i + 1 == N - 1) {
			pos[i + 1][j + 1] = BKING;
		}

		return 1;
	}

	return 0;
}

int leftJumpUp(char pos[][N], int turn, int index[2]) 
{
	int flag;
	int i = index[0];
	int j = index[1];

	if (i <= 1 || j <= 1) {
		return 0;
	}

	flag = 0;
	if (turn) {
		if ((pos[i - 1][j - 1] == WPAWN || pos[i - 1][j - 1] == WKING) && pos[i - 2][j - 2] == '-') {
			flag = 1;
		}
	} else {
		if ((pos[i - 1][j - 1] == BPAWN || pos[i - 1][j - 1] == BKING) && pos[i - 2][j - 2] == '-') {
			flag = 1;
		}
	}
	if (flag) {
		pos[i - 2][j - 2] = pos[i][j];
		if (turn) {
			if (pos[i - 2][j - 2] == BPAWN && i - 2 == N - 1) {
				pos[i - 2][j - 2] = BKING;
			}
		} else {
			if (pos[i - 2][j - 2] == WPAWN && i - 2 == 0) {
				pos[i - 2][j - 2] = WKING;
			}
		}
		pos[i - 1][j - 1] = '-';
		pos[i][j] = '-';
		index[0] = i - 2;
		index[1] = j - 2;

		return 1;
	}	

	return 0;
}

int rightJumpUp(char pos[][N], int turn, int index[2]) 
{
	int flag;
	int i = index[0];
	int j = index[1];

	if (i <= 1 || j >= N - 2) {
		return 0;
	}

	flag = 0;
	if (turn) {
		if (((pos[i - 1][j + 1] == WPAWN) || (pos[i - 1][j + 1] == WKING)) && pos[i - 2][j + 2] == '-') {
			flag = 1;
		}
	} else {
		if (((pos[i - 1][j + 1] == BPAWN) || (pos[i - 1][j + 1] == BKING)) && pos[i - 2][j + 2] == '-') {
			flag = 1;
		}
	}
	if (flag) {
		pos[i - 2][j + 2] = pos[i][j];
		if (turn) {
			if (pos[i - 2][j + 2] == BPAWN && i - 2 == N - 1) {
				pos[i - 2][j + 2] = BKING;
			}
		} else {
			if (pos[i - 2][j + 2] == WPAWN && i - 2 == 0) {
				pos[i - 2][j + 2] = WKING;
			}
		}
		pos[i - 1][j + 1] = '-';
		pos[i][j] = '-';
		index[0] = i - 2;
		index[1] = j + 2;

		return 1;
	}	

	return 0;
}

int leftJumpDown(char pos[][N], int turn, int index[2]) 
{
	int flag;
	int i = index[0];
	int j = index[1];

	if (i >= N - 2 || j <= 1) {
		return 0;
	}

	flag = 0;
	if (turn) {
		if (((pos[i + 1][j - 1] == WPAWN) || (pos[i + 1][j - 1] == WKING)) && pos[i + 2][j - 2] == '-') {
			flag = 1;
		}
	} else {
		if (((pos[i + 1][j - 1] == BPAWN) || (pos[i + 1][j - 1] == BKING)) && pos[i + 2][j - 2] == '-') {
			flag = 1;
		}
	 }
	if (flag) {
		pos[i + 2][j - 2] = pos[i][j];
		if (turn) {
			if (pos[i + 2][j - 2] == BPAWN && i + 2 == N - 1) {
				pos[i + 2][j - 2] = BKING;
			}
		} else {
			if (pos[i + 2][j - 2] == WPAWN && i + 2 == 0) {
				pos[i + 2][j - 2] = WKING;
			}
		}
		pos[i + 1][j - 1] = '-';
		pos[i][j] = '-';
		index[0] = i + 2;
		index[1] = j - 2;

		return 1;
	}

	return 0;
}

int rightJumpDown(char pos[][N], int turn, int index[2]) 
{
	int flag;
	int i = index[0];
	int j = index[1];

	if (i >= N - 2 || j >= N - 2) {
		return 0;
	}

	flag = 0;
	if (turn) {
		if ((pos[i + 1][j + 1] == WPAWN || pos[i + 1][j + 1] == WKING) && pos[i + 2][j + 2] == '-') {
			flag = 1;
		}
	} else {
		if ((pos[i + 1][j + 1] == BPAWN || pos[i + 1][j + 1] == BKING) && pos[i + 2][j + 2] == '-') {
			flag = 1;	
		}
	}
	if (flag) {
		pos[i + 2][j + 2] = pos[i][j];
		if (turn) {
			if (pos[i + 2][j + 2] == BPAWN && i + 2 == N - 1) {
				pos[i + 2][j + 2] = BKING;
			}
		} else {
			if (pos[i + 2][j + 2] == WPAWN && i + 2 == 0) {
				pos[i + 2][j + 2] = WKING;
			}
		}
		pos[i + 1][j + 1] = '-';
		pos[i][j] = '-';
		index[0] = i + 2;
		index[1] = j + 2;	

		return 1;
	}

	return 0;
}

void print(char a[][N]) {
	int i;
	int j;

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf("%c ", a[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

void convert_into_2D(char a[32], char b[][N])
{
	int i;
	int j;
	int k;

	k = 0;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0)) {
				b[i][j] = '-';
			} else {
				b[i][j] = a[k++];
			}
		}
	}
}

void convert_into_1D(char a[][N], char b[32])
{
	int i;
	int j;
	int k;

	k = 0;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if ((i % 2 == 0 && j % 2 != 0) || (i % 2 != 0 && j % 2 == 0)) {
				b[k++] = a[i][j];
			}
		}
	}
}

void insert_into_array(struct board_position pos, int nc, char *child_ptr)
{
	char child[32];
	int x;
	int y;

	convert_into_1D(pos.board, child);

	y = 0;
	for (x = nc * 32; x < (nc * 32) + 32; x++) {
		*(child_ptr + x) = child[y++];
	}
}

void init_new_node(struct board_position pos, int k, int l, struct node *leaf)
{
	leaf->pos = pos;
	leaf->k = k;
	leaf->l = l;
	leaf->nc = 4;
	leaf->it = 0;
	leaf->child[0] = '0';
	leaf->child[1] = '1';
	leaf->child[2] = '2';
	leaf->child[3] = '3';
}

void stacks(struct board_position pos, int k, int l, int turn, int *nc, char *child_ptr)
{
	struct node root;
	struct node leaf;
	struct node ply_node;
	struct node stk[STK_SIZE];

	struct board_position p;
	int i;
	int j;
	int v = -1;
	int flag;
	int ply = -1;

	init_new_node(pos, k, l, &root);
	ply++;
	stk[ply] = root;
	
	while (ply != -1) {
		if (ply < LEAF_DEPTH) {
			ply_node = stk[ply];
			
			if (ply_node.it < ply_node.nc) {
				int index[2];
				
				ply_node.it++;
				
				flag = 0;
				index[0] = ply_node.k;
				index[1] = ply_node.l;
				i = index[0];
				j = index[1];
				v = ply_node.child[ply_node.it - 1];
				p = ply_node.pos;
				
				if (v == '0' && p.board[i][j] != WPAWN) {
					flag = leftJumpDown(p.board, turn, index);
				} else if (v == '1' && p.board[i][j] != WPAWN) {
					flag = rightJumpDown(p.board, turn, index);
				} else if (v == '2' && p.board[i][j] != BPAWN) {
					flag = leftJumpUp(p.board, turn, index);
				} else if (v == '3' && p.board[i][j] != BPAWN) {
					flag = rightJumpUp(p.board, turn, index);
				}

				if (flag) {
					init_new_node(p, index[0], index[1], &leaf);
					
					insert_into_array(p, *nc, child_ptr);
					(*nc)++;

					stk[ply] = ply_node;
					ply++;
					stk[ply] = leaf;
				} else {
					stk[ply] = ply_node;
				}
			} else {
				ply--;
			}
		} else {
			ply--;
			ply_node = stk[ply];
		}
	}
}
void individualMove(struct board_position pos, int i, int j, int turn, int *nc, char *child_ptr) 
{
	struct board_position p;
	
	if (pos.board[i][j] != WPAWN) {
		p = pos;
		if (leftDown(p.board, i, j)) {
			insert_into_array(p, *nc, child_ptr);
			(*nc)++;
		}
		p = pos;
		if (rightDown(p.board, i, j)) {
			insert_into_array(p, *nc, child_ptr);
			(*nc)++;
		}
	}

	if (pos.board[i][j] != BPAWN) {
		p = pos;
		if (leftUp(p.board, i, j)) {
			insert_into_array(p, *nc, child_ptr);
			(*nc)++;
		}
		p = pos;
		if (rightUp(p.board, i, j)) {
			insert_into_array(p, *nc, child_ptr);
			(*nc)++;
		}
	}

	stacks(pos, i, j, turn, nc, child_ptr);
}

void generate_moves(char board[32], int turn, int *nc, char *child_ptr)
{
	int flag;
	int i;
	int j;
	char p[N][N];
	struct board_position pos;

	convert_into_2D(board, p);
	flag = 1;

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (turn && flag) {
				if (p[i][j] == BPAWN || p[i][j] == BKING) {
					flag = 0;
				}
			} else if (flag) {
				if (p[i][j] == WPAWN || p[i][j] == WKING) {
					flag = 0;
				}
			}
			pos.board[i][j] = p[i][j];
		}
	}

	if (flag) {
		return;
	}

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (turn) {
				if (pos.board[i][j] == BPAWN || pos.board[i][j] == BKING) {
					individualMove(pos, i, j, turn, nc, child_ptr);
				}
			} else {
				if (pos.board[i][j] == WPAWN || pos.board[i][j] == WKING) {				
					individualMove(pos, i, j, turn, nc, child_ptr);
				}
			}
		}
	}
}

void process(char *child_ptr, int nc) {
	int i;
	int j;
	char a[32];
	char b[N][N];

	j = 0;
	for (i = 0; i < nc * 32; i++) {
		a[j++] = *(child_ptr + i);
		if (j % 32 == 0) {
			j = 0;
			convert_into_2D(a, b);
			print(b);
		}
	}
}

void init_new_child(struct position pos, struct position *new_pos, int turn, int i)  
{
	int j;

	new_pos->nc = 0;

	for (j = 0; j < 32; j++) {
		new_pos->board[j] = pos.child_ptr[(i * 32) + j];
	}

	generate_moves(new_pos->board, (turn + 1) % 2, &(new_pos->nc), new_pos->child_ptr);
}
