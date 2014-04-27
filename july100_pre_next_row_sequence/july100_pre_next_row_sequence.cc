#include <stdio.h>
#include <vector>
#include "igloo/igloo_alt.h"
using namespace igloo;

#if 0
http://onestraw.net/2014/02/19/tencent-interview-problem/
http://blog.csdn.net/wcyoot/article/details/6428305 (seems incorrect conclusion)
#endif

bool isValid(const std::vector<int>& originVec, const std::vector<int>& numIdxVec, int N){
  for (int i = 0; i < N; ++i) {
    int count = 0;
    for (int j = 0; j < N; ++j) {
      if (numIdxVec[j] == originVec[i]) {
        ++count;
      }
    }
    if (numIdxVec[i] != count) {
      return false;
    }
  }
  return true;
}

void outputValidResult(const std::vector<int>& origVec, const std::vector<int>& numIdxVec) {
  for(auto ovi: origVec) {
    printf("%d ", ovi);
  }
  printf("\n");
  for(auto nivi: numIdxVec) {
    printf("%d ", nivi);
  }
  printf("\n");
}

void solve(const std::vector<int>& origVec, std::vector<int>& numIdxVec, int p, std::vector<int>& retVec) {
  int size = origVec.size();
  if (p == size ) {
    return;
  }
  for(numIdxVec[p] = 0; numIdxVec[p] <= size/(p+1); ++numIdxVec[p]) {
    if (!isValid(origVec, numIdxVec, size) ) {
      solve(origVec, numIdxVec, p+1, retVec);
    }
    else {
      outputValidResult(origVec, numIdxVec);
      retVec.insert(retVec.end(), numIdxVec.begin(), numIdxVec.end() );
    }
  }
}

Describe(pre_next_row_solver) {
  It(from_0_9_reorder) {
    std::vector<int> input{0,1,2,3,4,5,6,7,8,9};
    std::vector<int> numRow;
    numRow.reserve(10);
    numRow.resize(10);
    std::vector<int> finalResult;
    solve(input, numRow, 0, finalResult);
    AssertThat(finalResult, EqualsContainer(std::vector<int>({6,2,1,0,0,0,1,0,0,0}) ) );
  };
  It(no_zero_sequence_reorder) {
    std::vector<int> input{1,2,3,4,5,6,8,7,9,7};
    std::vector<int> numRow;
    numRow.resize(10);
    std::vector<int> finalResult;
    solve(input, numRow, 0, finalResult);
    AssertThat(finalResult, EqualsContainer(std::vector<int>({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0,0,0}) ) );
  }
  //todo more testcase
};

int main(int argc, char *argv[]) {
  return TestRunner::RunAllTests(argc, argv);
}
