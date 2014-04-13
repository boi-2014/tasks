#include <cstdio>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

typedef tuple<int, int, int> Position;

const int MAX_N = 500;

const int COP = 0, ROBBER = 1;
vector<int> Neighbours[MAX_N];
int LeftToWin[2][MAX_N][MAX_N];

int N;
bool A[MAX_N][MAX_N];
int TimeToWin[2][MAX_N][MAX_N];
int NextPos[MAX_N][MAX_N];
int StartPos[MAX_N];

bool calcStrategy(int strategy) {
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
						&& (--LeftToWin[ROBBER][c][n]) == 0) {
					q.push(Position(ROBBER, c, n));
					TimeToWin[ROBBER][c][n] = 1 + TimeToWin[t][c][r];
				}
		} else if (t == ROBBER) {
			for (int n : Neighbours[c])
				if (LeftToWin[COP][n][r] > 0
						&& (--LeftToWin[COP][n][r]) == 0) {
					q.push(Position(COP, n, r));
					TimeToWin[COP][n][r] = 1 + TimeToWin[t][c][r];
				}
			if (LeftToWin[COP][c][r] > 0
					&& (--LeftToWin[COP][c][r]) == 0) {
				q.push(Position(COP, c, r));
				TimeToWin[COP][c][r] = 1 + TimeToWin[t][c][r];
			}
		}
	}
	if (leftUntilWin != 0)
		return false;
	
	/*for (int t = 0; t < 2; t++) {
		printf("%d:\n", t);
		for (int c = 0; c < N; c++) {
			for (int r = 0; r < N; r++) {
				printf("%3d", TimeToWin[t][c][r]);
			}
			printf("\n");
		}
	}*/
	
	// Calculate robber starting positions
	// Strategy: maximise chasing time
	for (int c = 0; c < N; c++) {
		int maxTime = -1;
		for (int r = 0; r < N; r++)
			if (TimeToWin[COP][c][r] > maxTime) {
				maxTime = TimeToWin[COP][c][r];
				StartPos[c] = r;
			}
	}
	
	// Calculate robber strategy
	switch (strategy) {
	case 0:
		// Strategy: maximise chasing time
		for (int c = 0; c < N; c++) {
			for (int r = 0; r < N; r++) {
				if (c == r)
					continue;
				int maxTime = -1;
				for (int nr : Neighbours[r])
					if (TimeToWin[COP][c][nr] > maxTime) {
						maxTime = TimeToWin[COP][c][nr];
						NextPos[c][r] = nr;
					}
			}
		}
		break;
	case 1:
		// Alternative strategy: minimise chasing time
		for (int c = 0; c < N; c++) {
			for (int r = 0; r < N; r++) {
				if (c == r)
					continue;
				int minTime = INT_MAX;
				for (int nr : Neighbours[r])
					if (TimeToWin[COP][c][nr] < minTime) {
						minTime = TimeToWin[COP][c][nr];
						NextPos[c][r] = nr;
					}
			}
		}
		break;
	case 2:
		// Random strategy
		srand(time(NULL));
		for (int c = 0; c < N; c++) {
			for (int r = 0; r < N; r++) {
				if (c == r)
					continue;
				NextPos[c][r] = Neighbours[r][rand() % Neighbours[r].size()];
			}
		}
		break;
	}
	
	return true;
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &A[i][j]);
	printf("%d\n", N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (j > 0) putchar(' ');
			putchar(A[i][j] ? '1' : '0');
		}
		printf("\n");
	}
	bool copCanWin = calcStrategy(0);
	printf("%d\n", copCanWin);
	if (copCanWin) {
		for (int c = 0; c < N; c++) {
			for (int r = 0; r < N; r++)
				printf("%d ", NextPos[c][r]);
			printf("%d\n", StartPos[c]);
		}
	}
	return 0;
}
