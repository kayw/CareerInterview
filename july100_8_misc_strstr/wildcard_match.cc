//http://www.kuqin.com/shuoit/20140105/337440.html
//https://github.com/julycoding/The-Art-Of-Programming-By-July/blob/master/ebook/zh/01.03.md             (original about link1)(TODO: divide * ? substring parts & lookbehind method
//字符串匹配问题，给定一串字符串，按照指定规则对其进行匹配，并将匹配的结果保存至output数组中，多个匹配项用空格间隔，最后一个不需要空格
//
//http://discuss.leetcode.com/questions/222/wildcard-matching  ==> about the full string matching
//Implement wildcard pattern matching with support for '?' and '*'.
//'?' Matches any single character.
//'*' Matches any sequence of characters (including the empty sequence).
//The matching should cover the entire input string (not partial).
//
//http://blog.csdn.net/moon789/article/details/20444959 (dp method explaination = 0 assignment incorrect)
//
//considering the greedy or nongreedy matching so the print matches may be different, the link2 implementation is greedy match
#include "igloo/igloo_alt.h"
using namespace igloo;

#include <vector>
#include <string>
//http://stackoverflow.com/a/21361419 (a dp method not tested)
//link4
bool asterisk_interrogation_partial_wild_match(const std::string& input, const std::string& pattern, std::vector<std::string>& matches) {
  int textLength = input.length();
  int patLength = pattern.length();
  // when we don't need output all match result, we may use swap cyclic array for dp
  std::vector<int> dpj(patLength+1, -1);
  std::vector<std::vector<int>> dpij(textLength+1, dpj);// std::vector(length, initial)
  //dpij[i][j] text[0..i] matches pattern[0..j]'s most length
  for (int i = 0; i <= textLength; ++i) {
    dpij[i][0] = 0; // if pattern string length is zero, largest matching string length is zero
  }
  for (int i = 1; i <= textLength; ++i) {
    for (int j = 1; j <= patLength; ++j) {
      if (pattern[j-1] == '*') {
        //maybe need skip multiple asterisks
        int max = -1;
        for (int k = 0; k <= i; ++k) {
          max = dpij[k][j-1] != -1  ? std::max(max, dpij[k][j-1] + i - k) : max;
        }
        dpij[i][j] = max;
      }
      else if (dpij[i-1][j-1] != -1) {
        if (pattern[j-1] == '?' || input[i-1] == pattern[j-1]) {
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
      matchPos.push_back(i - maxMatchLength);
      //matchPos[0] = i - maxMatchLength;
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
    std::cout << std::endl;
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
}

//copyright@chpeih 2013/4/23
char* my_find(char input[], char rule[])
{
    //write your code here
    int len1, len2;
    for (len1 = 0; input[len1]; len1++);
    for (len2 = 0; rule[len2]; len2++);
    //int MAXN = len1 > len2 ? (len1 + 1) : (len2 + 1);
    int  **dp;
    //dp[i][j]表示字符串1和字符串2分别以i j结尾匹配的最大长度
    //记录dp[i][j]是由之前那个节点推算过来  i*MAXN+j
    dp = new int *[len1 + 1];
    for (int i = 0; i <= len1; i++)
    {
        dp[i] = new int[len2 + 1];

    }

    dp[0][0] = 0;
    for (int i = 1; i <= len2; i++)
        dp[0][i] = -1;
    for (int i = 1; i <= len1; i++)
        dp[i][0] = 0;

    for (int i = 1; i <= len1; i++)
    {
        for (int j = 1; j <= len2; j++)
        {
            if (rule[j - 1] == '*')
            {
                dp[i][j] = -1;
                if (dp[i - 1][j - 1] != -1)
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;

                }
                if (dp[i - 1][j] != -1 && dp[i][j] < dp[i - 1][j] + 1)
                {
                    dp[i][j] = dp[i - 1][j] + 1;
                }
            }
            else if (rule[j - 1] == '?')
            {
                if (dp[i - 1][j - 1] != -1)
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;

                }
                else dp[i][j] = -1;
            }
            else
            {
                if (dp[i - 1][j - 1] != -1 && input[i - 1] == rule[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                else dp[i][j] = -1;
            }
        }
    }

    int m = -1;//
    int *ans = new int[len1];
    int count_ans = 0;//
    char *returnans = new char[len1 + 1];
    int count = 0;
    for (int i = 1; i <= len1; i++)
        if (dp[i][len2] > m)
        {
            m = dp[i][len2];
            count_ans = 0;
            ans[count_ans++] = i - m;
        }
        else if (dp[i][len2] != -1 && dp[i][len2] == m)
        {
            ans[count_ans++] = i - m;
        }

    if (count_ans != 0)
    {
        //int len = ans[0];
        for (int i = 0; i < m; i++)
        {
            printf("%c", input[i + ans[0]]);
            returnans[count++] = input[i + ans[0]];
        }
        for (int j = 1; j < count_ans; j++)
        {
            printf(" ");
            returnans[count++] = ' ';
            //len = ans[j];
            for (int i = 0; i < m; i++)
            {
                printf("%c", input[i + ans[j]]);
                returnans[count++] = input[i + ans[j]];
            }
        }
        printf("\n");
        returnans[count++] = '\0';
    }

    return returnans;
}

//http://discuss.leetcode.com/questions/222/wildcard-matching  No.4 recursion version
bool isFullWildMatchRecursion(const std::string& text, const std::string& pattern) {
  auto textIter = text.begin();
  auto subIter = pattern.begin();
  if (*subIter == '*') {
    while(*subIter == '*') {
      ++subIter;//skip multiple '*'
    }
    if (subIter == pattern.end() ) {
      return true;
    }
    while(textIter != text.end()
        && !isFullWildMatchRecursion(std::string(textIter, text.end() ), std::string(subIter, pattern.end() ) ) ) {
      ++textIter;
    }
    return textIter != text.end();
  }
  else if (*subIter == '\0' || *textIter == '\0') {
    return *subIter  == *textIter;
  }
  else if (*subIter == '?' || *subIter == *textIter) {
    return isFullWildMatchRecursion(std::string(++textIter, text.end() ),
        std::string(++subIter, pattern.end() ) );
  }
  else {
    return false;
  }
}

//http://blog.csdn.net/sunnianzhong/article/details/8932326
//http://blog.csdn.net/zqt520/article/details/7487944
//Link2 method1 (greedy)
int subMatchLen(const char* subText, const char* pattern);
bool retrievePartialWildMatchesRecursively(const std::string& text, const std::string& pattern, std::vector<std::string>& matches) {
  auto textIter = text.begin();
  auto patIter = pattern.begin();
  std::vector<int> matchesForCharInText;// every char in text matches at most chars, -1 for nonmatch
  int maxPos = -1;
  for (; textIter != text.end(); ++textIter) {
    //http://stackoverflow.com/a/2058307
     matchesForCharInText.push_back(subMatchLen(&*textIter, &*patIter) );
     if (maxPos < 0 || matchesForCharInText.back() > matchesForCharInText[maxPos]) {
       maxPos = matchesForCharInText.size() - 1;
     }
  }
  if (maxPos < 0 || matchesForCharInText[maxPos] < 0) {
    return false;
  }
#if 0 // output only the longest matching strings
  int i = 0;
  for (textIter = text.begin(); textIter != text.end(); ) {
    if (matchesForCharInText[i] == matchesForCharInText[maxPos]) {
      std::string tmp(textIter, textIter+matchesForCharInText[i]);
      std::cout << tmp << std::endl;
      matches.push_back(tmp);
      i += matchesForCharInText[maxPos];
      textIter += matchesForCharInText[maxPos];
    }
    else {
      ++i;
      ++textIter;
    }
  }
#endif
  int charNum = matchesForCharInText.size();
  for (int i = 0; i < charNum; ++i) {
    if (matchesForCharInText[i] != -1) {
      std::string tmp(text.begin() + i, text.begin() + i + matchesForCharInText[i]);
      std::cout << tmp << std::endl;
      matches.push_back(tmp);
    }
  }
  return true;
}

int subMatchLen(const char* subText, const char* pattern) {
  if (*pattern == '\0') {
    return 0;//zero pattern string matches zero text length
  }
  int r = -1;
  int maybeLen = -1;
  if (*pattern == '*') {
    r = subMatchLen(subText, pattern+1);// asterisk match zero
    if (*subText) {
      maybeLen = subMatchLen(subText + 1, pattern); // match one
      if (maybeLen >= 0 && ++maybeLen > r) {
        r = maybeLen;
      }
    }
  }
  if (*subText == '\0') {
    return r;
  }
  if (*pattern == '?' || *pattern == *subText) {
    maybeLen = subMatchLen(subText+1, pattern+1);
    if (maybeLen >= 0 && ++maybeLen > r) {
      r = maybeLen;
    }
  }
  return r;
};

Describe(Wildcard_match) {
  It(case_from_below_link1) {
    std::string text = "Oh year.Today is weekend!";
    std::string pat = "*ye*a*e*";
    matched_strings_.clear();

    const char* pText = "abcdefge";
    const char* pPat = "a?c";
    char* matchChars = my_find(const_cast<char*>(pText), const_cast<char*>(pPat) );
    matchChars ? printf("%s\n", matchChars) : NULL;
  }

  It(partial_starting_asterisk_match) {
    std::string text = "abcdabbcd";
    std::string pat = "*a*d"; //or *a*b
    matched_strings_.clear();
    bool matched = asterisk_interrogation_partial_wild_match(text, pat, matched_strings_);
    Assert::That(matched, IsTrue() );
  }
  It(partial_recursion_multiple_match) {
    std::string text = "aac";
    std::string pat = "a*c";
    matched_strings_.clear();
    bool matched = retrievePartialWildMatchesRecursively(text, pat, matched_strings_);
    Assert::That(matched, IsTrue() );
    Assert::That(matched_strings_[0], Equals(std::string("aac") ) );
    Assert::That(matched_strings_[1], Equals(std::string("ac") ) );
  }
  It(inmiddle_matching_zero_star) {
    std::string text = "wil";
    std::string pat = "wi*l";
    matched_strings_.clear();
    bool matched = asterisk_interrogation_partial_wild_match(text, pat, matched_strings_);
    Assert::That(matched, IsTrue() );
    text = "wil";
    pat = "*wil";
    matched = isFullWildMatchRecursion(text, pat);
    Assert::That(matched, IsTrue() );
  }
  It(simple_match_with_asterisk_question_for_debug) {
    std::string text = "will it be good";
    std::string pat = "w?l*t";
    matched_strings_.clear();
    bool matched = asterisk_interrogation_partial_wild_match(text, pat, matched_strings_);
    Assert::That(matched, IsTrue() );
  }
  It(case_unmatch) {
    std::string text = "abcdefge";
    std::string pat = "*a?ce";
    matched_strings_.clear();
    bool matched = asterisk_interrogation_partial_wild_match(text, pat, matched_strings_);
    Assert::That(matched, IsFalse() );
  }
  std::vector<std::string> matched_strings_;
};


//http://www.cnblogs.com/pangxiaodong/archive/2011/09/07/2169588.html 

//http://stackoverflow.com/questions/2093426/wildcard-string-matching
//TODO mini Regex & found all occurence for submatches
//http://swtch.com/~rsc/regexp/regexp1.html (regular expression nfa dfa way)
//http://code.ohloh.net/file?fid=PutoX90WYdxdMfgr8S6Fdc33Muo&cid=--hXj0Z_CaE&s=&fp=305319&mp&projSelected=true#L0 ( git://github.com/openstreetmap/osm2pgsql.git wildcmp.c)  ==> only fit for full match
//http://www.google.com.hk/search?newwindow=1&safe=strict&client=firefox-a&rls=org.mozilla%3Aen-US%3Aofficial&channel=fflb&biw=1920&bih=970&q=+wildcard+submatch&oq=+wildcard+submatch
