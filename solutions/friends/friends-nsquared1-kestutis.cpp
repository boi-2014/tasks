#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

#define MaxN 100010

string S;
vector<string> ANS;
int N;
int C[1000] = {0};

int main() {
	cin >> S;
	
	for (int i = 0; i < S.size(); i++)
		C[S[i]]++;
		
	N = S.length() / 2;
	
	for (int i = 0; i < S.size(); i++) if (C[S[i]] & 1) {
		string Sn = S.substr(0, i) + S.substr(i + 1, 2*N - i);
		bool good = true;
		for (int i = 0; i < N; i++) 
			if (Sn[i] != Sn[i+N])
				good = false;
		if (good)
			ANS.push_back(Sn.substr(0, N));
	}

	bool good = true;
	for (int i = 1; i < ANS.size(); i++)
		if (ANS[0] != ANS[i])
			good = false;
	if (ANS.size() == 0)
		printf("IMPOSSIBLE\n");
	else if (good) 
		printf("%s\n", ANS[0].c_str());
	else 
		printf("NOT UNIQUE\n");


	return 0;
}
