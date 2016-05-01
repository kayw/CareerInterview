#include "nPatriciaTrie_codeproject.hpp"
#include "patricia_trie_codeproject.hpp"
#include "simple-trie-googlecode.hpp"
#include "simple_trie.hpp"
int main(int /*argc*/, char* /*argv*/ [])
{
  PatriciaTrie<char*, int> ptree;
  ptree.Insert("SOME", 2000);
  ptree.Insert("ABACUS", 2000);
  ptree.Insert("SOMETHING", 2000);
  ptree.Insert("B", 2000);

  nPatriciaTrie<int> nptree;
  nptree.Insert("SOME", 2000);
  nptree.Insert("ABACUS", 2000);
  nptree.Insert("SOMETHING", 2000);
  nptree.Insert("B", 2000);

#ifdef RTV_
  rtv::Trie<char, int> simpleTrie('@');
  simpleTrie.insert("SOME@", 20);
  simpleTrie.insert("ABACUS@", 30);
  simpleTrie.insert("B@", 25);
#else
  MNB::Trie<char, int> mnbTrie('$');
  mnbTrie.insert("SOME$", 23);
  mnbTrie.insert("ABACUS$", 13);
  mnbTrie.insert("B$", 33);
#endif
  return 0;
}

// https://news.ycombinator.com/item?id=12914495
