#include <stdio.h>

struct BOARD {
	char position[32];
	char nc;
	int score;
};

typedef struct BOARD BOARD;

int safe_pieces(char position[32], int turn)
{
	int count;
	int i;

	count = 0;

	if (turn == 1) {
		for (i = 4; i < 29; i = i + 8) {
			if (position[i] == 'b') {
				count = count + 100;
			} else if (position[i] == 'B') {
				count = count + 200;
			}
		}
		for (i = 3; i < 28; i = i + 8) {
			if (position[i] == 'b') {
				count = count + 100;
			} else if (position[i] == 'B') {
				count = count + 200;
			}
		}
	} else if (turn == 0) {
		for (i = 4; i < 29; i = i + 8) {
			if (position[i] == 'g') {
				count = count + 100;
			} else if (position[i] == 'G') {
				count = count + 200;
			}
		}
		for (i = 3; i < 28; i = i + 8) {
			if (position[i] == 'g') {
				count = count + 100;
			} else if (position[i] == 'G') {
				count = count + 200;
			}
		}
	}

	return count;
}

int defender_pieces(char position[32], int turn)
{
	int count;
	int i;

	count = 0;

	if (turn == 1) {
		for (i = 0; i < 8; i++) {
			if (position[i] == 'b') {
				count = count + 100;
			} else if (position[i] == 'B') {
				count = count + 200;
			}
		}
	} else if (turn == 0) {
		for (i = 24; i < 32; i++) {
			if (position[i] == 'g') {
				count = count + 100;
			} else if (position[i] == 'G') {
				count = count + 200;
			}
		}
	}

	return count;
}

int loner_pieces(char position[32], int turn)
{
	int count;
	int i;

	count = 0;

	if (turn == 1) {
		for (i = 0; i < 32; i++) {
			if (position[i] == 'b' || position[i] == 'B') {
				if (i < 4) {
					if (i == 0) {
						if ((position[5] == '-') && (position[4] == '-')) {
							count++;
						}
					} else if (i == 3) {
						if (position[7] == '-') {
							count++;
						}
					} else {
						if ((position[i+4] == '-') && (position[i+5] == '-')) {
							count++;
						}
					}
				} else if (i >= 4 && i < 28) {
					if (i == 4 || i == 12 || i == 20 || i == 11 || i == 19 || i == 27) {
						if ((position[i-4] == '-') && (position[i+4] == '-')) {
							count++;
						}
					} else {
						if ((i >= 5 && i < 8) || (i >= 13 && i < 16) || (i >= 21 && i < 24)) {
							if ((position[i-5] == '-') && (position[i-4] == '-') &&
							    (position[i+3] == '-') && (position[i+4] == '-')) {
								count++;
							}
						} else {
							if ((position[i-3] == '-') && (position[i-4] == '-') &&
							    (position[i+5] == '-') && (position[i+4] == '-')) {
								count++;
							}
						}
					}
				} else if (i >= 28 && i < 32) {
					if (i == 28) {
						if (position[24] == '-') {
							count++;
						}
					} else if (i == 31) {
						if ((position[26] == '-') && (position[27] == '-')) {
							count++;
						}
					} else {
						if ((position[i-5] == '-') && (position[i-4] == '-')) {
							count++;
						}
					}
				}
			}
		}
	} else if (turn == 0) {
		for (i = 0; i < 32; i++) {
			if (position[i] == 'g' || position[i] == 'G') {
				if (i < 4) {
					if (i == 0) {
						if ((position[5] == '-') && (position[4] == '-')) {
							count++;
						}
					} else if (i == 3) {
						if (position[7] == '-') {
							count++;
						}
					} else {
						if ((position[i+4] == '-') && (position[i+5] == '-')) {
							count++;
						}
					}
				} else if (i >= 4 && i < 28) {
					if (i == 4 || i == 12 || i == 20 || i == 11 || i == 19 || i == 27) {
						if ((position[i-4] == '-') && (position[i+4] == '-')) {
							count++;
						}
					} else {
						if ((i >= 5 && i < 8) || (i >= 13 && i < 16) || (i >= 21 && i < 24)) {
							if ((position[i-5] == '-') && (position[i-4] == '-') &&
							    (position[i+3] == '-') && (position[i+4] == '-')) {
								count++;
							}
						} else {
							if ((position[i-3] == '-') && (position[i-4] == '-') &&
							    (position[i+5] == '-') && (position[i+4] == '-')) {
								count++;
							}
						}
					}
				} else if (i >= 28 && i < 32) {
					if (i == 28) {
						if (position[24] == '-') {
							count++;
						}
					} else if (i == 31) {
						if ((position[26] == '-') && (position[27] == '-')) {
							count++;
						}
					} else {
						if ((position[i-5] == '-') && (position[i-4] == '-')) {
							count++;
						}
					}
				}
			}
		}
	}

	return count;
}

