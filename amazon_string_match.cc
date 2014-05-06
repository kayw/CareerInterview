//http://www.mitbbs.com/article_t1/JobHunting/32633319_0_1.html
#include <stdio.h>
#include <vector>
#include <string>

bool isRepeatMatch(const std::string& cmpString) {
  std::string repeater;
  int repeaterPtr = 0;
  bool matched = true;
  for (auto strIter = cmpString.begin(); strIter != cmpString.end(); ++strIter)
  {
    const char ch = *strIter; 
    if (repeater.empty() ) {
      repeater.append(1, ch);
    }
    else if (repeater[repeaterPtr] == ch) {
      repeaterPtr = ++repeaterPtr%repeater.size();
    }
    else if (repeaterPtr != 0) {
      matched = false;
      break;
    }
    else {
      repeater.append(1, ch);
    }  
  }
  if (repeater.size() == 1 || repeater.size() == cmpString.size() ) {
    matched = false;
  }
  return matched;
}

int main(int /*argc*/, char */*argv*/[]) {
  std::vector<std::string> tests;
  tests.push_back("abcabad");
  tests.push_back("xyz");
  tests.push_back("abcdabcd");
  tests.push_back("abcdaabcd");
  tests.push_back("aaaaaaa");
  tests.push_back("abaaba");//FAILED  TODO
//need suffix tree ??
//http://www.allisons.org/ll/AlgDS/Tree/Suffix/
  for (auto vecIter = tests.begin(); vecIter != tests.end(); ++vecIter) {
    printf("%s ", vecIter->c_str());
    if (isRepeatMatch(*vecIter) ) {
      printf("TRUE\n");
    }
    else {
      printf("FALSE\n");
    }
  }
  return 0;
}

//see also
//http://leetcode.com/2011/05/longest-substring-without-repeating-characters.html
