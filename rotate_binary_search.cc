#include <stdio.h>
#include <functional>
//careercup 9.3
/**
 * assume the rotate sorted array is in ascending order & without duplicates
 * @param rotateSortedInt
 *   	given search array     
 * @param searchOne
 *   	element number to be found
 * @return element index in the given array
 */
//http://stackoverflow.com/questions/11179476/array-type-deduction-in-a-function-template
//http://stackoverflow.com/questions/472530/how-to-pass-an-array-size-as-a-template-with-template-type
//http://stackoverflow.com/questions/499106/what-does-template-unsigned-int-n-mean
template<int N>
int findElementInRotateSortedArray(const int (&rotateSortedInt)[N], const int searchOne) {
  int upper = N - 1;
  int lower = 0;
  while(lower <= upper) {
    int mid = lower + (upper - lower)/2; // consider addition overflow
    if (rotateSortedInt[mid] == searchOne) {
      return mid;
    } else if (rotateSortedInt[lower] <= rotateSortedInt[upper]) {
      if (rotateSortedInt[mid] < searchOne) {
        lower = mid + 1;
      } else if (rotateSortedInt[lower] <= searchOne) { // when s <= a[m] && s >= a[l] means the l -> m range
        upper = mid - 1; 
      } else {
        lower = mid + 1;
      }
    } else if (rotateSortedInt[mid] > searchOne && rotateSortedInt[lower] <= searchOne) {
      upper = mid - 1;
    } else if (rotateSortedInt[upper] >= searchOne) {
      lower = mid + 1;
    } else {
      upper = mid - 1;
    }
  }
  return -1;
}

//http://leetcode.com/2010/04/searching-element-in-rotated-array.html
template<int N>
int findLeetCodeVersion(int (&array)[N], const int x) {
  int l = 0;
  int r = N - 1;
  while (l <= r) {
    int m = l + (r - l)/2;
    if (array[m] == x)
      return m;
    if (array[l] <= array[m]) {
      //left part subarray sorted
      if (array[l] <= x && x < array[m]) {
        r = m - 1;
      }
      else {
        l = m + 1;
      }
    }
    else {
      if (array[m] < x && x <= array[r]) {
        l = m + 1;
      }
      else {
        r = m - 1;
      }
    }
  }
  return -1;
}

/**
 * Implement the following function, FindSortedArrayRotation, which takes as its input an array of unique integers that has been sorted in ascending order, then rotated by an unknown amount X where 0 <= X <= (arrayLength - 1). An array rotation by amount X moves every element array[i] to array[(i + X) % arrayLength]. FindSortedArrayRotation discovers and returns X by examining the array.  
 *
 * @param 
 *   	     
 * @return 
 */
template<int N>
int findRotateSortPivot(int (&RSArray)[N]) {
  int l = 0;
  int r = N - 1;
  while (RSArray[l] > RSArray[r]) {
    int m = l + (r - l)/2;
    if (RSArray[m] > RSArray[r]) {
      l = m + 1;
    }
    else {
      r = m;
    }
  }
  return l;
}

/**
 *  
 *
 * @param cmp
 *   	a increasing order means a[i] < a[i+1] => less
 * @return 
 */
template<int N, class Pred>
int binarySearch(int (&a)[N], int lo, int hi, const int x, const Pred& cmp){
  while (lo <= hi) {
    int mid = lo + (hi - lo)/2;
    if (a[mid] == x) {
      return mid;
    }
    else if (cmp(a[mid], x) ) {// x's index should be larger than mid
      lo = mid + 1;
    }
    else {
      hi = mid - 1;
    }
  }
  return -1;
}
/**
 * Given an array which is monotonically increasing order till certain point and started decreasing after that point. Find whether a number exist in it or not. Ex: {1,3,5,7,11,9,6,2} Find whether 6 exist or not. 
 *
 * @param 
 *   	     
 * @return 
 */