int attacking_pieces(char position[32], int turn)
{
	int count;
	int i;

	count = 0;

	if (turn == 1) {
		for (i = 20; i < 32; i++) {
			if (position[i] == 'b') {
				count = count + 100;
			} else if (position[i] == 'B') {
				count = count + 200;
			}
		}
	} else if (turn == 0) {
		for (i = 0; i < 12; i++) {
			if (position[i] == 'g') {
				count = count + 100;
			} else if (position[i] == 'G') {
				count = count + 200;
			}
		}
	}

	return count;
}

int kill_left_up(char pos[8][8], char ch, int i, int j)
{
	if (ch == 'b') {
		return 0;
	}

	if (i < 2 || j < 2) {
		return 0;
	}

	if (ch == 'B') {
		if ((pos[i-1][j-1] == 'g' || pos[i-1][j-1] == 'G') && (pos[i-2][j-2] == '-')) {
			return 1;
		}
	} else if (ch == 'g' || ch == 'G') {
		if ((pos[i-1][j-1] == 'b' || pos[i-1][j-1] == 'B') && (pos[i-2][j-2] == '-')) {
			return 1;
		}
	}

	return 0;
}

int kill_right_up(char pos[8][8], char ch, int i, int j)
{
	if (ch == 'b') {
		return 0;
	}

	if (i < 2 || j > 5) {
		return 0;
	}

	if (ch == 'B') {
		if ((pos[i-1][j+1] == 'g' || pos[i-1][j+1] == 'G') && (pos[i-2][j+2] == '-')) {
			return 1;
		}
	} else if (ch == 'g' || ch == 'G') {
		if ((pos[i-1][j+1] == 'b' || pos[i-1][j+1] == 'B') && (pos[i-2][j+2] == '-')) {
			return 1;
		}
	}

	return 0;
}

int kill_left_down(char pos[8][8], char ch, int i, int j)
{
	if (ch == 'g') {
		return 0;
	}

	if (i > 5 || j < 2) {
		return 0;
	}

	if (ch == 'b' || ch == 'B') {
		if ((pos[i+1][j-1] == 'g' || pos[i+1][j-1] == 'G') && (pos[i+2][j-2] == '-')) {
			return 1;
		}
	} else if (ch == 'G') {
		if ((pos[i+1][j-1] == 'b' || pos[i+1][j-1] == 'B') && (pos[i+2][j-2] == '-')) {
			return 1;
		}
	}

	return 0;
}

int kill_right_down(char pos[8][8], char ch, int i, int j)
{
	if (ch == 'g') {
		return 0;
	}

	if (i > 5 || j > 5) {
		return 0;
	}

	if (ch == 'b' || ch == 'B') {
		if ((pos[i+1][j+1] == 'g' || pos[i+1][j+1] == 'G') && (pos[i+2][j+2] == '-')) {
			return 1;
		}
	} else if (ch == 'G') {
		if ((pos[i+1][j+1] == 'b' || pos[i+1][j+1] == 'B') && (pos[i+2][j+2] == '-')) {
			return 1;
		}
	}

	return 0;
}

