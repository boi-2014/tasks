#include <cstdio>
int main() {
  long long A, B, i;
  scanf("%lld%lld", &A, &B);
  if (B < A) {i = A; A = B; B = i;}
  printf ("%d\n", B - A - 1);
  for (i = A + 1; i < B; i++) printf ("%lld ", i);
}