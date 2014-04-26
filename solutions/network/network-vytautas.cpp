/**
 * Correct solution to Network.
 *
 * Author: Vytautas Gruslys
 */

#include <vector>
#include "network.h"

using namespace std;
const int MaxN = 1001;

vector<int> S[MaxN];
int dist;

void findRoute(int N, int x, int y)  {
    dist = ping(x, y);
    for (int i = 1; i <= N; i++)
        if (i != x && i != y)
            S[ping(i, y)].push_back(i);
    int u = x; dist--;
    while (dist >= 0) {
        int j = 0; 
        while (ping(S[dist][j], u) != 0) 
            j++;
        u = S[dist][j];
        dist --;
        travelTo(u);
    }
    travelTo(y);    
}
