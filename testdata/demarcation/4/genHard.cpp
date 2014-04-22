#include <cstdio>
using namespace std;

const int Maxl = 24999;
const int a = 501;
const int b = 20000000;
const int c = 10;
const int d = 53;

int main()
{
	printf("%d\n", 4 * (Maxl + 1));
	int nilx = 10, nily = 20;
	int curx = nilx, cury = nily;
	printf("%d %d\n", curx, cury);
	cury += Maxl * a + (Maxl - 1) * (a - 2 * d);
	printf("%d %d\n", curx, cury);
	curx += b + c;
	printf("%d %d\n", curx, cury);
	cury -= d;
	for (int i = 0; i < Maxl; i++) {
		printf("%d %d\n", curx, cury);
		curx -= b;
		printf("%d %d\n", curx, cury);
		cury -= a - 2 * d;
		printf("%d %d\n", curx, cury);
		curx += b;
		printf("%d %d\n", curx, cury);
		if (i + 1 < Maxl) cury -= a;
		else {
			cury -= d;
			printf("%d %d\n", curx, cury);
		}
	}
	return 0;
}