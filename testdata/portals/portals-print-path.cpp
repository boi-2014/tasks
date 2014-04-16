#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

template <class T, int N>
struct ar {
	T v[N];
	T& operator[](int x) { return v[x]; }
};

void get_cake(int R, int C, char** M) {
	const int X[4] = {-1, 1, 0, 0};
	const int Y[4] = {0, 0, -1, 1};

	vector<string> map(R+2, string(C+2, '#'));
	for (int i = 0; i < R; ++i)
		copy(M[i], M[i] + C, map[i+1].begin()+1);
	R += 2;
	C += 2;

	// Indices of start and end positions.
	int startx, starty, endx, endy;
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			if (map[i][j] == 'S')
				starty = i, startx = j;
			if (map[i][j] == 'C')
				endy = i, endx = j;
		}
	}

	// Find distances to the nearest wall.
	vector<vector<int> > distToWall(R, vector<int>(C, -1));
	{
		queue<pair<int, int> > q;
		for (int i = 0; i < R; ++i) {
			for (int j = 0; j < C; ++j) {
				if (map[i][j] == '#') {
					q.push(make_pair(i, j));
					distToWall[i][j] = 0;
				}
			}
		}
		while (!q.empty()) {
			pair<int, int> pa = q.front();
			q.pop();
			int y = pa.first, x = pa.second;
			for (int d = 0; d < 4; ++d) {
				int nx = x + X[d], ny = y + Y[d];
				if (0 <= nx && 0 <= ny && nx < C && ny < R && distToWall[ny][nx] == -1) {
					distToWall[ny][nx] = distToWall[y][x] + 1;
					q.push(make_pair(ny, nx));
				}
			}
		}
	}

	// Find the square you see when standing at a given square and looking in a
	// given direction.
	vector<vector<ar<pair<int, int>, 4> > > seen(R, vector<ar<pair<int, int>, 4> >(C));
	{
		int last;
		for (int y = 0; y < R; ++y) {
			for (int x = 0; x < C; ++x) {
				if (map[y][x] == '#') last = x;
				seen[y][x][0] = make_pair(y, last+1);
			}
			for (int x = C; x --> 0; ) {
				if (map[y][x] == '#') last = x;
				seen[y][x][1] = make_pair(y, last-1);
			}
		}
		for (int x = 0; x < C; ++x) {
			for (int y = 0; y < R; ++y) {
				if (map[y][x] == '#') last = y;
				seen[y][x][2] = make_pair(last+1, x);
			}
			for (int y = R; y --> 0; ) {
				if (map[y][x] == '#') last = y;
				seen[y][x][3] = make_pair(last-1, x);
			}
		}
	}

	// Finally, solve the problem with Dijkstra's algorithm.
	vector<vector<int> > dists(R, vector<int>(C, -1));
	vector<vector<pair<int, int> > > cameFrom(R, vector<pair<int, int> >(C));
	{
		const int MaxDist = R * C;
		vector<vector<pair<pair<int, int>, pair<int, int> > > > q(MaxDist + 1);
		q[0].push_back(make_pair(make_pair(starty, startx), make_pair(0, 0)));
		for (int dist = 0; dist <= MaxDist; ++dist) {
			vector<pair<pair<int, int>, pair<int, int> > >& dq = q[dist];
			for (int i = 0; i < (int)dq.size(); ++i) {
				pair<int, int> pa = dq[i].first;
				int y = pa.first, x = pa.second;
				if (dists[y][x] != -1)
					continue;
				dists[y][x] = dist;
				cameFrom[y][x] = dq[i].second;

				// Move to an adjacent square.
				for (int d = 0; d < 4; ++d) {
					int nx = x + X[d], ny = y + Y[d];
					pair<int, int> pa2 = make_pair(ny, nx);
					if (map[ny][nx] != '#' && dist+1 <= MaxDist)
						q[dist+1].push_back(make_pair(pa2, pa));
				}

				// Shoot a portal
				for (int d = 0; d < 4; ++d) {
					pair<int, int> pa2 = seen[y][x][d];
					int ndist = dist + distToWall[y][x];
					if (ndist <= MaxDist)
						q[ndist].push_back(make_pair(pa2, pa));
				}
			}
		}
	}

	cout << dists[endy][endx] << endl << endl;
	if (dists[endy][endx] != -1) {
		while (!(endy == starty && endx == startx)) {
			pair<int, int> from = cameFrom[endy][endx];
			int y = from.first, x = from.second;
			if (!(y == starty && x == startx))
				map[y][x] = '+';
			while (true) {
				if (y < endy) ++y;
				if (y > endy) --y;
				if (x < endx) ++x;
				if (x > endx) --x;
				if (y == endy && x == endx) break;
				if (map[y][x] == '.')
					map[y][x] = (y == endy ? '-' : '|');
			}
			endy = from.first, endx = from.second;
		}
	}

	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			if (map[i][j] == '.') map[i][j] = ' ';
			else if (map[i][j] == '#') map[i][j] = '.';
		}
	}
	for (int i = 0; i < R; ++i)
		cout << map[i] << endl;
}

int main() {
	int R, C;
	cin >> R >> C;
	char** M = new char*[R];
	for (int i = 0; i < R; ++i) {
		M[i] = new char[C+1];
		for (int j = 0; j < C; ++j)
			cin >> M[i][j];
	}
	get_cake(R, C, M);
	return 0;
}