int killer_pieces(char position[32], int turn)
{
	char pos[8][8];
	char ch;
	int count;
	int i;
	int j;
	int k;

	k = 0;
	
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0)) {
				pos[i][j] = '-';
			} else {
				pos[i][j] = position[k++];
			}
		}
	}
	count = 0;

	if (turn == 1) {
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				if (pos[i][j] == 'b' || pos[i][j] == 'B') {
					ch = pos[i][j];

					if (kill_left_up(pos, ch, i, j) == 1) {
						count++;
					}
					if (kill_right_up(pos, ch, i, j) == 1) {
						count++;
					}
					if (kill_left_down(pos, ch, i, j) == 1) {
						count++;
					}
					if (kill_right_down(pos, ch, i, j) == 1) {
						count++;
					}
				}
			}
		}
	} else if (turn == 0) {
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				if (pos[i][j] == 'g' || pos[i][j] == 'G') {
					ch = pos[i][j];

					if (kill_left_up(pos, ch, i, j) == 1) {
						count++;
					}
					if (kill_right_up(pos, ch, i, j) == 1) {
						count++;
					}
					if (kill_left_down(pos, ch, i, j) == 1) {
						count++;
					}
					if (kill_right_down(pos, ch, i, j) == 1) {
						count++;
					}
				}
			}
		}
	}

	return count;
}

int aggr_distance(char position[32], int turn)
{
	int dist;
	int i;

	dist = 0;
	
	if (turn == 1) {
		for (i = 16; i < 28; i++) {
			if (position[i] == 'b') {
				if (i < 20) {
					dist = dist + 3;
				} else if (i >= 20 && i < 24) {
					dist = dist + 2;
				} else if (i >= 24 && i < 28) {
					dist = dist + 1;
				}
			}
		}
	} else if (turn == 0) {
		for (i = 4; i < 16; i++) {
			if (position[i] == 'g') {
				if (i < 8) {
					dist = dist + 1;
				} else if (i >= 8 && i < 12) {
					dist = dist + 2;
				} else if (i >= 12 && i < 16) {
					dist = dist + 3;
				}
			}
		}
	}

	return dist;
}

int unoccupied_fields(char position[32], int turn)
{
	int count;
	int i;

	count = 0;

	if (turn == 1) {
		for (i = 28; i < 32; i++) {
			if (position[i] == '-') {
				count++;
			}
		}
	} else if (turn == 0) {
		for (i = 0; i < 4; i++) {
			if (position[i] == '-') {
				count++;
			}
		}
	}

	return count;
}

int evaluate(char position[32], int turn)     /*Evaluation Function*/
{
	int safe;          		  /* Pieces adjacent to board edge */
	int loner;             		  /* Pieces with no other adjacent piece */
	int defender;         		  /* Pieces in 2 lowermost rows */
	int attacking;        		  /* Pieces in 3 topmost rows */
	int killer;        		  /* Pieces who can kill an opponent */
	/*int unocc_fields_promotion_line;  Unoccupied fields on the promotion line 
	int aggr_dist_from_promotion;    Distance from the promotion row(of the pieces in the opposition half) */
	int score;

	safe = safe_pieces(position, turn);
	loner = loner_pieces(position, turn) * 100;
	defender = defender_pieces(position, turn);
	attacking = attacking_pieces(position, turn);
	killer = killer_pieces(position, turn) * 100;
	/*unocc_fields_promotion_line = unoccupied_fields(position, turn) * 100;
	aggr_dist_from_promotion = aggr_distance(position, turn) * 100;*/

	/*printf("%d %d %d %d %d %d %d\n", safe, loner, defender, attacking, killer, unocc_fields_promotion_line, aggr_dist_from_promotion); */

	score = safe + loner + defender + attacking + killer /*+ unocc_fields_promotion_line + aggr_dist_from_promotion*/;

	return score;
}
/*
void getBoardPosition(char position[32])
{
	int i;

	for (i = 0; i < 32; i++) {
		scanf("%c ", &position[i]);
	}
}

int main()
{
	BOARD board;
	int turn;

	getBoardPosition(board.position);
	scanf("%d", &turn);

	board.score = evaluate(board.position, turn);

	printf("\nScore = %d\n", board.score);

	return 0;
}*/
