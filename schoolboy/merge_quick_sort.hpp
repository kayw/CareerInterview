#ifndef MERGE_QUICK_SORT_HPP_B87C72AA_443C_4220_AAE9_800D84CB7274
#define MERGE_QUICK_SORT_HPP_B87C72AA_443C_4220_AAE9_800D84CB7274

#include <algorithm>
template<typename T, typename Comp, int N>
void mergeWithoutBoundCheck(T (&a)[N], T* pTmp, int left, int mid, int right) {
  for (int i = mid; i >= left; --i) {
    pTmp[i] = a[i];
  }
  for (int i = 1; i <= right - mid; ++i) {
    pTmp[right - i + 1] = a[mid + i];
  }
  for (int i = left, j = right, k = left; k <= right; ++k) {
    if (Comp()(pTmp[i], pTmp[j]) ) {
      a[k] = pTmp[i++];
    }
    else {
      a[k] = pTmp[j--];
    }
  }
}

template<typename T, typename Comp, int N>
void merge(T (&a)[N], T* pTmp, int left, int mid, int right) {
  for (int i = left; i <= right; ++i) {
    pTmp[i] = a[i];
  }
  int leftIndex = left;
  int rightIndex = mid + 1;
  for (int curr = left; curr <= right; ++curr) {
    if (leftIndex == mid + 1) {//left array exhausted
      a[curr] = pTmp[rightIndex++];
    }
    else if (rightIndex > right) {//right array exhausted
      a[curr] = pTmp[leftIndex++];
    } 
    else if (Comp()(pTmp[leftIndex], pTmp[rightIndex]) ) {
      a[curr] = pTmp[leftIndex++];
    }
    else {
      a[curr] = pTmp[rightIndex++];
    }
  }
}

template<typename T, typename Comp, int N>
void mSort(T (&a)[N], T* pTemp, int left, int right) {
  if (left < right) {
    int mid = left + ((right - left)>>1);
    mSort<T, Comp, N>(a, pTemp, left, mid);
    mSort<T, Comp, N>(a, pTemp, mid+1, right);
    mergeWithoutBoundCheck<T, Comp, N>(a, pTemp, left, mid, right);
  }
}

template<typename T, typename Comp, int N>
void mergeSort(T (&a)[N]) {
  T* pTempArray = new T[N];
  mSort<T, Comp, N>(a, pTempArray, 0, N-1);
  delete pTempArray;
}


template<typename T, typename Comp, int N>
int partition(T (&a)[N], int left, int right) {
#define _PRACTICAL
#ifndef _PRACTICAL
  for (int i = 0; i < N; ++i) {
    printf("%d ", a[i]);
  }
  printf("\n");
#endif
  int mid = left + ((right - left) >> 1);
  //invariant: a[left] <= a[mid] <= a[right]
  if (Comp()(a[right], a[left]) ) {
    std::swap(a[left], a[right]);
  }
  if (Comp()(a[right], a[mid]) ) {
    std::swap(a[right], a[mid]);
  }
  if (Comp()(a[mid], a[left]) ) {
    std::swap(a[left], a[mid]);
  }
#if 0
  if (Comp()(a[mid], a[left]) ) {
    std::swap(a[left], a[mid]);
  }
  if (Comp()(a[right], a[left]) ) {
    std::swap(a[left], a[right]);
  }
  if (Comp()(a[right], a[mid]) ) {
    std::swap(a[right], a[mid]);
  }
#endif
  std::swap(a[mid], a[right-1]); //hide pivot
#ifndef _PRACTICAL
  for (int i = 0; i < N; ++i) {
    printf("%d ", a[i]);
  }
  printf("\n");
#endif
  int pivot = a[right - 1];
  int i = left;
  int j = right - 1;
  for (; ;) {
    while(Comp()(a[++i], pivot) );
    while(Comp()(pivot, a[--j]) );
    if (i < j) {
      std::swap(a[i], a[j]);
    }
    else {
      break;
    }
  }
#ifndef _PRACTICAL
  for (int i = 0; i < N; ++i) {
    printf("%d ", a[i]);
  }
  printf("\n");
#endif
  std::swap(a[i], a[right - 1]);//restore
#ifndef _PRACTICAL
  for (int i = 0; i < N; ++i) {
    printf("%d ", a[i]);
  }
  printf("\n");
#endif
  return i;
}

template<typename T, typename Comp, int N>
void qSort(T (&a)[N], int left, int right) {
  if (left + 8 <= right) {
    int median = partition<T, Comp, N>(a, left, right);
    qSort<T, Comp, N>(a, left, median -1);
    qSort<T, Comp, N>(a, median+1, right);
  }
}

#include "O_n2_sort.hpp"
template<typename T, typename Comp, int N>
void quickSort(T (&a)[N]) {
  //copy from weiss dsaa in c
  qSort<T, Comp, N>(a, 0, N-1);
  insertSort<T, Comp, N>(a);
}

//http://stackoverflow.com/questions/12937732/number-of-comparisons-made-in-median-of-3-function

#endif /* MERGE_QUICK_SORT_HPP_B87C72AA_443C_4220_AAE9_800D84CB7274 */