template<int N>
int findInIncreasingDecresingSeq(int (&a)[N],const int l, const int h, const int x) {
  //http://stackoverflow.com/questions/19372930/given-a-bitonic-array-and-element-x-in-the-array-find-the-index-of-x-in-2logn
  while (l <= h) {
    int mid = l + (h - l)/2;
    if (x == a[mid])
      return mid;
    if ((mid == 0 || a[mid - 1] < a[mid]) && (mid = N - 1 || a[mid] < a[mid+1]) ) {
      // in left increasing part
#if 0 
      [3,4,7, 10, 5, 2] -> 5: Invalid
      if (x < a[mid]) {
        h = mid - 1;
      } 
      else {
        l = mid + 1;
      }
#endif
      //http://stackoverflow.com/questions/279854/how-do-i-sort-a-vector-of-pairs-based-on-the-second-element-of-the-pair
      int found = binarySearch(a, l, mid - 1, x, std::less<int>() );//binarySearchAscending(a, l, mid - 1, x);
      if (found != -1)
        return found;
      return findInIncreasingDecresingSeq(a, mid + 1, h, x);
    }
    else if ((mid == 0 || a[mid - 1] > a[mid]) && (mid == N - 1 || a[mid] > a[mid+1]) ) {
#if 0
      if (x < a[mid]) {
        l = mid + 1;
      }
      else {
        h = mid - 1;
      }
#endif
      int found = binarySearch(a, mid + 1, h, x, std::greater<int>() );//binarySearchDescending(a, mid + 1, h, x);
      if (found != -1)
       return found;
      return findInIncreasingDecresingSeq(a, l, mid - 1, x); 
    }
    else {
      // in turning point
      int found = binarySearch(a, l, mid - 1, x, std::less<int>() );
      if (found != -1)
        return found;
      return binarySearch(a, mid+1, h, x, std::greater<int>() );
    }
  }
  return -1;
}

template<int N>
int findMaxIndexInBitonic(int (&a)[N]) {
  //http://www.geeksforgeeks.org/find-the-maximum-element-in-an-array-which-is-first-increasing-and-then-decreasing/
  int lo = 0;
  int hi = N - 1;
  int mid = -1;
  while (lo <= hi) {
    mid = lo + (hi - lo)/2;
    int now = a[mid];
    int left = (mid == 0) ? a[mid] : a[mid - 1];
    int right = (mid == N -1) ? a[mid] : a[mid + 1];
    if (left < now && now < right) {
      hi = mid - 1;
    }
    else if (left > now && now > right) {
      lo = mid + 1;
    }
    else { // split point
      break;
    }
  }
  return mid;
}
//http://stackoverflow.com/questions/1878769/searching-a-number-in-a-rotated-sorted-array
int main(int /*argc*/, char */*argv*/[]) {
  int array[] = {15, 16, 19, 20, 25, 1, 3, 4, 5,7, 10, 14 };
  printf("5's index in array: %d\n", findElementInRotateSortedArray(array, 5) );
  int array2[] = {17, 19, 20, 25, 4, 7, 10};
  printf("7's index in array: %d\n", findElementInRotateSortedArray(array2, 7) );
  printf("5's index in array: %d\n", findElementInRotateSortedArray(array2, 5) );

  printf("7's index in leetcode version: %d\n", findLeetCodeVersion(array2, 7) );

  int array3[] = {6, 8, 1, 2, 4, 5};
  printf("rotate pivot is %d\n", findRotateSortPivot(array3) );

  int array4[] = {1, 1, 0, 1, 1, 1, 1};
  printf("0' s index in duplicate array: %d\n", findLeetCodeVersion(array4, 0) );

  int array5[] = {2, 5, 9, 13, 8, 6, 4};
  printf("max index in array5: %d\n", findMaxIndexInBitonic(array5) );
  //http://stackoverflow.com/questions/37538/how-do-i-determine-the-size-of-my-array-in-c
  printf("6's index in array5: %d\n", findInIncreasingDecresingSeq(array5, 0, sizeof(array5)/sizeof(array[0])-1, 6) );
  return 0;
}
