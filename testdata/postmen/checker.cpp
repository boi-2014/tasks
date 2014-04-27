#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <algorithm>
using namespace std;
#define MaxN 500010
#define MaxM 500010

int N, M;
int E[2*MaxM], C[MaxN], P[MaxN], t[MaxN];
int a[MaxM], b[MaxM];
bool used[2*MaxM];

char S[30];

void Parse(char lin[], int &a, int &b) {
    int slen = strlen(lin);
    int pnt = 0;
    a = 0; b = 0;
    while (isdigit(lin[pnt])) {
        a = 10 * a + lin[pnt] - '0';
        pnt++;
    }
    while (!isdigit(lin[pnt])) pnt++;
    while (pnt < slen && isdigit(lin[pnt])) {
        b = 10 * b + lin[pnt] - '0';
        pnt++;
    }
}

//Read
void read_input (char * filename) {
    FILE * f = fopen(filename, "r");
    fscanf(f, "%d%d\n", &N, &M);
	for (int i = 0; i < M; i++) {
        fgets(S, 30, f);
        Parse(S, a[i], b[i]);
        //fscanf(f, "%d%d", &a[i], &b[i]);
        if (a[i] > N || b[i] > N)
	    fprintf(stderr, "Bad input file\n");
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


void getInt (FILE * f, int & n, bool & endln, bool & eof) {
    char c;
    do {
       c = fgetc(f);
    }while (c != EOF && c != '\n' && c != '\r' && !isDigit(c));
	
	if (c == '\n') {
		endln = true;
		return;
	}else if (c == EOF) {
		endln = eof = true;
		return;
	}
	n = c - '0';
    c = fgetc(f);
    while (isDigit(c)) {
        n = n*10 + (c - '0');
        if (n > N) 
			error ("Number in output too big");
		c = fgetc(f);
	}
	if (c == '\n')
		endln = true;
	else if (c == EOF)
		endln = eof = true;

}


int T, TC[MaxN], PT[MaxN], TD[2*MaxM], T_;
bool usedV[MaxN];

void read_output (char * filename) {
    FILE * f = fopen(filename, "r");
    PT[0] = TC[0] = 0;
    T_ = 1;

	bool eoln = false, eof = false;
	int tmp;

	while (!eof) {
		//printf ("NEW ONE!\n");
		PT[T_] = PT[T_-1] + TC[T_-1];
		while (!eoln) {
			tmp = -1;
			getInt(f, tmp, eoln, eof);
			//printf ("   TMP = %d\n", tmp);
			if (tmp != -1) {
				if (used[tmp]) error ("Junction twice in a tour");
				TD[PT[T_] + TC[T_]] = tmp;
				TC[T_]++;
				used[tmp] = false;
			}
			if (PT[T_] + TC[T_] > M) error ("Too many junctions in answer");
		}
		eoln = false;
		for (int i = 0; i < TC[T_]; i++)
			used[TD[PT[T_]+i]] = false; 
		if (TC[T_] > 0) T_++;
		if (T_ > M) error("Too many junctions in answer");
	}
	if (TC[T_] == 0) T_--;
	T = T_;
	//printf("T = %d\n", T);
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
        sort(E + P[i], E + P[i] + C[i]);
    }
    
    int prev;
    for (T_ = 1; T_ <= T; T_++) {
        prev = TD[PT[T_]+TC[T_]-1];
        for (int j = 0; j < TC[T_]; j++) {
            int v = TD[PT[T_]+j];
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
