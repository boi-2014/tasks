#include "network.h"

void findRoute (int N, int a, int b)
{
    /*
     *  Obviously, this is not a good solution.
     *  Replace it with your own code.
     */

    int dist = ping(a, b);
    for (int i = 1; i <= dist; ++i)
        travelTo (i);
}
