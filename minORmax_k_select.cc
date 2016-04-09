//http://blog.csdn.net/v_JULY_v/article/details/6370650
#include <vector>
#include "practice_base/heapsort.hpp"
template<typename T, typename Comp, int N>
void heapSelect(T (&arr)[N], int k, std::vector<T>& kthVec) {
  // todo only need k heap
  Heap<T, Comp, N> h(arr, N);
  for (int i = 0; i < k; ++i) {
    kthVec.push_back(h.popFront() );
  }
}

//top link's seventh section
template<typename T, typename Comp, int N>
int partition(T (&arr)[N], int head, int tail) { //from CLRS quicksort partition
  int posSlow = head - 1;
  int posFast = head;
  for (; posFast < tail; ++posFast) {
    if (arr[posFast] < arr[tail]) {
      ++posSlow;
      std::swap(arr[posSlow], arr[posFast]);
    }
  }
  ++posSlow;
  std::swap(arr[posSlow], arr[tail]);
  return posSlow;
}
template<typename T, typename Comp, int N>
void quickSelect(T (&arr)[N], int left, int right, int k, std::vector<T>& kthVec) {
  if (left < right) {
    int mid = partition<T, Comp, N>(arr, left, right);
    if (mid > k) {
      quickSelect<T, Comp, N>(arr, left, mid - 1, k, kthVec);
    }
    else if (mid < k) {
      quickSelect<T, Comp, N>(arr, mid + 1, right, k, kthVec);
    }
  }
}

//http://en.wikipedia.org/wiki/Selection_algorithm#Linear_general_selection_algorithm_-_Median_of_Medians_algorithm
template<typename T, typename Comp, int N>
void BFPRTSelect(T (&arr)[N], int k, std::vector<T>& kthVec) {
  if (k > N) {
    assert(false && "no enough k element to select");
    return;
  }
  quickSelect<T, Comp, N>(arr, 0, N - 1, k, kthVec);
}

//https://www.v2ex.com/t/182407
//a[N] K[r]  O(Nlogr)
//首先把 K 排序，取第 r/2 个元素，SELECT 从 S 中找到第 K(r/2) 小元素 S(r/2)。
//将 S 按照 S(r/2) 分割为两半，一半全小于 S(r/2) 一半全大于 S(r/2)。
//在小的那一半中查找 K(j<r/2)，在大的那一半查找 K(j>r/2)。
#include <random>
int main(int /*argc*/, char */*argv*/[]) {
  int arr[9] = {8,4,6,3, 12, 17,14, 1, 25};
  std::vector<int> selectk;
  heapSelect<int, std::less<int>, 9>(arr, 4, selectk);

  for(auto sk: selectk) {
    printf("%d ", sk);
  }
  printf("\n");

  std::default_random_engine gen((std::random_device())() );
  std::uniform_int_distribution<int> dis(1, 2000);
  int randarr[20] = {0};
  for (int i = 0; i < 20; ++i) {
    randarr[i] = dis(gen);
    printf("%d ", randarr[i]);
  }
  printf("\n");
  BFPRTSelect<int, std::less<int>, 20>(randarr, 5, selectk); 
  for (int i = 0; i < 5; ++i) {
    printf("%d ", randarr[i]);
  }
  printf("\n");
  return 0;
}
