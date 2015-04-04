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

#if 0
//73楼|CrTn|2013-05-06 22:41:47|只看此ID
//从屁股往前扫一遍不就可以了么
#include <iostream>
#include <unordered_map>

#include <type_traits>
#include <string>
#include <vector>
using namespace std;

template <typename T>
T firstUnique(const T& beg, const T& end) {
    using keyType = typename remove_const<
        typename remove_reference<decltype(*beg)
            >::type>::type;
    unordered_map<keyType, size_t> stat;
    auto it = beg;
    auto res = beg;
    while(it != end) {
        const auto &ref = *it;
        ++stat[ref];
        if(stat[ref] == 1)
            res = it;
        ++it;
    }

    const auto &ref = *res;
    if(stat[ref] == 1)
        return res;
    else {
        return end;
    }
}

int main()
{
    string str = "afdafgag";
    auto cit = firstUnique(str.crbegin(), str.crend());
    if(cit != str.crend())
        cout << *cit << endl;
    else
        cout << "No Unique" << endl;

    vector<int> ivec{1,2,3,2,3,4,5,1,9,3,3,2,5,6};
    auto iit = firstUnique(ivec.crbegin(), ivec.crend());
    if(iit != ivec.crend())
        cout << *iit << endl;
    else
        cout << "No Unique" << endl;

    return 0;
}
#endif

#if 0
linkedhashtable
27楼|bxhsix|2012-03-30 15:08:11|
第一道应该是hash表+双向链表，简单写了一下，应该可以一遍解决问题

#include <iostream>
#include <map>

using namespace std;

struct pointer
{
    int prev_chr;
    int next_chr;
};

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Usage: " << argv[0] << " <InputString>" << endl;
        return -1;
    }

    char *str = argv[1];
    map<char, pointer> hash;
    int first_uniq_chr = -1;
    int last_chr = -1;

    for (int i=0; str[i]!='\0'; ++i)
    {
        if (first_uniq_chr == -1)
        {
            if (hash.find(str[i]) == hash.end())
            {
                first_uniq_chr = i;
                last_chr = i;
                hash[str[i]] = (pointer){-1, -1};
            }
            continue;
        }

        if (str[i] == str[first_uniq_chr])
        {
            first_uniq_chr = hash[str[first_uniq_chr]].next_chr;
        }
        else
        {
            if (hash.find(str[i]) == hash.end())
            {
                hash[str[i]] = (pointer){last_chr, -1};
                hash[str[last_chr]].next_chr = i;
                last_chr = i;
            }
            else
            {
                if (hash[str[i]].prev_chr != -2)
                {
                    hash[str[hash[str[i]].prev_chr]].next_chr = hash[str[i]].next_chr;
                    hash[str[hash[str[i]].next_chr]].prev_chr = hash[str[i]].prev_chr;
                    if (str[i] == str[last_chr])
                    {
                        last_chr = hash[str[last_chr]].prev_chr;
                    }
                    hash[str[i]].prev_chr = -2;
                }
            }
        }
    }

    cout << first_uniq_chr << ": " << str[first_uniq_chr] << endl;

    return 0;
}
#endif 
