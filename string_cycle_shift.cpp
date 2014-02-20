//http://m.newsmth.net/article/CoderInterview/1451?p=1
//1，在一个字符串中找到第一个只出现一次的字符。
//这题后来在网上一搜全是答案，不过都好像只是hash。
//这个当时下意识说了第一遍哈希，第二遍就能找到。
//面试官继续问，如果进行一遍扫描呢，我就卡住了。
//
//
//2，两个大文本文件中相同的行输出出来。求交集。
//
//3.右移一个字符串，比如：abcdefg-> fgabcde


#include <stdio.h>
#include <string>
#include <algorithm>

// copy from libcxx __rotate_gcd
void cstring_shift(char pChar[], int size, int shiftcycle) {
  int exchangePos = size - shiftcycle - 1;
  int exchangeSize = exchangePos+1;
  if (exchangeSize == shiftcycle) {
    for (int i = 0; i < exchangeSize; ++i)
    {
      char tmpchar = pChar[i];
      pChar[i] = pChar[exchangeSize + i];
      pChar[exchangeSize + i ] = tmpchar;
    }
    return;
  }
  int p = exchangeSize;
  int q = shiftcycle;
  do {
    int t = p % q;
    p = q;
    q = t;
  } while(q);
  for (char * pp = pChar + p; pp != pChar; ) {
    int t = *--pp;
    char *pp1 = pp;
    char *pp2 = pp1 + exchangeSize;
    do {
      *pp1 = *pp2;
      pp1 = pp2;
      const int d = pChar + size - pp2;
      if (exchangeSize < d)
      {
        pp2 += exchangeSize;
      }
      else
      {
        pp2 = pChar + (exchangeSize - d);
      }
    } while(pp2 != pp);
    *pp1 = t;
  }
}
void string_shift(std::string& input, int shiftcycle) {
  std::string::iterator midIter = input.begin() + input.size() - shiftcycle;
  std::rotate(input.begin(), midIter, input.end() );
  printf("after shift :%s\n", input.c_str() );
}

int main() {
  //char* p = "abcdefg";
  //std::rotate(0, 2, sizeof(p));
  std::string str = "abcdefg";
  string_shift(str, 2);
  //std::rotate(str.begin(), str.begin() + 2, str.end());
  //http://www.cplusplus.com/reference/algorithm/rotate/
  //Rotates the order of the elements in the range [first,last), in such a way that the element pointed by middle becomes the new first element.
  str = "abcdefg";
  std::rotate(str.begin(), str.begin() + 5, str.end());
  printf("%s\n", str.c_str());

  char pStr[] = "abcdefg";
  cstring_shift(pStr, 7, 2);
  printf("%s\n", pStr);
  char pStr2[] = "abcdefgh";
  cstring_shift(pStr2, 8, 4);
  printf("%s\n", pStr2 );
}
