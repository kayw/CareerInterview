//http://oj.leetcode.com/problems/search-for-a-range/
#include <assert.h>
template<int N>
int searchLowRange(const int (&a)[N], const int x, int lowBound, int highBound) {
  int lo = lowBound;
  int hi = highBound;
  int rvRange = -1;
  while(lo <= hi) {
    int mid = lo + ((hi - lo)>>1);
    if (a[mid] == x) {
      hi = mid - 1;
      rvRange = mid;
    }
    else if (a[mid] < x) {
      lo = mid + 1;
    }
    else {
      assert(false);
    }
  }
  return rvRange;
}
template<int N>
int searchHighRange(const int (&a)[N], const int x, int lowBound, int highBound) {
  int lo = lowBound;
  int hi = highBound;
  int rvRange = -1;
  while(lo <= hi) {
    int mid = lo + ((hi - lo)>>1);
    if (a[mid] == x) {
      lo = mid + 1;
      rvRange = mid;
    }
    else if (a[mid] > x) {
      hi = mid - 1;
    }
    else {
      assert(false);
    }
  }
  return rvRange;
}

template<int N>
void searchValueRange(const int (&a)[N], const int x, int& lowBound, int& highBound) {
  int lo = 0;
  int hi = N - 1;
  while(lo <= hi) {
    int mid = lo + ((hi - lo)>>1);
    if (a[mid] == x) {
      highBound = searchHighRange(a,x, mid+1, hi);
      lowBound = searchLowRange(a, x,lo, mid-1);
      if (highBound == -1) {
        highBound = mid;
      }
      if (lowBound == -1) {
        lowBound = mid;
      }
      break;
    }
    else if (a[mid] > x) {
      hi = mid - 1;
    }
    else {
      lo = mid + 1;
    }
  }
}

#include <vector>
using std::vector;
class Solution {
  public:
    vector<int> searchRange(int A[], int n, int target) {
      int lo = 0;
      int hi = n - 1;
      int highBound = -1;
      int lowBound = -1;
      while(lo <= hi) {
        int mid = lo + ((hi - lo)>>1);
        if (A[mid] == target) {
          highBound = searchHighRange(A,target, mid+1, hi);
          lowBound = searchLowRange(A, target,lo, mid-1);
          if (highBound == -1) {
            highBound = mid;
          }
          if (lowBound == -1) {
            lowBound = mid;
          }
          break;
        }
        else if (A[mid] > target) {
          hi = mid - 1;
        }
        else {
          lo = mid + 1;
        }
      }
      vector<int> rvVec;
      rvVec.push_back(lowBound);
      rvVec.push_back(highBound);
      return rvVec;
    }

  private:
    int searchLowRange(const int a[], const int x, int lowBound, int highBound) {
      int lo = lowBound;
      int hi = highBound;
      int rvRange = -1;
      while(lo <= hi) {
        int mid = lo + ((hi - lo)>>1);
        if (a[mid] == x) {
          hi = mid - 1;
          rvRange = mid;
        }
        else if (a[mid] < x) {
          lo = mid + 1;
        }
        else {
          //assert(false);
        }
      }
      return rvRange;
    }

    int searchHighRange(const int a[], const int x, int lowBound, int highBound) {
      int lo = lowBound;
      int hi = highBound;
      int rvRange = -1;
      while(lo <= hi) {
        int mid = lo + ((hi - lo)>>1);
        if (a[mid] == x) {
          lo = mid + 1;
          rvRange = mid;
        }
        else if (a[mid] > x) {
          hi = mid - 1;
        }
        else {
          //assert(false);
        }
      }
      return rvRange;
    }
};

namespace LEETCODE_REF {
//http://discuss.leetcode.com/questions/213/search-for-a-range
class Solution {
public:
    vector<int> searchRange(int A[], int n, int target) {
        vector<int> range(2, -1);
        int lower = 0;
        int upper = n;
        int mid;

        // Search for lower bound
        while (lower < upper) {
            mid = (lower + upper) / 2;
            if (A[mid] < target)
                lower = mid + 1;
            else
                upper = mid;
        }

        // If the target is not found, return (-1, -1)
        if (A[lower] != target)
            return range;
        range[0] = lower;

        // Search for upper bound
        upper = n;
        while (lower < upper) {
            mid = (lower + upper) / 2;
            if (A[mid] > target)
                upper = mid;
            else
                lower = mid + 1;
        }
        range[1] = upper - 1;

        return range;
    }
};
}

//[8,8,8,8,8] 8
//[1,2,4,5,5,5,5,8] 5
//[1,2,3,4,5] 6
int main(int /*argc*/, char */*argv*/[]) {
  int high = -1;
  int low = -1;
  int arr1[5] = {8, 8, 8, 8, 8};
  searchValueRange(arr1, 8, low, high);
  assert((low == 0) && (high == 4) );

  high = -1;
  low = -1;
  int arr2[] = {1,2,4,5,5,5,5,8};
  searchValueRange(arr2, 5, low, high);
  assert((low == 3) && (high == 6) );

  high = -1;
  low = -1;
  int arr3[] = {1,2,3, 4,5};
  searchValueRange(arr3, 6, low, high);
  assert((low == -1) && (high == -1) );

  high = -1;
  low = -1;
  int arr_leet[] = {5, 7, 7, 8, 8, 10};
  searchValueRange(arr_leet, 8, low, high);
  assert((low == 3) && (high == 4) );

  Solution sol;
  vector<int> vecInt = sol.searchRange(arr_leet, 6, 8);
  assert((vecInt[0] == 3) && (vecInt[1] == 4) );

  vecInt = sol.searchRange(arr3, 5, 6);
  assert((vecInt[0] == -1) && (vecInt[1] == -1) );

  vecInt = sol.searchRange(arr1, 5, 8);
  assert((vecInt[0] == 0) && (vecInt[1] == 4) );
  return 0;
}
