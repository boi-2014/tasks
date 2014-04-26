/**
 * BFS solution to Network. Should only pass subtask #2.
 *
 * Author: Donatas Kucinskas
 */

#include <vector>
#include "network.h"

using namespace std;
const int MAX_N = 1000;
const int INF = 2*MAX_N;

vector<int> e[MAX_N];
int back[MAX_N];

bool visited[MAX_N];
int dist[MAX_N];

void findRoute(int N, int x, int y)  {
	x--; y--;
	for (int i = 0; i < N; ++i) {
		dist[i] = INF;
		for (int j = i+1; j < N; ++j)
			if (ping(i+1, j+1) == 0) {
				e[i].push_back(j);
				e[j].push_back(i);
			}
	}
	dist[x] = 0;
	
	int now = x;
	while (now != -1) {
		for (int i = 0; i < e[now].size(); ++i) {
			int next = e[now][i];
			int newDist = dist[now] + 1;
			if (newDist < dist[next]) {
				dist[next] = newDist;
				back[next] = now;
			}
		}
		visited[now] = true;
		now = -1;
		for (int i = 0; i < N; ++i)
			if (!visited[i] && (now == -1 || dist[i] < dist[now]))
				now = i;
	}

	vector<int> path;
	now = y;
	while (now != x) {
		path.push_back(now+1);
		now = back[now];
	}
	for (int i = path.size()-1; i >= 0; --i)
		travelTo(path[i]);
}
