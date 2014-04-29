#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
using namespace std;

const int Maxn = 100005;
const int lim = 1000000000;

typedef pair <int, int> ii;
typedef long long ll;

struct cut {
    ii a, b;
    cut(ii ga = ii(0, 0), ii gb = ii(0, 0)) {
        a = ga; b = gb;
        if (a > b) swap(a, b);
    }
    bool operator ==(const cut &c) const {
        return a == c.a && b == c.b;
    }
};

int n;
int x[Maxn], y[Maxn];
vector <cut> correct;
cut outp;
bool none;

void readInput(char *fileName)
{
    FILE *f = fopen(fileName, "r");
    fscanf(f, "%d", &n);
    for (int i = 0; i < n; i++)
        fscanf(f, "%d %d", &x[i], &y[i]);
    fclose(f);
}

void readCorrect(char *fileName)
{
    FILE *f = fopen(fileName, "r");
    int cnt; fscanf(f, "%d", &cnt);
    ii a, b;
    for (int i = 0; i < cnt; i++) {
        fscanf(f, "%d %d %d %d", &a.first, &a.second, &b.first, &b.second);
        correct.push_back(cut(a, b));
    }
    fclose(f);
}

void Error(const char s[]) {
    fprintf(stderr, "%s\n", s);
    printf("0\n");
    exit(0);
}

void Get(const string &s, int &pnt, int &cur)
{
    ll got = 0ll;
    bool rd = false;
    while (pnt < s.length() && !isdigit(s[pnt]))
        if (s[pnt] != ' ') Error("Invalid symbols");
        else pnt++;
    while (got <= lim && pnt < s.length() && isdigit(s[pnt])) {
        got = 10ll * got + s[pnt] - '0';
        rd = true;
        pnt++;
    }
    if (!rd) Error("Not enough numbers in output");
    if (got > lim) Error("Number is too big");
    if (pnt < s.length() && s[pnt] != ' ') Error("Invalid symbols");
    cur = got;
}

void getFrom(const string &s, ii &a, ii &b)
{
    int pnt = 0;
    Get(s, pnt, a.first);
    Get(s, pnt, a.second);
    Get(s, pnt, b.first);
    Get(s, pnt, b.second);
}

void checkIntersection(const cut &c1, const cut &c2)
{
    if (c1.a.first == c1.b.first && c2.a.first == c2.b.first && c1.a.first == c2.a.first) {
        int mn = max(c1.a.second, c2.a.second);
        int mx = min(c1.b.second, c2.b.second);
        if (mn < mx) Error("Cut and vertical edge have many common points");
    }
    if (c1.a.second == c1.b.second && c2.a.second == c2.b.second && c1.a.second == c2.a.second) {
        int mn = max(c1.a.first, c2.a.first);
        int mx = min(c1.b.first, c2.b.first);
        if (mn < mx) Error("Cut and horizontal edge have many common points");
    }
    if (c1.a.first == c1.b.first && c2.a.second == c2.b.second) {
        if (c1.a.second < c2.a.second && c2.a.second < c1.b.second &&
            c2.a.first < c1.a.first && c1.a.first < c2.b.first)
            Error("Cut crosses an edge as '+'");
    }
    if (c1.a.second == c1.b.second && c2.a.first == c2.b.first) {
        if (c1.a.first < c2.a.first && c2.a.first < c1.b.first &&
            c2.a.second < c1.a.second && c1.a.second < c2.b.second)
            Error("Cut crosses an edge as '+'");
    }

}

void checkEdges(const cut &mycut)
{
    for (int i = 0; i < n; i++) {
        checkIntersection(mycut, cut(ii(x[i], y[i]), ii(x[(i + 1) % n], y[(i + 1) % n])));
        cut c = cut(ii(x[i], y[i]), ii(x[(i + 1) % n], y[(i + 1) % n]));
    }
}

void readOutput(char *fileName)
{
    ifstream f(fileName);
    ii a, b;
    string s;
    getline(f, s);
    f.close();
    if (s.substr(0, 2) == "NO") { none = true; return; }
    getFrom(s, a, b);
    outp = cut(a, b);
    checkEdges(outp);
}

bool Check() {
    if (none) {
        if (correct.size())
            Error("User didn't find an existing cut");
        return true;
    }
    if (correct.size() == 0) Error("User found a non-existing cut");
    for (int i = 0; i < correct.size(); i++)
        if (correct[i] == outp) return true;
    if (correct.size() == 2) Error("There were 2 cuts, user found an incorrect one");
    if (correct[0].a.first == correct[0].b.first && outp.a.first == outp.b.first)
        Error("Correct was vertical cut, user found an incorrect vertical");
    if (correct[0].a.second == correct[0].b.second && outp.a.second == outp.b.second)
        Error("Correct was horizontal cut, user found an incorrect horizontal");
    Error("User found not the same orientation cut");
    return false;
}

int main(int argc, char *argv[]) {
    
    if (argc < 4) {
        fprintf(stderr, "Usage: checker file.in file.sol file.out\n");
        exit(1);
    }
    readInput(argv[1]);
    readCorrect(argv[2]);
    readOutput(argv[3]);
    printf("%d\n", Check());
    return 0;    
}
