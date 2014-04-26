#include <cstdio>
int main() {
  long long A, B, i;
  scanf("%lld%lld", &A, &B);
  printf ("%d\n", B == A ? 0 : B - A - 1);
  for (i = A + 1; i < B; i++) printf ("%lld ", i);
}