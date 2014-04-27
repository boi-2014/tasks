#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
using namespace std;

const int MaxN = 100000;
const int Max = 1000000000;

typedef pair <int, int> pii;
typedef long long ll;

FILE *f;
int x[MaxN+10], y[MaxN+10];
int N;

void Error(const char s[]) {
    fclose(f);
    fprintf(stdout, "%s\n", s);
    //printf("0\n");
    exit(0);
}

bool inLine(int a, int b, int c) {
    return x[a] == x[b] && x[b] == x[c] ||
           y[a] == y[b] && y[b] == y[c];
}

bool shared (int i, int j) {
    return (x[i] == x[j]) || (y[i] == y[j]);
}

void check_1() {


}


void check_intersect() {

    for (int i = 0; i < N; i++) {
	for (int 


    }

}


void check(const char fileName[], string sub) {
    f = fopen(fileName, "r");
    fscanf(f, "%d", &N);
    if (N > Maxn || N < 0) Error("Too many points");
    int sub1 = 0;
    if (sub.find('1') != -1) sub1 = true;
    
    int rcnt = 0;
    while (rcnt <= N && fscanf(f, "%d %d", &x[rcnt], &y[rcnt]) == 2) {
        if (x[rcnt] < 0 || x[rcnt] > lim || y[rcnt] < 0 || y[rcnt] > lim)
            Error("Incorrect numbers");
        rcnt++;
    }
    if (rcnt < N) Error("Not enough numbers");
    if (rcnt > N) Error("Too many numbers");
    for (int i = 0; i < N; i++) {
        if (inLine(i, (i + 1) % N, (i + 2) % N)) Error("3 points in line!");
    	if (!shared(i, (i + 1) % N)) Error ("Points do not form figure parallel to axis!");
    }

    if (sub1) check1();
    check_intersect();
}

int main(int argc, char *argv[]) {
    
    if (argc < 3) {
        fprintf(stderr, "Usage: validator file.in subtask_string\n");
        exit(1);
    }
    check(argv[1], argv[2]);
    printf("OK\n");
    return 0;    
}
