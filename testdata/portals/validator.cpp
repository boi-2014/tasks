#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
using namespace std;

const int MaxN[] = {10, 50, 200, 200, 1000};
const int allow_four_crossing[] = {1, 1, 0, 1, 1};

FILE *f;

void Error(const char s[]) {
    fclose(f);
    fprintf(stderr, "%s\n", s);
    printf("0\n");
    exit(0);
}

int R, C;
char lab[1001][1002];
queue< pair<int,int> > q;

void go(int x, int y) {
    if (x < 0 || x >= C || y < 0 || y >= R) return;
    if (lab[y][x] == '#') return;
    lab[y][x] = '#';
    q.push(make_pair(x, y));
}

bool Check(const char fileName[], int subtask) 
{
    f = fopen(fileName, "r");
    
    fscanf(f, "%d%d", &R, &C);
    if (R > MaxN[subtask-1]) Error("R is too large");
    if (C > MaxN[subtask-1]) Error("C is too large");
    
    int i, j, cx = -1, cy = -1, sx = -1, sy = -1;
    for (j = 0; j < R; j++) {
        if (fscanf(f, " %s", lab[j]) == 0)
            Error("Too few rows.");
        if (strlen(lab[j]) > C) Error("Map is too wide.");
        if (strlen(lab[j]) < C) Error("Map is too narrow.");
        for (i = 0; i < C; i++) {
            switch (lab[j][i]) {
                case 'S': {
                    if (sx != -1) Error("Too many start positions.");
                    sx = i; sy = j;
                    break;
                }
                case 'C': {
                    if (cx != -1) Error("Too many cakes.");
                    cx = i; cy = j;
                    break;
                }
                case '.': {
                    break;
                }
                case '#': {
                    break;
                }
                default: {
                    Error("Wrong symbol in the map.");
                }
            }
        }
    }
    if (fscanf(f, " %s", lab[j]) != 0 && strlen(lab[j])) Error("Too many rows.");
    if (sx == -1) Error("No start position.");
    if (cx == -1) Error("No cake.");
    
    if (!allow_four_crossing[subtask-1])
        for (j = 1; j < R-1; j++) 
            for (i = 1; i < C-1; i++) 
                if (lab[j][i] != '#' && 
                    lab[j][i+1] != '#' &&
                    lab[j][i-1] != '#' &&
                    lab[j+1][i] != '#' &&
                    lab[j-1][i] != '#')
                        Error("Four crossings not allowed.");
    
    q.push(make_pair(sx, sy));
    lab[sy][sx] = '#';
    while (!q.empty() && lab[cy][cx] == 'C') {
        i = q.front().first;
        j = q.front().second;
        q.pop();
        go(i, j+1);
        go(i, j-1);
        go(i+1, j);
        go(i-1, j);
    }
    if (lab[cy][cx] == 'C')
        Error("Cake is unreachable.");
    
    fclose(f);
    return true;
}



int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        fprintf(stderr, "Usage: validator <input file> [<subtask>]\n");
        exit(1);
    }
    printf("%d\n", Check(argv[1], argc >= 3 ? max(1, min(5, atoi(argv[2]))) : 5));
    return 0;
}
