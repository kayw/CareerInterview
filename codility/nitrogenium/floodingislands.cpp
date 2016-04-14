/*
 *
The city of Codicity is located at the seaside. The city area comprises N plots located along a boulevard on one side of the city. Each plot is flat, but different plots have different heights above the sea level. The relative heights of the consecutive plots are given in the form of a non-empty zero-indexed array A of N integers.

The sea level changes constantly and many plots are sometimes under water. Water levels on consecutive days are given in the form of a non-empty zero-indexed array B of M integers.

A slice of array A is any pair of integers (P, Q) such that 0 <= P <= Q < N. An island is a slice of consecutive plots that rise above the waters surface. The plots on either side of each island are under water. More precisely, if the level of the water is K, then an island is a slice (P, Q) in which the level of each plot A[P], A[P + 1], ..., A[Q] is greater than K. Both of the adjacent plots should also be under water; that is:

        P = 0 or A[P - 1] > K
        Q = N - 1 or A[Q + 1] < K

The goal is to calculate the number of islands on consecutive days.

For example, given the following arrays A and B:

    A[0] = 2    B[0] = 0
    A[1] = 1    B[1] = 1
    A[2] = 3    B[2] = 2
    A[3] = 2    B[3] = 3
    A[4] = 3    B[4] = 1

We have the following number of islands on consecutive days:

        on the first day there is only 1 island: (0, 4),
        on the second day there are 2 islands: (0, 0) and (2, 4),
        on the third day there are 2 islands: (2, 2) and (4, 4),
        on the fourth day there aren't any islands,
        on the fifth day there are 2 islands: (0, 0) and (2, 4).

Write a function:

    vector<int> solution(vector<int> &A, vector<int> &B); 

that, given a non-empty zero-indexed array A of N integers and a non-empty zero-indexed array B of M integers, returns a sequence consisting of M integers representing the number of islands on consecutive days.

The sequence should be returned as:

        a structure Results (in C), or
        a vector of integers (in C++), or
        a record Results (in Pascal), or
        an array of integers (in any other programming language).

For example, given:

    A[0] = 2    B[0] = 0
    A[1] = 1    B[1] = 1
    A[2] = 3    B[2] = 2
    A[3] = 2    B[3] = 3
    A[4] = 3    B[4] = 1

the function should return the array [1, 2, 2, 0, 2], as explained above.

Assume that:

        N and M are integers within the range [1..30,000];
        each element of array A is an integer within the range [0..100,000];
        each element of array B is an integer within the range [0..100,000].

Complexity:

        expected worst-case time complexity is O(N+M+max(A)+max(B));
        expected worst-case space complexity is O(N+M+max(A)+max(B)), beyond input storage (not counting the storage required for input arguments).

Elements of input arrays can be modified.
*/
/*http://codereview.stackexchange.com/questions/33716/codility-fish-question-on*/

#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
#include "file.h"
#define _USE_NATIVE_IMPL_STRING
#include "mstring.h"
#include "timeclock.h"
void prepareIslandsByPlotHeights(const std::vector<int>& A, std::vector<int>& islands_per_level) {
  int previous = 0;
  std::vector<int>::const_iterator plotHeightIter = A.begin();
  for (; plotHeightIter != A.end(); ++plotHeightIter)
  {
    if (*plotHeightIter > previous)
    {
      ++islands_per_level[*plotHeightIter - 1 ];
      if (previous)
      {
        --islands_per_level[previous - 1];
      }
    }
    previous = *plotHeightIter;
  }
}

void determineIslandsPerLevel(std::vector<int>& islands_per_level) {
  std::vector<int>::reverse_iterator tmpIslandsIter = islands_per_level.rbegin();
  int tmp = *tmpIslandsIter;
  std::vector<int>::reverse_iterator curIslandsIter = tmpIslandsIter;
  ++curIslandsIter;
  while(curIslandsIter != islands_per_level.rend() ) {
    *curIslandsIter += tmp;
    if (*curIslandsIter)
    {
      tmp = *curIslandsIter;
    }
    ++curIslandsIter;
  }
}

//http://stackoverflow.com/questions/9874802/how-can-i-get-the-max-or-min-value-in-a-vector-c
//template <typename T, size_t N> const T* mybegin(const T (&a)[N]) { return a; }
//template <typename T, size_t N> const T* myend(const T (&a)[N]) { return a+N; }
//
std::vector<int> solution(std::vector<int> &A, std::vector<int> &B) {
  //int maxLevel = std::max(A.size(), B.size() );
  //http://stackoverflow.com/questions/10158756/using-stdmax-element-on-a-vectordouble
  int maxLevel = std::max(*std::max_element(A.begin(), A.end() ), *std::max_element(B.begin(), B.end() ) ) + 1;
  std::vector<int> islands_per_level(maxLevel, 0);
  prepareIslandsByPlotHeights(A, islands_per_level);
  determineIslandsPerLevel(islands_per_level);
  std::vector<int> islands;
  for (std::vector<int>::const_iterator waterlevelIter = B.begin(); waterlevelIter 
       != B.end(); ++waterlevelIter)
  {
    islands.push_back(islands_per_level[*waterlevelIter]);
  }
  return islands;
}

void ExtractIntVector(const char*& startPos, const char* endPos, std::vector<int>& intVec) {
  //printf("[");
  while(startPos < endPos && *startPos != ']') { 
    while(*startPos == ' ' || *startPos == '\t' || *startPos == '[') ++startPos;
    const char* begin = startPos;
    while(*++startPos != ','&& *startPos != ']');
    const char* end = startPos;
    mnb::StringRef sr(begin, end);
    int val;
    mnb::MString::toInteger(sr, val);
    intVec.push_back(val);
    //printf("%d", val);
    if (*startPos == ',') {
      //printf(",");
      ++startPos;
    }
  }
  ++startPos;
  //printf("]\n");
}

//http://www.qtcentre.org/archive/index.php/t-39725.html
int main(int /*argc*/, char */*argv*/[])
{
  mnb::File f;
  f.open("case-data", mnb::File::kMode_Read);
  std::string ioputs;
  int i = 0;
  mnb::TimeTick tt;
  while(f.readline(ioputs) ) {
    //const char* begin = ioputs.cbegin();
    const char* begin = ioputs.data();
    const char* end = begin + ioputs.length();
    std::vector<int> plots;
    std::vector<int> waterlevels;
    std::vector<int> answers;
    ExtractIntVector(begin, end, plots);
    ExtractIntVector(begin, end, waterlevels);
    ExtractIntVector(begin, end, answers);
    mnb::TimeTick t;
    std::vector<int> answers_here = solution(plots, waterlevels);
    //http://stackoverflow.com/questions/2844/how-do-you-printf-an-unsigned-long-long-int
    printf("solution %d takes %llu us\n", ++i, t.elapseInMicroseconds() );
    if(answers != answers_here)
      printf("solution %d failed\n",  i); 
    else
      printf("solution %d succeed\n", i);
    ioputs.clear();
    printf("solution %d total takes %llu us\n", i, tt.elapseInMicroseconds() );
    mnb::TimeTick tt;

  }
  return 0;
}
