#include <stdio.h>
//careercup 9.3
/**
 *
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
  while(lower < upper) {
    int mid = lower + (upper - lower)/2; // consider addition overflow
    if (rotateSortedInt[mid] == searchOne) {
      return mid;
    } else if (rotateSortedInt[lower] < rotateSortedInt[upper]) {
      if (rotateSortedInt[mid] < searchOne) {
        lower = mid + 1;
      } else if (rotateSortedInt[lower] <= searchOne) { // when s <= a[m] && s >= a[l] means the l -> m range
        upper = mid - 1; 
      } else {
        lower = mid + 1;
      }
    } else if (rotateSortedInt[mid] > searchOne) {
      upper = mid - 1;
    } else if (rotateSortedInt[upper] >= searchOne) {
      lower = mid + 1;
    } else {
      upper = mid - 1;
    }
  }
  return -1;
}

int main(int /*argc*/, char */*argv*/[]) {
  int array[] = {15, 16, 19, 20, 25, 1, 3, 4, 5,7, 10, 14 };
  printf("5's index in array: %d\n", findElementInRotateSortedArray(array, 5) );
  return 0;
}
