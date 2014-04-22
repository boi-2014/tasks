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

void Error(const char s[]) {
    fclose(f);
    fprintf(stderr, "%s\n", s);
    printf("0\n");
    exit(0);
}

bool Check(const char fileName[]) 
{
    f = fopen(fileName, "r");
    int cnt; fscanf(f, "%d", &cnt);
    if (cnt > Maxn) Error("Too many points");
    int rcnt = 0;
    int x, y;
    while (fscanf(f, "%d %d", &x, &y) == 2) {
        if (x < 0 || x > lim || y < 0 || y > lim)
            Error("Incorrect numbers");
        rcnt++;
    }
    if (rcnt < cnt) Error("Not enough numbers");
    if (rcnt > cnt) Error("Too many numbers");
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
