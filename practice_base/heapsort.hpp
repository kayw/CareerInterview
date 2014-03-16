#ifndef HEAPSORT_HPP_BF6FECE1_DD9D_41AA_BCBC_8E9F5F06FFF3
#define HEAPSORT_HPP_BF6FECE1_DD9D_41AA_BCBC_8E9F5F06FFF3

#include <assert.h>
#include <algorithm>
//Comp::operator() a binary boolean function return true if first element should come before the second in the heap
template<typename Elem, typename Comp, int maxN>
class Heap {
  public:
    Heap(Elem (&h)[maxN], int num) 
      : heap_(h), num_(num) {
        buildHeap();
      }

    int size() const { return num_; }
    bool isLeaf(const int pos) const { return (pos*2 >= num_) && (pos < num_); }
    int leftChild(const int pos) const { return 2*pos + 1; }
    int rightChild(const int pos) const { return 2*pos + 2; }
    int parent(const int pos) const { return (pos-1)/2; }
    void buildHeap() {
      for (int i = num_/2 - 1; i >= 0; --i) {
        siftDown(i); 
      }
    }

    Elem popFront() {
      assert(num_ > 0 && "heap is empty");
      std::swap(heap_[0], heap_[--num_]);
      if (num_ != 0) {
        siftDown(0); //siftdown new root value
      }
      return heap_[num_];
    }
    void pushElem(const Elem& e) {
      assert(num_ < maxN && "heap is full");
      int curr = num_++;
      heap_[curr] = e;
      while (curr != 0 &&
          Comp()(heap_[curr], heap_(parent(curr) ) )  ){
        std::swap(heap_[curr], heap_[parent(curr)]);
        curr = parent(curr);
      }
    }

  private:
    void siftDown(int pos) {
      while (2*pos+1 < num_) {//!isLeaf(pos) ) {
        int l = leftChild(pos);
        int r = l + 1;
        if (r < num_ && Comp()(heap_[r], heap_[l]) ) {
          l = r;
        }
        if (Comp()(heap_[l], heap_[pos]) ) {
            std::swap(heap_[pos], heap_[l]);
        }
        pos = l;
      }
    }
  private:
    Elem* heap_;
    //Elem heap_[maxN]; // heap elements
    int num_;//current number of element in heap
    //int maxSize_; //max number of heap
};

template<typename T, typename Comp, int N>
void heapSort(T (&arr)[N]) {
  Heap<T, Comp, N> h(arr, N);
  for (int i = N - 1; i >= 0; --i) {
    h.popFront();
  }
}

class MaxHeap{
  public:
    template<typename T, int N>
    void sort(T (&a)[N]) {
      buildMaxHeap(a);
      int n = N - 1;
      for(int i = n; i > 0; --i) {
        std::swap(a[0], a[i]);
        --n;
        siftDown(a, i);
      }
#ifdef LIBCXX
      int last = N;
      for (int i = last-1; i > 1; --last, --i) {
        pop(a, 0, last, i);
      };
#endif
    }

    template<typename T, int N>
      void pop(T (&a)[N], int lastIndex, int len) {
        if (len > 1) {
          std::swap(a[0], a[lastIndex]);
          int p = 0;
          T* pp = &(a[0]);
          int c = 2;
          T* cp = &(a[c]);
          if ( c == len || (*cp < *(cp+1) ) ){
            --c;
            --cp;
          }
          if (*pp < *cp) {
            T* t = pp;
            do {
              *pp = *cp;
              pp = cp;
              p = c;
              c = (p+1)*2;
              if (c > len)
                break;
              cp = &(a[c]);
              if (c == len || *cp < *(cp - 1) ) {
                --c;
                --cp;
              }
            } while (*t < *pp);
            *pp = *t;
          }
        }
      }
    template<typename T, int N>
    void buildMaxHeap(T (&a)[N]) {
      for (int i = N/2 - 1; i >= 0; --i)
        siftDown(a, i);
    }
    template<typename T, int N>
    void siftDown(T (&a)[N], int index) {//max-heap
      while (2*index + 1 < N) {
        int l = 2*index + 1;
        if (l + 1 < N && a[l+1] < a[l]) {
          ++l;
        }
        if (a[l] < a[index]) {
          std::swap(a[l], a[index]);
        }
        index = l;
      }
#if INTRO_ALGRO
      int l = 2*index; //index start from 1
      int r = 2*index + 1;
      int largest = -1;
      if (l <= N && a[l] > a[index]) {
        largest = l; 
      }
      else {
        largest = index;
      }
      if (r <= N && a[r] > a[largest]) {
        largest = r;
      }
      if (largest != index) {
        std::swap(a[largest], a[index]);
        siftDown(a, largest);
    }
#endif
  }
  template<typename T, int N>
  void siftUp(T (&a)[N], int index) {
    while (index > 0) {
      int sibling = (index&1) == 0 ? index-1 : index+1;// even node'sibling is odd
      int parent = (index - 1) >> 1;
      if (sibling < N && a[sibling] < a[index]) {
        index = sibling;
      }
      if (a[parent] > a[index] ) {
        std::swap(a[parent], a[index]);
      }
      index = parent;
    }
  }
};


#endif /* HEAPSORT_HPP_BF6FECE1_DD9D_41AA_BCBC_8E9F5F06FFF3 */
