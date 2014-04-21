#include <cstdio>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef pair <int, int> ii;

const string nam = "1/demarcation.in.";
const int lim = 1000000000;
const int Maxn = 100000;

int cur = 1;

ll Random() { return ll(rand()) << 45ll | ll(rand()) << 30ll | ll(rand()) << 15ll | ll(rand()); }

ll Random(ll l, ll r) { return rand() % (r - l + 1) + l; }

void randomSortedPair(int &a, int &b, int l, int r)
{
	do {
		a = Random(l, r);
		b = Random(l, r);
	} while (a == b);
	if (a > b) swap(a, b);
}

string toStr(int num)
{
	stringstream ss; ss << num;
	string s; ss >> s;
	return s;
}

void Print(const vector <ii> &p)
{
	FILE *f = fopen((nam + toStr(cur)).c_str(), "w");
	fprintf(f, "%d\n", p.size());
	for (int i = 0; i < p.size(); i++)
		fprintf(f, "%d %d\n", p[i].first, p[i].second);
	fclose(f);
	cur++;
}

// Impossible square
void Test1()
{
	vector <ii> p;
	p.push_back(ii(1, 1));
	p.push_back(ii(lim, 1));
	p.push_back(ii(lim, lim));
	p.push_back(ii(1, lim));
	Print(p);
}

// Trivial rectange - solvable only with Oy cut
void Test2()
{
	vector <ii> p;
	p.push_back(ii(0, 1));
	p.push_back(ii(lim, 1));
	p.push_back(ii(lim, lim));
	p.push_back(ii(0, lim));
	Print(p);
}

// Trivial rectangle - solvable only with Ox cut
void Test3()
{
	vector <ii> p;
	p.push_back(ii(1, 0));
	p.push_back(ii(lim, 0));
	p.push_back(ii(lim, lim));
	p.push_back(ii(1, lim));
	Print(p);
}

// Triminos - solvable
void Test4()
{
	vector <ii> p;
	p.push_back(ii(4, 12));
	p.push_back(ii(7, 12));
	p.push_back(ii(7, 10));
	p.push_back(ii(6, 10));
	p.push_back(ii(6, 11));
	p.push_back(ii(3, 11));
	p.push_back(ii(3, 13));
	p.push_back(ii(4, 13));
	Print(p);
}

// Triminos - unsolvable
void Test5()
{
	vector <ii> p;
	p.push_back(ii(14, 5));
	p.push_back(ii(14, 6));
	p.push_back(ii(12, 6));
	p.push_back(ii(12, 4));
	p.push_back(ii(11, 4));
	p.push_back(ii(11, 3));
	p.push_back(ii(13, 3));
	p.push_back(ii(13, 5));
	Print(p);
}

// BIG
void Test6()
{
	vector <ii> p;
	int a = 25000;
	int b = a - 2;
	int curx = 10000000, cury = 1000000;
	for (int i = 0; i < a; i += 2) {
		curx++;
		p.push_back(ii(curx, cury));
		cury--;
		p.push_back(ii(curx, cury));
	}
	for (int i = 0; i < b; i += 2) {
		curx--;
		p.push_back(ii(curx, cury));
		cury--;
		p.push_back(ii(curx, cury));
	}
	curx--;
	for (int i = 0; i < a; i += 2) {
		curx--;
		p.push_back(ii(curx, cury));
		cury++;
		p.push_back(ii(curx, cury));
	}
	for (int i = 0; i < b; i += 2) {
		curx++;
		p.push_back(ii(curx, cury));
		cury++;
		p.push_back(ii(curx, cury));
	}
	Print(p);
}

// Small, not solvable test case
void Small()
{
	vector <ii> p;
	p.push_back(ii(5, 3));
	p.push_back(ii(6, 3));
	p.push_back(ii(6, 1));
	p.push_back(ii(7, 1));
	p.push_back(ii(7, 4));
	p.push_back(ii(8, 4));
	p.push_back(ii(8, 1));
	p.push_back(ii(9, 1));
	p.push_back(ii(9, -1));
	p.push_back(ii(8, -1));
	p.push_back(ii(8, -3));
	p.push_back(ii(7, -3));
	p.push_back(ii(7, -1));
	p.push_back(ii(6, -1));
	p.push_back(ii(6, -2));
	p.push_back(ii(5, -2));
	p.push_back(ii(5, -1));
	p.push_back(ii(4, -1));
	p.push_back(ii(4, -4));
	p.push_back(ii(3, -4));
	p.push_back(ii(3, -1));
	p.push_back(ii(2, -1));
	p.push_back(ii(2, 1));
	p.push_back(ii(3, 1));
	p.push_back(ii(3, 2));
	p.push_back(ii(4, 2));
	p.push_back(ii(4, 1));
	p.push_back(ii(5, 1));
	Print(p);
}

