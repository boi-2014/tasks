#include <cstdio>
#include "coprobber.h"

using namespace std;

static const int MAX_N = 1000;
static int N_, M_, U_[MAX_N], V_[MAX_N];

int main() {
	scanf("%d%d", &N_, &M_);
	for (int i = 0; i < M_; i++)
		scanf("%d%d", &U_[i], &V_[i]);
	
	int result = Start(N_, M_, U_, V_);
	
	printf("%d\n", result);
	return 0;
}
