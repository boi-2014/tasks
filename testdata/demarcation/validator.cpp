#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
using namespace std;

const int Maxn = 100000;
const int lim = 1000000000;

typedef pair <int, int> ii;
typedef long long ll;

FILE *f;
int x[Maxn + 1], y[Maxn + 1];

void Error(const char s[]) {
    fclose(f);
    fprintf(stderr, "%s\n", s);
    printf("0\n");
    exit(0);
}

bool inLine(int a, int b, int c)
{
    return x[a] == x[b] && x[b] == x[c] ||
           y[a] == y[b] && y[b] == y[c];
}

bool Check(const char fileName[]) 
{
    f = fopen(fileName, "r");
    int cnt; fscanf(f, "%d", &cnt);
    if (cnt > Maxn) Error("Too many points");
    int rcnt = 0;
    while (rcnt <= cnt && fscanf(f, "%d %d", &x[rcnt], &y[rcnt]) == 2) {
        if (x[rcnt] < 0 || x[rcnt] > lim || y[rcnt] < 0 || y[rcnt] > lim)
            Error("Incorrect numbers");
        rcnt++;
    }
    if (rcnt < cnt) Error("Not enough numbers");
    if (rcnt > cnt) Error("Too many numbers");
    for (int i = 0; i < cnt; i++)
        if (inLine(i, (i + 1) % cnt, (i + 2) % cnt)) Error("3 points in line!");
    fclose(f);
    return true;
}

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        fprintf(stderr, "Usage: validator file.in\n");
        exit(1);
    }
    printf("%d\n", Check(argv[1]));
    return 0;    
}
