#include <stdio.h>
#define T(X,Y,i) (Y & (1<<i)) && (X+=(Y<<i))

int macro_calc(int n) {
  int r = n;
  for (int i = 0; i < 32; ++i) {
    T(r, n, i);
  }
  return r >> 1;
}

int main(void)
{
  int pow3 = macro_calc(3);
  printf("pow3 %d\n", pow3);
  return 0;
}
