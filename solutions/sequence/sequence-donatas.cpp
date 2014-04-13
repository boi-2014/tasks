/**
 * O(K log K) solution.
 *
 * Author: Donatas Kucinskas
 * Idea: Vytautas Gruslys
 *
 * Correctness is not guaranteed (too many special cases).
 */

#include <iostream>
#include <set>
#include <vector>

using namespace std;

const long long INF = 1000000000000000000;

long long find(vector<set<int> > sets, int depth, bool canFinish) {
	int from = 0;
	int to = 9;

	if (sets.size() == 1) {
		if (sets[0].empty()) {
			if (canFinish)
				return 0;
			from = 1;
		}
		else {
			long long number = 0;
			for (set<int>::iterator it = sets[0].begin(); it != sets[0].end(); ++it) {
				number *= 10;
				number += *it;
			}
			return number;
		}
	}
	else if (sets.size() == 2) {
		if (!sets[0].count(9) && !sets[1].count(0))
			to = 8;
	}
	
	long long best = INF;
	for (int i = from; i <= to; ++i) {
		vector<set<int> > newSets;
		set<int> currentSet;

		bool allowFinish = !(i == 0 && (sets[0].count(0) || !canFinish));

		int digit = i;
		for (int j = 0; j < sets.size(); j++) {
			if (digit == 10) {
				digit = 0;
				newSets.push_back(currentSet);
				currentSet.clear();
			}
			set<int> tempSet = sets[j];
			tempSet.erase(digit);
			currentSet.insert(tempSet.begin(), tempSet.end());
			digit++;
		}
		newSets.push_back(currentSet);
		long long returned = find(newSets, depth+1, allowFinish);
		if (returned != INF) {
			long long now = returned * 10 + i;
			if (best == INF || now < best)
				best = now;
			//TODO: optimize - if returned 0, finish?
		}
	}
	return best;
}

long long recreate_sequence(int K, int B[]) {
	vector<set<int> > sets;
	sets.reserve(K);
	for (int i = 0; i < K; ++i) {
		set<int> s;
		s.insert(B[i]);
		sets.push_back(s);
	}
	return find(sets, 0, true);
}

const int LENGTH = 6;
int ARRAY[LENGTH] = {7, 8, 9, 5, 1, 2};

//const int LENGTH = 10;
//int ARRAY[LENGTH] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
//answer: 10

int main() {
	cout << recreate_sequence(LENGTH, ARRAY) << endl;
	return 0;
}
