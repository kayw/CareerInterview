//http://hawstein.com/posts/9.1.html
#include <stdio.h>
void mergeBackwards(int a[], int b[], int an, int bn) {
  int i = an-1;
  int j = bn-1;
  int k = an+bn-1;
  while(i >= 0 && j >= 0) {
    if (a[i] > b[j]) {
      a[k--] = a[i--];
    }
    else {
      a[k--] = b[j--];
    }
  }
  while (j >= 0) {
    a[k--] = b[j--];
  }
}

int main(int /*argc*/, char */*argv*/[]) {
  int a[20] = {1, 3, 7, 9, 13, 29};
  int b[6] = {2, 5, 11, 22, 23};
  mergeBackwards(a, b, 6, 5);
  for (int i = 0; i < 11; ++i) {
    printf("%d ", a[i]);
  }
  printf("\n");
  return 0;
}
