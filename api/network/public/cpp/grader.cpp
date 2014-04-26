#include <cstdio>
#include <cstdlib>

#include "network.h"

static const int MAX_N = 1010;

static int N, a, b, M,
           pingCount,
           routeLength, current;
static int distance[MAX_N][MAX_N];

static void raiseError (const char* message)
{
    printf ("ERROR\n%s\n", message);
    exit (0);
}

int ping (int i, int j)
{
    if (i < 1 || j < 1 || i > N || j > N || i == j)
        raiseError ("ping called with invalid arguments");

    ++pingCount;
    if (pingCount > M)
        raiseError ("Too many calls to ping");

    return distance[i-1][j-1];
}

void travelTo (int k)
{
    if (k < 1 || k > N)
        raiseError ("travelTo called with invalid argument");

    if (k == current || distance[current-1][k-1] > 0)
        raiseError ("Travelling to nonadjacent computer");

    ++routeLength;
    if (routeLength > distance[a-1][b-1] + 1)
        raiseError ("Route is too long");

    current = k;
}

int main()
{
    scanf ("%d%d%d%d", &N, &a, &b, &M);
    for (int u = 0; u < N; ++u)
        for (int v = 0; v < N; ++v)
            scanf("%d", &distance[u][v]);

    pingCount = 0;
    routeLength = 0;
    current = a;

    findRoute (N, a, b);

    if (current != b)
        raiseError ("Message has not reached its target");

    if (routeLength < distance[a-1][b-1] + 1)
        raiseError ("Unexpected: route is too short");

    printf ("OK\n");

    return 0;
}
