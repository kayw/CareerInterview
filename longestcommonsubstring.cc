//http://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Longest_common_substring
#include <iostream>
#include <string.h>
#include <string>
int RetrieveLongestCommonsSubstring(const std::string& str1, const std::string& str2,
                                    std::string& commonSubstring) {
  if (str1.empty() || str2.empty() ) {
    commonSubstring.clear();
    return 0;
  }
  int len1 = str1.length();
  int len2 = str2.length();
  int* pCurr = new int[len2];
  int* pPrev = new int[len2];
  memset(pPrev, 0, len2);
  int* pSwap = nullptr;
  int currSubStart = 0;
  int lastSubStart = 0;
  int maxSubLen = 0;
  for (int i = 0; i < len1; ++i) {
    for (int j = 0; j < len2; ++j) {
      if (str1[i] != str2[j]) {
        pCurr[j] = 0;
      }
      else {
        if (i == 0 || j == 0) {
          pCurr[j] = 1;
        }
        else {
          pCurr[j] = pPrev[j-1] + 1;
        }
        //maxSubLen = std::max(maxSubLen, pCurr[j]);  
        if (maxSubLen < pCurr[j]) {
          maxSubLen = pCurr[j];
          currSubStart = i - pCurr[j] + 1;
          if (currSubStart == lastSubStart) {
            commonSubstring.append(1, str2[j]);
          }
          else {
            lastSubStart = currSubStart;
            commonSubstring.clear();
            commonSubstring = str1.substr(lastSubStart, i+1-lastSubStart);
          }
        }
      }
    }
    pSwap = pCurr;
    pCurr = pPrev;
    pPrev = pSwap;
  }
  return maxSubLen;
}

int main(int /*argc*/, char */*argv*/[]) {
  std::string str1 = "zabcdefghijk";
  std::string str2 = "lmnopabcdrst";
  std::string commonStr;
  int maxCommLen = RetrieveLongestCommonsSubstring(str1, str2, commonStr);
  std::cout << "max substring: " << commonStr << " length " << maxCommLen << std::endl;
  
  {
    //http://www.geeksforgeeks.org/longest-common-substring/
  std::string str1 = "OldSite:GeeksforGeeks.org";
  std::string str2 = "NewSite:GeeksQuiz.com";
  std::string commonStr;
  int maxCommLen = RetrieveLongestCommonsSubstring(str1, str2, commonStr);
  std::cout << "max substring: " << commonStr << " length " << maxCommLen << std::endl;
  }
  return 0;
}

//http://www.cnblogs.com/ider/p/longest-common-substring-problem-optimization.html
