#include <cstdio>
#include "coprobber.h"

using namespace std;

static int N;
static bool A[MAX_N][MAX_N];

int main() {
	int m;
	scanf("%d%d", &N, &m);
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		A[u - 1][v - 1] = A[v - 1][u - 1] = true;
	}
	
	int result = start(N, A);
	
	printf("%d\n", result);
	return 0;
}
