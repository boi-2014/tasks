#include <cstdio>
#include <algorithm>
#include <map>
#include <set>
#include <tuple>
#include <vector>
#include "coprobber.h"

using namespace std;

typedef tuple<bool, int, int> State;

const int MAX_N = 1001;
set<int> neighbors[MAX_N];

set<State> states;
map<State, int> cache;

bool robber_move(int, int);

// Can cop win in this situation?
bool cop_move(int cop, int robber) {
	if (cop == robber)
		return true;
	
	State s(true, cop, robber);
	if (cache.count(s))
		return cache[s];
	if (states.count(s))
		return false;
	states.insert(s);
	bool result = any_of(neighbors[cop].begin(), neighbors[cop].end(), [&](int i) {
		return !robber_move(i, robber);
	}) || !robber_move(cop, robber);
	states.erase(s);
	cache[s] = result;
	return result;
}

// Can robber win in this situation?
bool robber_move(int cop, int robber) {
	if (cop == robber)
		return false;
	
	State s(false, cop, robber);
	if (cache.count(s))
		return cache[s];
	if (states.count(s))
		return true;
	states.insert(s);
	bool result = any_of(neighbors[robber].begin(), neighbors[robber].end(), [&](int i) {
		return !cop_move(cop, i);
	});
	states.erase(s);
	cache[s] = result;
	return result;
}

int Start(int N, int M, int U[], int V[]) {
	for (int i = 0; i < M; i++) {
		neighbors[U[i]].insert(V[i]);
		neighbors[V[i]].insert(U[i]);
	}
	bool can_catch = true;
	for (int i = 2; i <= N; i++)
		can_catch &= cop_move(1, i);
	return can_catch;
}

int NextMove(int robber) {

}
