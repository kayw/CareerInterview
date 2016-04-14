//https://github.com/fookwood/zoj-solutions-fish_ball/blob/master/Vol.01%281001-1099%29/%231004%20Anagrams%20by%20Stack/p1004.cpp
//http://www.fookwood.com/archives/172

//http://lukaipeng1992.blog.sohu.com/169776003.html

//http://blog.csdn.net/immortality/article/details/717991
//http://hi.baidu.com/acmers/blog/item/2128a6fb8aa6add9b58f315a.html
#include <iostream> 
#include <string>
#include <stack>

bool dfs(const std::string& src, const int srcIdx, const std::string& dst, const int dstIdx, std::stack<char>& putstack, std::deque<char>& opstring);

int main(int /*argc*/, char */*argv*/[])
{
  std::string src_word;
  std::string dest_word;
  while(std::cin >> src_word >> dest_word) {
    //std::string op;
    std::deque<char> opQueue;
    std::stack<char> putstack;
    const std::string::size_type srclen = src_word.length();
    std::cout << '[' << std::endl;
    if(srclen == dest_word.length() ) {
      //dfs(src_word,0, dest_word, 0, putstack, opQueue);
      if (dfs(src_word,0, dest_word, 0, putstack, opQueue) ) {
        //for(auto opq: opQueue)
        //  std::cout << opq << ' ';
      }
    }
    std::cout << ']' << std::endl;
  }
  return 0;
}

bool dfs(const std::string& src, const int srcIdx, const std::string& dst, const int dstIdx, std::stack<char>& putstack, std::deque<char>& opstring){
  int len = src.length();
  if (/*srcIdx == len&&*/ dstIdx == len) {
    //need consume(output) here otherwise pop out after dfs
    for(auto opi:opstring)
      std::cout << opi << ' ';
    std::cout << std::endl;
    //opstring.push_back('\n');
    return true;
  }

  bool result = false;
  if (/*dstIdx < len && dstIdx < srcIdx && */!putstack.empty() ) {
    char ch = putstack.top();
    if (ch == dst[dstIdx]) {
      putstack.pop();
      opstring.push_back('o');
      //opstring.push_back(' ');
      result = dfs(src, srcIdx, dst, dstIdx + 1, putstack, opstring);
      putstack.push(ch);
      opstring.pop_back();
      //opstring.pop_back();
    }
  }
  if (srcIdx < len) {
    putstack.push(src[srcIdx]);
    opstring.push_back('i');
    //opstring.push_back(' ');
    result = dfs(src, srcIdx+1, dst, dstIdx, putstack, opstring);
    putstack.pop();
    opstring.pop_back();
    //opstring.pop_back();
  }
  
  //if (/*dstIdx < len && dstIdx < srcIdx && */!putstack.empty() ) {
  //  char ch = putstack.top();
  //  if (ch == dst[dstIdx]) {
  //    putstack.pop();
  //    opstring.push_back('o');
  //    //opstring.push_back(' ');
  //    result = dfs(src, srcIdx, dst, dstIdx + 1, putstack, opstring);
  //    putstack.push(ch);
  //    opstring.pop_back();
  //    //opstring.pop_back();
  //  }
  //}
  return result;
}

/*
bool dfs(std::deque<char> src, std::deque<char> dst, std::deque<char> putstack, std::string& opstring) {
  while(!src.empty() ) {
    char c = src.front();
    opstring += "i ";
    src.pop_front();
    putstack.push_back(c);
    if (c == dst.front() ) {
      opstring += "o ";
      dst.pop_front();
      putstack.pop_front();
      if (!dfs(src, dst,putstack, opstring) ) {
        return false;
      }
      dst.push_front(c);
      putstack.push_front(c);
      opstring += "i ";
    }
  }
  bool result = true;
  if (putstack.size() == dst.size() ) {
    int size = putstack.size();
    for (int i = 0; i < size; ++i)
    {
      if(putstack[i] == dst[i]) {
        opstring += "o ";
      }
      else {
        result = false;
        break;
      }
    }
    putstack.clear();
    opstring += '\n';
  }
  else {
    result = false;
  }
  return result;
}
*/
//http://www.cnblogs.com/jaskist/archive/2009/05/03/1448059.html
