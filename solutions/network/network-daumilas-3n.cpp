#include "network.h"
const int MAX_N = 1000;

void findRoute (int N, int a, int b)
{
    int da[MAX_N], db[MAX_N], i, x = a;
    for (i = 0; i < N; i++) {
        db[i] = (i+1 == b) ? 0 : (ping(i+1, b) + 1);
        da[i] = (i+1 == a) ? 0 : (ping(i+1, a) + 1);
    }
    while (db[x-1]) {
        for (i = 0; i < N; i++) 
            if (da[i] == da[x-1] + 1 && db[i] == db[x-1] - 1 && ping(i+1, x) == 0) {
                x = i+1;
                travelTo (x);
                break;
            }
    }
}
