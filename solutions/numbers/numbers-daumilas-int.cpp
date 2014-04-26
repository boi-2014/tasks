#include <cstdio>
int main() {
  int A, B, i;
  scanf("%d%d", &A, &B);
  if (B < A) {i = A; A = B; B = i;}
  printf ("%d\n", B == A ? 0 : B - A - 1);
  for (i = A + 1; i < B; i++) printf ("%d ", i);
}