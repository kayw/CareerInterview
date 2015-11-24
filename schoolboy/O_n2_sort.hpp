#ifndef O_N2_SORT_HPP_10B8000B_0C4F_4AB6_890B_9D1CD8DD6DB2
#define O_N2_SORT_HPP_10B8000B_0C4F_4AB6_890B_9D1CD8DD6DB2

#include <algorithm>
template<typename T, typename Comp, int maxN>
void insertSort(T (&arr)[maxN]) {
  for (int i = 1; i < maxN; ++i) {
    for (int j = i; j > 0; --j) {
      if (Comp()(arr[j], arr[j-1]) ) {
          std::swap(arr[j], arr[j-1]);
      }
    }
  }
}
template<typename T, typename Comp, int maxN>
void insertSortCLRS(T (&arr)[maxN]) {
  for (int i = 1; i < maxN; ++i) {
    T key = arr[i];
    int j = i - 1;
    while(j >= 0 && Comp()(key, arr[j]) ) {
      arr[j+1] = arr[j];
      --j;
    }
    arr[j+1] = key;
  }
}
//optimize: binary search insertion place

template<typename T, typename Comp, int maxN>
void bubbleSort(T (&arr)[maxN]) {
  for (int i = 0; i < maxN; ++i) {
    for (int j = maxN - 1; j > i; --j) {
      if (Comp()(arr[j], arr[j-1]) ) {
        std::swap(arr[j], arr[j-1]);
      }
    }
  }
}
//optimize: flag for one path comparision if it needn't swap

template<typename T, typename Comp, int maxN>
void selectSort(T (&arr)[maxN]) {
  for (int i = 0; i < maxN - 1; ++i) {
    int low = i;
    for (int j = maxN - 1; j > i; --j) {
     if (Comp()(arr[j], arr[low]) ) {
        low = j;
     } 
    } 
    std::swap(arr[i], arr[low]);
  }
}

#endif /* O_N2_SORT_HPP_10B8000B_0C4F_4AB6_890B_9D1CD8DD6DB2 */
