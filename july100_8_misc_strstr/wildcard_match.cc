//http://www.kuqin.com/shuoit/20140105/337440.html
//https://github.com/julycoding/The-Art-Of-Programming-By-July/blob/master/ebook/zh/01.03.md
//http://discuss.leetcode.com/questions/222/wildcard-matching
//http://blog.csdn.net/moon789/article/details/20444959 (dp method explaination incorrect)
#include "igloo/igloo_alt.h"
using namespace igloo;

#include <vector>
#include <string>
bool asterisk_interrogation_wild_match(const std::string& input, const std::string& pattern, std::vector<std::string>& matches) {
  int textLength = input.length();
  int patLength = pattern.length();
#ifdef _TWO_SWAP_DP_ARRAY_ENOUGH // is it possible like 
  std::vector<int> currLenRecord(patLength+1, -1);// input[i] -> pattern[j] : dp[i][j]
  currLenRecord[0] = 0;
  std::vector<int> lastLenRecord(patLength+1, 0);// input[i-1] -> pattern[j]: dp[i-1][j]
  for (int i = 1; i <= textLength; ++i) {
    for (int j = 1; j <= patLength; ++j) {
      if (pattern[j] == '*') {
        if (lastLenRecord[j-1] != -1) {
          currLenRecord[j] = lastLenRecord[j-1] + 1;
        }
        if (lastLenRecord[j] != -1 && currLenRecord[j] < (lastLenRecord[j] + 1) ) {
          currLenRecord[j] = lastLenRecord[j] + 1;
        }
      }
      else if (pattern[j] == '?') {
        if (lastLenRecord[j-1] != -1) {
          currLenRecord[j] = lastLenRecord[j-1] + 1;
        }
      }
      else {
        if (lastLenRecord[j-1] != -1 && input[i-1] == pattern[j-1]) {
          currLenRecord[j] = lastLenRecord[j-1] + 1;
        }
      }
    }
    currLenRecord.swap(lastLenRecord);
  }
  return (lastLenRecord[patLength] != -1);
#else
  std::vector<int> dpj(patLength+1, -1);
  std::vector<std::vector<int>> dpij(textLength+1, dpj);// std::vector(length, initial)
  for (int i = 0; i <= textLength; ++i) {
    dpij[i][0] = 0;
  }
  for (int i = 1; i <= textLength; ++i) {
    for (int j = 1; j <= patLength; ++j) {
      if (pattern[j] == '*') {
        if (dpij[i-1][j-1] != -1) {
          dpij[i][j] = dpij[i-1][j-1] + 1;
        }
        if (dpij[i-1][j] != -1 && dpij[i][j] < (dpij[i-1][j] + 1) ) {
          dpij[i][j] = dpij[i-1][j] + 1;
        }
      }
      else if (pattern[j] == '?') {
        if (dpij[i-1][j-1] != -1) {
          dpij[i][j] = dpij[i-1][j-1] + 1;
        }
      }
      else {
        if (dpij[i-1][j-1] != -1 && input[i-1] == pattern[j-1]) {
          dpij[i][j] = dpij[i-1][j-1] + 1;
        }
      }
    }
  }
  int maxMatchLength = -1;
  //int leftAnchor = 0;
  //int rightAnchor = 0;
  std::vector<int> matchPos;
  std::string matchSegment;
  for (int i = 1; i <= textLength; ++i) {
    if (dpij[i][patLength] > maxMatchLength) {
      maxMatchLength = dpij[i][patLength];
      matchPos.clear();
      matchPos[0] = i - maxMatchLength;
    }
    else if (dpij[i][patLength] != -1 && dpij[i][patLength] == maxMatchLength) {
      matchPos.push_back(i - maxMatchLength);
    }
  }
  bool rv = false;
  int matchNum = matchPos.size();
  if (matchNum > 0) {
    for (int i = 0; i < maxMatchLength; ++i) {
      std::cout << input[i+matchPos[0] ];
      matchSegment.append(input[i+matchPos[0] ], 1);
    }
    matches.push_back(matchSegment);
    for (int j = 1; j < matchNum; ++j) {
      matchSegment.clear();
      std::cout << " "; 
      for (int i = 0; i < maxMatchLength; ++i) {
        std::cout << input[i+matchPos[j] ];
        matchSegment.append(input[i+matchPos[j] ], 1);
      }
      std::cout << std::endl;
      matches.push_back(matchSegment);
    }
    rv = true;
  }
  return rv;
#endif
}

Describe(Wildcard_match) {
  It(case_from_below_link1) {
    std::string text = "Oh year.Today is weekend!";
    std::string pat = "*ye*a*e*";
    matched_strings_.clear();
    bool matched = asterisk_interrogation_wild_match(text, pat, matched_strings_);
    Assert::That(matched, IsTrue() );
  }
  It(case_match_interrogation) {
    std::string text = "abcdefge";
    std::string pat = "*a?c";
    matched_strings_.clear();
    bool matched = asterisk_interrogation_wild_match(text, pat, matched_strings_);
    Assert::That(matched, IsTrue() );
  }
  std::vector<std::string> matched_strings_;
};


//http://www.cnblogs.com/pangxiaodong/archive/2011/09/07/2169588.html (TODO: divide * ? substring parts & lookbehind method)
