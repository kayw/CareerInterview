//http://stackoverflow.com/questions/337664/counting-inversions-in-an-array
#include <stdio.h>
template<int N>
void countAndMerge(int (&a)[N], int* pTmp, int left, int mid, int right, int& inverNum) {
  for (int i = mid; i >= left; --i) {
    pTmp[i] = a[i];
  }
  for (int i = 1; i <= right - mid; ++i) {
    pTmp[right-i+1] = a[mid+i];
  }
  for (int i = left, j = right, k = left; k <= right; ++k) {
    if (pTmp[i] > pTmp[j]) {
      inverNum += mid - i + 1;
      a[k] = pTmp[j--];
    } 
    else {
      a[k] = pTmp[i++];
    }
  }
}

template<int N>
void countInversions(int (&a)[N], int* pTmp, int left, int right, int& invNum) {
  if (left < right) {
    int mid = left + ((right - left) >> 1);
    countInversions(a, pTmp, left, mid, invNum);
    countInversions(a, pTmp, mid+1, right, invNum);
    countAndMerge(a, pTmp, left, mid, right, invNum);
  }
}

template<int N>
void countInversions(int (&a)[N], int& inversions) {
  int* pTmp = new int[N];
  countInversions(a, pTmp, 0, N-1, inversions);
  delete pTmp;
}

#include <random>
int main(int /*argc*/, char */*argv*/[]) {
  std::default_random_engine gen((std::random_device())() );
  std::uniform_int_distribution<int> dis(0, 5000);
  int arr[6] = {};
  for (int i = 0; i < int(sizeof(arr)/sizeof(int) ); ++i) {
    arr[i] = dis(gen);
    printf("%d ", arr[i]);
  }
  printf("\n");
  int inversions = 0;
  countInversions(arr, inversions);
  printf("%d\n", inversions);
  for (int i = 0; i < int(sizeof(arr)/sizeof(int) ); ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");
  return 0;
}
