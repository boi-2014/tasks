#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <set>
using namespace std;

const int MaxN = 100000;
const int lim = 1000000000;
#define TX1 10
#define TY 11
#define TX2 12


typedef pair<int, int> pii;
typedef long long ll;
typedef set<int>::iterator sii;


FILE *f;
int X[MaxN+10], Y[MaxN+10];
int N;

void Error(const char s[]) {
    fclose(f);
    fprintf(stdout, "%s", s);
    //printf("0\n");
    exit(0);
}

bool inLine(int a, int b, int c) {
    return X[a] == X[b] && X[b] == X[c] ||
           Y[a] == Y[b] && Y[b] == Y[c];
}

bool shared (int i, int j) {
    return (X[i] == X[j]) || (Y[i] == Y[j]);
}

struct element {
    int y, i;
    element (int y = 0, int i = -1): y(y), i(i) {}
    bool operator < (const element & e) const {
        return y < e.y;
    }
};

struct event {
    int x, t;
    element e;
    event (int x = 0, int t = 0, element e = element()) : x(x), t(t), e(e) {}
    bool operator< (const event & k) const {
        if (x != k.x) return x < k.x;
        else if (t != k.t) return t < k.t;
        else return e < k.e;
    }
};

struct event1 {
    int x, t;
    element e;
    event1 (int x = 0, int t = 0, element e = element()) : x(x), t(t), e(e) {}
    bool operator< (const event1 & k) const {
        if (x != k.x) return x < k.x;
        else if (t != k.t) return t > k.t; 
        else return e < k.e;
    }
};
/*
struct event2 {
    int x, t;
    element e;
    event2 (int x = 0, int t = 0, element e = element()) : x(x), t(t), e(e) {}
    bool operator< (const event2 & k) const {
        if (x != k.x) return x < k.x;
        else if (t != k.t) 
    }
};*/

vector<event> E;
vector<event1> E1;
vector<event1> E2;



void check_intersect(bool sub1) {
    //printf("NEW TRY!\n");
    E.clear();
    E1.clear();
    E2.clear();
    for (int i = 0; i < N; i++) {
        int j = (i + 1) % N;
        if (X[i] == X[j]) {
            E.push_back(event(X[i], TY,element())); 
            E1.push_back(event1(X[i], TY, element()));
            E2.push_back(event1(X[i], TY, element(min(Y[i],Y[j]), max(Y[i],Y[j])) ));
        }else {
            E.push_back(event(min(X[i], X[j]), TX1, element(Y[i], i) ));
            E.push_back(event(max(X[i], X[j]), TX2, element(Y[i], i) ));
            
            E1.push_back(event1(min(X[i], X[j]), TX1, element(Y[i], i) ));
            E1.push_back(event1(max(X[i], X[j]), TX2, element(Y[i], i) ));
            
            E2.push_back(event1(min(X[i], X[j]), TX1, element(Y[i], i) ));
            E2.push_back(event1(max(X[i], X[j]), TX2, element(Y[i], i) ));
        }
    }
    sort (E.begin(), E.end());
    sort (E1.begin(), E1.end());
    sort (E2.begin(), E2.end());
    set <int> S; //for two unique Y's. 
    set <int> S1;
    set <int> S2;

    for (int i = 0; i < E.size(); i++) {
        if (E[i].t == TX1) {
            if (S.find(E[i].e.y) != S.end())
                Error ("Overlaping edges");
            S.insert(E[i].e.y);
        }else if (E[i].t == TY) {
        }else if (E[i].t == TX2) {
            S.erase(E[i].e.y);
        }

        if (E1[i].t == TX1) {
            S1.insert(E1[i].e.y);
        }else if (E1[i].t == TX2) {
            S1.erase(E1[i].e.y);
        }
        if (sub1 && S1.size() > 2) Error("FAIL, too many intersections (1)");
     
       
        //printf("Event: X = %d, type = %d, y1 = %d, y2 = %d\n", E2[i].x, E2[i].t, E2[i].e.y, E2[i].e.i) ;
        //for (sii P = S2.begin(); P != S2.end(); P++) printf("%d ", (*P));
        //printf("\n");
        if (E2[i].t == TX1) {
            S2.insert(E2[i].e.y);     
        }else if (E2[i].t == TY) {
            int a = E2[i].e.y+1, b =E2[i].e.i-1;
            sii c = S2.lower_bound(a),
                d = S2.upper_bound(b);
            if (c != d) Error ("Fail, two sides cross");
        }else if (E2[i].t ==TX2) {
            S2.erase(E2[i].e.y);
        }
     
     
     }


}


void check(const char fileName[], string sub) {
    f = fopen(fileName, "r");
    fscanf(f, "%d", &N);
    bool sub1 = false;
    if (sub.find('1') != -1) sub1 = true;
    
    int rcnt = 0;
    while (rcnt <= N && fscanf(f, "%d %d", &X[rcnt], &Y[rcnt]) == 2) {
        if (X[rcnt] < 0 || X[rcnt] > lim || Y[rcnt] < 0 || Y[rcnt] > lim)
            Error("Coordinates out of bounds");
        rcnt++;
    }
    if (rcnt < N) Error("Not enough numbers");
    if (rcnt > N) Error("Too many numbers");
    for (int i = 0; i < N; i++) {
        if (inLine(i, (i + 1) % N, (i + 2) % N)) Error("3 points in line!");
    	if (!shared(i, (i + 1) % N)) Error ("Points do not form figure parallel to axis!");
    }

    check_intersect(sub1);
    for (int i = 0; i < N; i++)
        swap (X[i], Y[i]);
    check_intersect(sub1);
}

int main(int argc, char *argv[]) {
    
    if (argc < 3) {
        fprintf(stderr, "Usage: validator file.in subtask_string\n");
        exit(1);
    }
    check(argv[1], argv[2]);
    printf("OK");
    return 0;    
}
