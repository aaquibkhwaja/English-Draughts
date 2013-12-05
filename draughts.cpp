#include <iostream>
#include "score.c"

#define ALPHA -100000
#define BETA 100000

using namespace std;

struct tree {
	char pos[32];
	int turn;
	int nc;
	int scr;
	int iter;
	tree *child;
};

/*ALPHA-BETA*/
int alphabeta(tree **ptr_root, int alpha, int beta, string player, int &vn)
{
	vn++;
	tree *root;

	root = *ptr_root;

        if (root->child->child == NULL) {
                return root->scr;
        }

       	for (int i = 0; i < root->nc; i++) {
		tree *p;

		p = &(root->child[i]);
		if (player == "max") {
                     	alpha = max(alpha, alphabeta(&p, alpha, beta, "min", vn));
			root->scr = alpha;
		} else {
                       	beta = min(beta, alphabeta(&p, alpha, beta, "max", vn));
			root->scr = beta;
		}
                if (beta <= alpha) {
                        break;
                }
	}

	*ptr_root = root;
	
	if (player == "max") {
		return alpha;
	} else {
		return beta;
	}
}

/*score_and_grow_leaf*/
void score_and_grow_leaf(tree **rt, int c)
{
	tree *root;
	int nc;
	int ctr;
	char children[6400];

	root = *rt;
	nc = 0;

	generate_moves(root->pos, root->turn, &nc, children);
	root->nc = nc;

	tree *child = new tree[nc];
	ctr = 0;

	for (int i = 0; i < (nc * 32); i = i + 32) {
		int in;
		char arr[32];

		in = -1;
		for (int j = i; j < (i + 32); j++) {
			in++;
			arr[in] = children[j];
		}
		for (int k = 0; k < 32; k++) {
			child[ctr].pos[k] = arr[k];
		}	
		child[ctr].turn = (root->turn + 1) % 2;
		child[ctr].nc = 0;
		if (c == 2) {
			child[ctr].scr = find_score(child[ctr].pos, child[ctr].turn);
		} else {
			child[ctr].scr = 0;
		}
		child[ctr].iter = 0;
		child[ctr].child = NULL;
		ctr++;
	}
	root->child = child;
	*rt = root;
}

/*score_and_grow_tree*/
void score_and_grow_tree(tree **rt, int &c)
{
	tree *root;
	int nc;
	int ctr;
	char children[6400];

	root = *rt;
	nc = 0;
	
	if (c == 0) {
		int ab;
		int vn; // visited nodes

		ab = 0;
		vn = 0;
		ab = alphabeta(&root, ALPHA, BETA, "max", vn);
		root->scr = ab;
		*rt = root;
		c = vn;
		
		return;
	}

	if (root->child == NULL) {
		score_and_grow_leaf(&root, c);
	} else {
		while (root->iter < root->nc) {
			tree *temp = root->child + root->iter;
			score_and_grow_tree(&temp, c);
			root->iter++;
		}
		root->iter = 0;
	}
}

/*PRINTS THE WHOLE TREE*/
void print_tree(tree *root, int depth)
{
	for (int i = 0; i < root->nc; i++) {
		cout <<"\nDepth - " << depth << endl;
		cout << "child no. " << i << endl;
		tree *t;

		t = root->child + i;

		for (int j = 0; j < 32; j++) {
			cout << t->pos[j];
		}
		cout << endl;
		if (t->child != NULL) {
			print_tree(t, depth + 1);
		}
	}
	cout << endl << endl;
}

/*CALCULATES TOTAL NUMBER OF NODES*/
void total_nodes(tree *root, int *ctr)
{
	for (int i = 0; i < root->nc; i++) {
		(*ctr)++;
		tree *t;

		t = root->child + i;

		if (t->child != NULL) {
			total_nodes(t, ctr);
		}
	}
}

/*PRINTS CHILDREN OF THE POSITION PASSED AS ARGUMENT*/
void print_child(tree *root)
{
	int c = 0;

	cout << "chldr: ";
	for (int i = 0; i < root->nc; i++) {
		tree *t;

		t = root->child + i;

		if (c != 0) {
			cout << "       ";
		}

		for (int j = 0; j < 32; j++) {
			cout << t->pos[j];
		}
		cout << endl;
		c++;
	}
}

void display(tree *root, int v)
{
	int tn;
	int vn;

	tn = 1;
	vn = v;

	cout << "input: ";
	for (int i = 0; i < 32; i++) {
		cout << root->pos[i] << " ";
	}
	cout << endl << "turn : ";
	cout << root->turn << endl;
	
	cout << "pos  : ";
	for (int j = 0; j < root->nc; j++) {
		tree *t;
		t = root->child + j;
		if (t->scr == root->scr) {
			for (int i = 0; i < 32; i++) {
				cout << t->pos[i];
			}
			break;
		}
	}
	cout << endl;
	cout << "score: " << root->scr << endl;
	cout << "nc   : " << root->nc << endl;
	print_child(root);		/*Prints children of the position passed as argument*/
	total_nodes(root, &tn);		/*Finds total no. of nodes*/
	cout << "#nd  : " << tn << endl;
	cout << "ab_nd: " << vn << endl;
	cout << "%" << "nd  : " << (float)vn/(float)tn * 100 << endl;
}

int main()
{
	tree *root;
	int turn;
	char ch;
	int ctr;
	int ab;
	int vn;
	int flg;
	
	root = new tree;
	ab = 0;
	vn = 0;
		
	for (int i = 0; i < 32; i++) {
		cin >> ch;
		root->pos[i] = ch;
	}

	cin >> turn;

	root->turn = turn;
	root->nc = 0;
	root->scr = 0;
	root->iter = 0;
	root->child = NULL;

	cin >> ctr;

	flg = 0;

	while (ctr > -1) {
		root->iter = 0;
		score_and_grow_tree(&root, ctr);
		if (flg == 1) {
			vn = ctr;
			ctr = 0;
		}
		ctr--;
		
		if (ctr == 0) {
			flg = 1;
		}
	}

	display(root, vn);
	//print_tree(root, 0);		/*Prints whole tree*/
	
	return 0;
}
