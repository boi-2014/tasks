#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
#define MaxN 500010
#define MaxM 500010

int N, M;
int E[2*MaxM], C[MaxN], P[MaxN], t[MaxN];
int a[MaxM], b[MaxM];
bool used[2*MaxM];

//Read
void read_input (char * filename) {
    FILE * f = fopen(filename, "r");
    fscanf(f, "%d%d", &N, &M);
    for (int i = 0; i < M; i++) {
        fscanf(f, "%d%d", &a[i], &b[i]);
        C[a[i]]++; C[b[i]]++;
    }
    P[1] = 0;
    for (int i = 2; i <= N; i++)
        P[i] = C[i-1] + P[i-1];
    for (int i = 0; i < M; i++){
        E[P[a[i]]+(t[a[i]]++)] = b[i];
        E[P[b[i]]+(t[b[i]]++)] = a[i];
    };
    fclose(f);
}

void error (const char s[]) {
    fprintf(stderr, "%s\n", s);
    printf("0\n");
    exit(0);
}

bool isDigit (char c) {return (c >= '0' && c <= '9');}

int getInt (FILE * f, bool endln = false) {
    char c;
    do {
       c = fgetc(f);
    }while (c != EOF && c != '\n' && c != '\r' && !isDigit(c));
    
    if (c == EOF || c=='\n') error("Not enough numbers in output");
    int ret = c - '0';
    c = fgetc(f);
    while (isDigit(c)) {
        ret = ret*10 + (c - '0');
        if (ret > N) error ("Number in output too big");
        c = fgetc(f);
    }
    if (ret > N) error ("Number in output too big");
    if (endln) {
        while (c != '\n' && c != EOF) 
            c = fgetc(f);
    }
    return ret;
}


int T, TC[MaxN], PT[MaxN], TD[2*MaxM], T_;
bool usedV[MaxN];

void read_output (char * filename) {
    FILE * f = fopen(filename, "r");
    T = getInt(f, true);
    PT[0] = TC[0] = 0;
    for (T_ = 1; T_ <= T; T_++) {
        TC[T_] = getInt(f);
        PT[T_] = PT[T_-1] + TC[T_-1];
        if (PT[T_] + TC[T_] - 1 >= M) error ("Too many junctions in answer");
        for (int i = 0; i < TC[T_]; i++) {
            TD[PT[T_]+i] = getInt(f,(i==TC[T_])?true:false);
            if (usedV[TD[PT[T_]+i]]) error("Junction twice in a tour");
            usedV[TD[PT[T_]+i]] = true;
        }
        for (int i = 0; i < TC[T_]; i++)
            usedV[TD[PT[T_]+i]] = false;
    }
}
int b_search (int * E, int pr, int pb, int X) {
    while (pr < pb) {
        int vid = ( pr + pb ) / 2;
        if (E[vid] == X) return vid;
        else if (E[vid] < X) pr = vid + 1;
        else pb = vid - 1;
    }
    return (E[pr]==X)?pr:-1;
}

bool check () {
    for (int i = 1; i <= N; i++) {
        //printf ("V=%d,[[%d %d]]",i, P[i], P[i] + C[i] - 1);
        sort(E + P[i], E + P[i] + C[i]);
        //for (int j = P[i]; j < P[i] + C[i]; j++)
        //    printf("%d ", E[j]);
        //printf("\n");
    }
    
    int prev;
    for (T_ = 1; T_ <= T; T_++) {
        prev = TD[PT[T_]+TC[T_]-1];
        for (int j = 0; j < TC[T_]; j++) {
            int v = TD[PT[TC[T_]]+j];
            int x = b_search(E, P[prev], P[prev]+C[prev]-1, v),
                y = b_search(E, P[v], P[v]+C[v]-1, prev);
            //printf("%d->%d: %d  %d\n", prev, v, x, y);
            if (x == -1 or y == -1) error("Path through non existent street");
            if (used[x] or used[y]) error("Path through same street twice");
            used[x] = used[y] = true;
            prev = v;
        }  
    }
    if (PT[T_-1] + TC[T_-1] < M) error("Not all streets covered");
    return true;
}

int main(int argc, char * argv[]) {
    
    if (argc < 4) {
        fprintf(stderr, "Usage: checker file.in file.sol file.out\n");
        exit(1);
    }
  
    read_input(argv[1]);
    read_output(argv[3]);
    printf("%d\n", check ());
    return 0;    
}
