#include <cstdio>
#include <algorithm>
#include <map>
#include <set>
#include <tuple>
#include <vector>
#include "coprobber.h"

using namespace std;

typedef tuple<bool, int, int> State;

vector<int> Neighbours[MAX_N];
set<State> States;
map<State, int> Cache;

bool robberMove(int, int);

// Can the cop win in this situation?
bool copMove(int cop, int robber) {
	if (cop == robber)
		return true;
	
	State s(true, cop, robber);
	if (Cache.count(s))
		return Cache[s];
	if (States.count(s))
		return false;
	States.insert(s);
	bool result = any_of(Neighbours[cop].begin(), Neighbours[cop].end(), [&](int i) {
		return !robberMove(i, robber);
	}) || !robberMove(cop, robber);
	States.erase(s);
	Cache[s] = result;
	return result;
}

// Can robber win in this situation?
bool robberMove(int cop, int robber) {
	if (cop == robber)
		return false;
	
	State s(false, cop, robber);
	if (Cache.count(s))
		return Cache[s];
	if (States.count(s))
		return true;
	States.insert(s);
	bool result = any_of(Neighbours[robber].begin(), Neighbours[robber].end(), [&](int i) {
		return !copMove(cop, i);
	});
	States.erase(s);
	Cache[s] = result;
	return result;
}

int start(int N, bool A[MAX_N][MAX_N]) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (A[i][j])
				Neighbours[i].push_back(j);
	bool can_catch = true;
	for (int i = 1; i < N; i++)
		can_catch &= copMove(0, i);
	return can_catch;
}

int nextMove(int robber) {

}