bool sanityCheck(const vector <ii> &p)
{
	if (p.size() > Maxn) return false;
	for (int i = 0; i < p.size(); i++)
		if (p[i].first < 0 || p[i].first > lim || p[i].second < 0 || p[i].second > lim)
			return false;
	return true;
}

const int aprox = 5000;

bool solvableOX()
{
	vector <ii> p;
	int Y = Random(1, lim - 1);
	int X1, X2; randomSortedPair(X1, X2, 0, lim);
	if (X1 + 1 == X2) return false;
	int X = Random(X1 + 1, X2);
	int curlim = min(lim, Y + Y);
	int mxsy = max((curlim - Y) / aprox, 10);
	int mxsx = max((X2 - X1) / aprox, 10);
	int curx = X1, cury = Y;
	while (curx < X2)
		if (curx < X) {
			cury = min(cury + int(Random(1, mxsy)), curlim);
			p.push_back(ii(curx, cury));
			if (cury == curlim) curx = X;
			else curx = min(curx + int(Random(1, mxsx)), X2);
			p.push_back(ii(curx, cury));
		} else {
			cury = max(cury - int(Random(1, mxsy)), Y + 1);
			p.push_back(ii(curx, cury));
			if (cury == Y + 1) curx = X2;
			else curx = min(curx + int(Random(1, mxsx)), X2);
			p.push_back(ii(curx, cury));
		}
	int delt = Random(1, min(100, X2 - X1));
	p.push_back(ii(X2, Y));
	int pnt = p.size() - 1;
	curx = X2 - delt, cury = Y;
	p.push_back(ii(curx, cury));
	while (pnt) {
		curx += p[pnt - 1].first - p[pnt].first;
		cury -= p[pnt - 1].second - p[pnt].second;
		p.push_back(ii(curx, cury));
		pnt--;
	}
	cury = Y; p.push_back(ii(curx, cury));
	p.push_back(ii(X1, Y));
	if (!sanityCheck(p)) return false;
	Print(p);
	return true;
}

bool solvableOY()
{
	vector <ii> p;
	int X = Random(1, lim - 1);
	int Y1, Y2; randomSortedPair(Y1, Y2, 0, lim);
	if (Y1 + 1 == Y2) return false;
	int Y = Random(Y1 + 1, Y2);
	int curlim = min(lim, X + X);
	int mxsx = max((curlim - X) / aprox, 10);
	int mxsy = max((Y2 - Y1) / aprox, 10);
	int curx = X, cury = Y1;
	while (cury < Y2)
		if (cury < Y) {
			curx = min(curx + int(Random(1, mxsx)), curlim);
			p.push_back(ii(curx, cury));
			if (curx == curlim) cury = Y;
			else cury = min(cury + int(Random(1, mxsy)), Y2);
			p.push_back(ii(curx, cury));
		} else {
			curx = max(curx - int(Random(1, mxsx)), X + 1);
			p.push_back(ii(curx, cury));
			if (curx == X + 1) cury = Y2;
			else cury = min(cury + int(Random(1, mxsy)), Y2);
			p.push_back(ii(curx, cury));
		}
	int delt = Random(1, min(100, Y2 - Y1));
	int len = p.size();
	p.push_back(ii(X, Y2));
	int ox = X, oy = Y1;
	curx = X, cury = Y2 + delt;
	p.push_back(ii(curx, cury));
	for (int i = 0; i < len; i++) {
		curx -= p[i].first - ox;
		cury -= p[i].second - oy;
		ox = p[i].first; oy = p[i].second;
		p.push_back(ii(curx, cury));
	}
	curx = X; p.push_back(ii(curx, cury));
	p.push_back(ii(X, Y1));
	if (!sanityCheck(p)) return false;
	Print(p);
	return true;
}

int main()
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	for (int i = 0; i < 3; i++)
		if (!solvableOX()) i--;
	for (int i = 0; i < 3; i++)
		if (!solvableOY()) i--;
	Small();
	return 0;
}