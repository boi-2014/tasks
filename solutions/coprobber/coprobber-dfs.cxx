#include <algorithm>
#include <cstdio>
#include "coprobber.h"

using namespace std;

int N;
bool (*A)[MAX_N];
const int COP = 0, ROBBER = 1;
int Cache[2][MAX_N][MAX_N];
bool StateStack[2][MAX_N][MAX_N];

// Returns -1 if impossible to win
int bestMove(int turn, int cop, int robber) {
	if (cop == robber)
		return turn == COP ? N : -1;
	int &c = Cache[turn][cop][robber];
	return c != -2 ? c : (c = [=]{
		bool &ss = StateStack[turn][cop][robber];
		if (ss) {
			printf("(%d, %d, %d): loop\n", turn, cop, robber);
			return turn == ROBBER ? N : -1;
		}
		ss = true;
		printf("<\n");
		int move = -1;
		if (turn == COP)
			for (int i = 0; i < N && move == -1; i++)
				if ((A[cop][i] || cop == i) && bestMove(ROBBER, i, robber) == -1)
					move = i;
		else
			for (int i = 0; i < N && move == -1; i++)
				if (A[robber][i] && bestMove(COP, cop, i) == -1)
					move = i;
		ss = false;
		printf("> bestMove(%d, %d, %d) = %d\n", turn, cop, robber, move);
		return move;
	}());
}

int start(int N, bool A[MAX_N][MAX_N]) {
	::N = N; ::A = A;
	fill(Cache[0][0], Cache[2][0], -2);
	bool can_catch = true;
	for (int i = 1; i < N; i++)
		can_catch &= bestMove(COP, 0, i) != -1;
	return can_catch ? 0 : -1;
}

int cop = 0;

int nextMove(int robber) {
	cop = bestMove(COP, cop, robber);
	return cop;
}
