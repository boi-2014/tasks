/*
 * A solution for task Sequence.
 * Complexity - O(K log K).
 *
 * Author: Daumilas Ardickas
 * Idea: Vytautas Gruslys
 */
 
#include <cstdio>
#include <vector>
using namespace std;

long long minN(vector<int>& A, bool try9 = true) {
    long long m = 102345678900000L;
    if (A.size() == 1) {
        m = 0;
        for (int a = 1; a <= 9; a++) 
            if (A[0] & (1 << a)) {
                m = m * 10 + a;
                if (m == a && A[0] & 1) m *= 10;
            }
        return m;
    }
    for (int n = 0; n < 9 + try9; n++) {
        int y = n, a = 0;
        vector<int> B;
        for (int i = 0; i < A.size(); i++) {
            a |= A[i] & (1023 - (1 << y));
            y = (y + 1) % 10;
            if (!y || i == A.size() - 1) {
                B.push_back(a);
                a = 0;
            }
        }
        m = min(m, minN(B, n < 9 || A.size() > 2) * 10 + n);
    }
    return m;
}

int main() {
    int K, d, i;
    vector<int> A;
    scanf("%d", &K);
    for (i = 0; i < K; i++) {
        scanf("%d", &d);
        A.push_back(1 << d);
    }
    printf ("%lld\n", minN(A));
}
