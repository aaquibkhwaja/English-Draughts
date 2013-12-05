#include <stdio.h>
#include <stdlib.h>
#include "move_generation.c"
#include "evaluation.c"

#ifndef LEAF_DEPTH
#define LEAF_DEPTH 8
#endif
#define INF 100000

struct checkers_t {
	struct position pos;
	int iter;
	int scr;
	int beta;
	int alpha;
};

/*CREATION OF NEW NODE FOR STACK*/
void new_node(struct position pos, struct checkers_t *leaf_node)
{
	leaf_node->pos = pos;
	leaf_node->iter = 0;
	leaf_node->beta = INF;
	leaf_node->alpha = -INF;
	leaf_node->scr = 0;
}

/*TREE TRAVERSAL*/
int stack_alpha_beta(struct position pos, int turn)
{
	char child[LEAF_DEPTH][6400];
	char max_depth_reached;
	int best_score;
	int alpha;
	int beta;
	int ply;
	struct checkers_t root;
	struct checkers_t curr_node;
	struct checkers_t prev_node;
	struct checkers_t leaf_node;
	struct checkers_t glb_stk[LEAF_DEPTH + 1];

	ply = 0;
	alpha = -INF;
	beta = INF;
	best_score = -INF;

	new_node(pos, &root);
	glb_stk[ply] = root;
	ply++;

	/*printf("Depth - %-2d             best_scr - %7d  alpha - %7d  beta - %7d\n", LEAF_DEPTH - ply + 1, best_score, alpha, beta);*/

	if (LEAF_DEPTH == 0) {
		if (root.pos.nc == 0) {
			best_score = -INF;
		} else {
			best_score = evaluate(root.pos.board, turn);
		}
	}
	while (ply > 0) {
		max_depth_reached = 1;
		if (ply < LEAF_DEPTH + 1) {
			curr_node = glb_stk[ply-1];
			max_depth_reached = 0;
			if (curr_node.iter < curr_node.pos.nc) {
				struct position p;
				int new_turn;

				/*printf("Depth - %-2d  Iter - %-2d  best_scr - %7d  alpha - %7d  beta - %7d\n", LEAF_DEPTH - ply + 1, curr_node.iter, best_score, curr_node.alpha, curr_node.beta);*/

				p.child_ptr = child[ply - 1];
				curr_node.iter++;
				new_turn = (ply + turn + 1) % 2;
				init_new_child(curr_node.pos, &p, new_turn, curr_node.iter - 1);
				new_node(p, &leaf_node);
				
				if (leaf_node.pos.nc == 0) {
					if (ply % 2 == 0) {
						leaf_node.scr = -INF;
					} else {
						leaf_node.scr = INF;
					}
				} else if (ply == LEAF_DEPTH) {
					leaf_node.scr = evaluate(p.board, (new_turn + 1) % 2);
				} else {
					leaf_node.alpha = curr_node.alpha;
					leaf_node.beta = curr_node.beta;
					if (ply % 2 != 0) {
						leaf_node.scr = -INF;
					} else {
						leaf_node.scr = INF;
					}
				}

				if (ply % 2 != 0) {
					curr_node.scr = (curr_node.scr > leaf_node.scr) ? curr_node.scr : leaf_node.scr;
				} else {
					curr_node.scr = (curr_node.scr < leaf_node.scr) ? curr_node.scr : leaf_node.scr;
				}

				glb_stk[ply-1] = curr_node;
				ply++;
				glb_stk[ply-1] = leaf_node;

				continue;
			}
		}
		prev_node = glb_stk[ply-1];
		ply--;
		if (ply <= 0) {
			continue;
		}
		curr_node = glb_stk[ply-1];

		if (ply % 2 == 1) {
			if (max_depth_reached) {
				alpha = (prev_node.scr > curr_node.alpha) ? prev_node.scr : curr_node.alpha;
			} else {
				alpha = (prev_node.scr < curr_node.beta) ? prev_node.scr : curr_node.beta;
			}
			curr_node.scr = alpha;
			if (alpha >= curr_node.beta) {
				ply--;
				if (ply == 0) {
					best_score = alpha;
				} else {
					glb_stk[ply-1].scr = curr_node.beta;
				}
			} else {
				curr_node.alpha = alpha;
				glb_stk[ply-1] = curr_node;
				if (ply == 1 && best_score < alpha) {
					best_score = alpha;
				}
			}
		} else {
			if (max_depth_reached) {
				beta = (prev_node.scr < curr_node.beta) ? prev_node.scr : curr_node.beta;
			} else {
				beta = (prev_node.scr > curr_node.alpha) ? prev_node.scr : curr_node.alpha;
			}
			curr_node.scr = beta;
			if (curr_node.alpha >= beta) {
				ply--;
				if (ply != 0) {
					glb_stk[ply-1].scr = curr_node.alpha;
				}
			} else {
				curr_node.beta = beta;
				glb_stk[ply-1] = curr_node;
			}
		}
	}
	return best_score;
}

int find_score(char posi[32], int turn)
{
	struct position pos;
	char child_ptr[6400];
	char arr[32];
	int nc;
	int i;

	nc = 0;

	for (i = 0; i < 32; i++) {
		arr[i] = posi[i];
	}

	generate_moves(arr, turn, &nc, child_ptr);

	for (i = 0; i < 32; i++) {
		pos.board[i] = arr[i];
	}
	pos.nc = nc;
	pos.child_ptr = child_ptr;

	return(stack_alpha_beta(pos, turn));
}

