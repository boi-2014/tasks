#include "coprobber.h"
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

typedef tuple<int, int, int> Position;

const int COP = 0, ROBBER = 1;
vector<int> Neighbours[MAX_N];
int LeftToWin[2][MAX_N][MAX_N];
int NextPos[MAX_N][MAX_N];

int start(int N, bool A[MAX_N][MAX_N]) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (A[i][j])
				Neighbours[i].push_back(j);

	for (int c = 0; c < N; c++)
		for (int r = 0; r < N; r++)
			if (c != r) {
				LeftToWin[COP][c][r] = 1;
				LeftToWin[ROBBER][c][r] = Neighbours[r].size();
			}

	queue<Position> q;
	for (int i = 0; i < N; i++) {
		q.push(Position(COP, i, i));
		q.push(Position(ROBBER, i, i));
	}
	
	int leftUntilWin = 2 * N * N;
	while (!q.empty()) {
		int t, c, r;
		tie(t, c, r) = q.front();
		q.pop();
		leftUntilWin--;
		if (t == COP) {
			for (int n : Neighbours[r])
				if (LeftToWin[ROBBER][c][n] > 0
						&& (--LeftToWin[ROBBER][c][n]) == 0)
					q.push(Position(ROBBER, c, n));
		} else if (t == ROBBER) {
			for (int n : Neighbours[c])
				if (LeftToWin[COP][n][r] > 0
						&& (--LeftToWin[COP][n][r]) == 0) {
					q.push(Position(COP, n, r));
					NextPos[n][r] = c;
				}
			if (LeftToWin[COP][c][r] > 0
					&& (--LeftToWin[COP][c][r]) == 0) {
				q.push(Position(COP, c, r));
				NextPos[c][r] = c;
			}
		}
	}
	
	return leftUntilWin == 0 ? 0 : -1;
}

int cop = 0;

int nextMove(int robber) {
	cop = NextPos[cop][robber];
	return cop;
}
