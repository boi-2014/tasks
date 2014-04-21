#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
using namespace std;

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

vector <cut> correct;
cut outp;
bool none;

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
}

bool Check() {
    if (none) return correct.size() == 0;
    for (int i = 0; i < correct.size(); i++)
        if (correct[i] == outp) return true;
    return false;
}

int main(int argc, char *argv[]) {
    
    if (argc < 4) {
        fprintf(stderr, "Usage: checker file.in file.sol file.out\n");
        exit(1);
    }
    readCorrect(argv[2]);
    readOutput(argv[3]);
    printf("%d\n", Check());
    return 0;    
}
