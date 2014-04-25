#include <cstdio>

int main()
{
    long long A, B;
    scanf ("%lld%lld", &A, &B);
    
    if (A > B) {
        long long tmp = B;
        B = A;
        A = tmp;
    }

    if (B < A+2) {
        printf ("0\n");
    } else {
        printf ("%lld\n", B-A-1);
        for (long long i = A+1; i < B; ++i) {
            if (i > A+1)
                printf (" ");
            printf ("%lld", i);
        }
    }

    return 0;
}

