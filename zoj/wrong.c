#include <stdio.h>
#define N 5

int* func(int* x, int* y) {
  static int t = 0;
  if (*x < *y)
  {
    t += *x;
    printf("%d\n", t);
    return x;
  }
  else
  {
    t += *y;
    printf("%d\n", t);
    return x;
  }
}
main() {
  int i, b = 3;
  int* p, *q, *r;
  q = &b;
  for (i = 1; i <= N; ++i)
  {
    p = &i;
    r = func(p, q);
  }
  printf("%d,%d,%d\n", *p, *q, *r);
}
