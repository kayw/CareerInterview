//clang++ -std=c++11 -g
#include "heapsort.hpp"
#include "merge_quick_sort.hpp"
#include "O_n2_sort.hpp"

#include <stdio.h>
#include <functional>
#include <random>
int main(int /*argc*/, char */*argv*/[]) {
  int arr[9] = {8,4,6,3, 12, 17,14, 1, 25};
  heapSort<int, std::less<int>, 9>(arr);
  for (int i = 0; i < 9; ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  int arr_equal[8] = {2, 2, 2, 2, 2, 2, 2, 2};
  heapSort<int, std::less<int>, 8>(arr_equal);
  for (int i = 0; i < 8; ++i) {
    printf("%d ", arr_equal[i]);
  }
  printf("\n");

  //int arr_sorted[] = {1, 2,3,4,5};
  //int arr_reversesorted[] = {10, 8, 7, 6, 5, 4, 2,0};
  int arr2[7] = {1, 2, 3, 6, 9, 5, 7};
  heapSort<int, std::less<int>, 7>(arr2);
  for (int i = 0; i < 7; ++i) {
    printf("%d ", arr2[i]);
  }
  printf("\n");
  std::default_random_engine gen((std::random_device())() );
  std::uniform_int_distribution<int> dis(1, 2000);
  int randarr[200] = {0};
  int randarr1[200] = {0};
  for (int i = 0; i < 200; ++i) {
    randarr[i] = dis(gen);
    randarr1[i] = dis(gen);
  }
  heapSort<int, std::greater<int>, 200>(randarr);
  for (int i = 0; i < 200; ++i) {
    printf("%d ", randarr[i]);
  }
  printf("\n");
  selectSort<int, std::less<int>, 200>(randarr1);  
  for (int i = 0; i < 200; ++i) {
    printf("%d ", randarr1[i]);
  }
  printf("\n");

  int arr4merge[20] = {};
  int arr4quick[20] = {};
  int arr4inssort[20] = {};
  int arr4bubble[20] = {};
  int arr4inssortCLRS[20] = {};
  for (int i = 0; i < 20; ++i) {
    arr4merge[i] = dis(gen);
    arr4quick[i] = dis(gen);
    arr4bubble[i] = dis(gen);
    arr4inssort[i] = dis(gen);
    arr4inssortCLRS[i] = dis(gen);
  }
  mergeSort<int, std::less<int>, 20>(arr4merge);
  for (int i = 0; i < 20; ++i) {
    printf("%d ", arr4merge[i]);
  }
  printf("\n");
  quickSort<int, std::less<int>, 20>(arr4quick);
  for (int i = 0; i < 20; ++i) {
    printf("%d ", arr4quick[i]);
  }
  printf("\n");
  insertSort<int, std::less<int>, 20>(arr4inssort);
  for (int i = 0; i < 20; ++i) {
    printf("%d ", arr4inssort[i]);
  }
  printf("\n");
  bubbleSort<int, std::less<int>, 20>(arr4bubble);
  for (int i = 0; i < 20; ++i) {
    printf("%d ", arr4bubble[i]);
  }
  printf("\n");
  insertSortCLRS<int, std::less<int>, 20>(arr4inssortCLRS);
  for (int i = 0; i < 20; ++i) {
    printf("%d ", arr4inssortCLRS[i]);
  }
  printf("\n");
  return 0;
}
