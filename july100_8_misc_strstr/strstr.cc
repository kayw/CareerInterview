//http://stackoverflow.com/questions/3183582/what-is-the-fastest-substring-search-algorithm (further survey for MString indexof implementation TODO)
//http://www.dmi.unict.it/~faro/smart/download.php  (corpus as test data performance testing TODO)
//http://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string_search_algorithm
//http://www-igm.univ-mlv.fr/~lecroq/string/node14.html (TODO suffixes why beginnig if)
//CLRS 1e 34.5 (TODO good suffix enhancement)

#include "igloo/igloo_alt.h"
using namespace igloo;

#include <string.h>
// assume character set is ASCII
#define ASCII_SIZE 256
//http://www-igm.univ-mlv.fr/~lecroq/string/node19.html
int bm_sunday_indexOf(const std::string& text, const std::string& sub) {
  int aux[ASCII_SIZE] = {0};
  int textLen = text.length();
  int patLen = sub.length();
  for (int i = 0; i < ASCII_SIZE; ++i) {
    aux[i] = patLen + 1;
  }
  for (int i = 0; i < patLen; ++i) {
    aux[static_cast<int>(sub[i]) ] = patLen - i;
  }
  int j = 0;
  while(j <= (textLen - patLen) ) {
    if (memcmp(text.c_str() + j, sub.c_str(), patLen) == 0) {
      return j;
    }
    j += aux[static_cast<int>(text[j+patLen])];
  }
  return -1;
}

#define HASH_BASE 127
int rehash(char a, char b, int hash, int reduce) {
  return (hash - a*reduce)*HASH_BASE + b;
}
//http://www-igm.univ-mlv.fr/~lecroq/string/node5.html#SECTION0050
int rabin_karp_indexOf(const std::string& haystacks, const std::string& needles) {
  int needleHash = 0;
  int hayHash = 0;
  int needleLen = needles.length();
  int hayLen = haystacks.length();
  int reduceHash = 1;
  for (int i = 0; i < needleLen; ++i) {
    needleHash = needleHash*HASH_BASE + needles[i];
    hayHash = hayHash*HASH_BASE + haystacks[i];
    reduceHash *= HASH_BASE;
  }
  int j = 0;
  while(j <= hayLen-needleLen) {
    if (needleHash == hayHash && memcmp(needles.c_str(), haystacks.c_str() + j, needleLen) ) {
      return j;
    }
    hayHash = rehash(haystacks[j], haystacks[j+needleLen], hayHash, reduceHash);
    ++j;
  }
  return -1;
}

Describe(Strstr) {
  It(isSub) {
    std::string needle = "if wrong";
    std::string text = "where shoud if wrong i go ";
    int index = bm_sunday_indexOf(text, needle);
    AssertThat(index, 13);
    int ondex = rabin_karp_indexOf(text, needle);
    AssertThat(index, ondex);
  }
  It(unMatch) {
    std::string haystack = "nothing is right";
    std::string needle = "great bad";
    int index = bm_sunday_indexOf(haystack, needle);
    AssertThat(index, -1);
  }
};
