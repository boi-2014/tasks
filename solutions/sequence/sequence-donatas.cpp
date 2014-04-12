/**
 * An invalid brute-force solution.
 * Should pass subtask 2.
 *
 * Author: Donatas Kucinskas
 */

#include <iostream>

using namespace std;

bool contains(int number, int digit) {
	while (number != 0) {
		int now = number % 10;
		if (now == digit)
			return true;
		number /= 10;
	}
	return false;
}

long long recreate_sequence(int K, int B[]) {
	for (int n = 1; true; ++n) {
		bool found = true;
		for (int i = 0; i < K; ++i)
			if (!contains(n+i, B[i])) {
				found = false;
				break;
			}
		if (found)
			return n;
	}
}

const int LENGTH = 6;
int ARRAY[LENGTH] = {7, 8, 9, 5, 1, 2};

int main() {
	cout << recreate_sequence(LENGTH, ARRAY) << endl;
	return 0;
}
