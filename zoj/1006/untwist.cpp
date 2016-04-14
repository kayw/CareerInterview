//http://www.cnblogs.com/jaskist/archive/2009/05/03/1448074.html
//p - i = q*n + c; p = p%q = (q*(n+x) + c+i -x*q)%q = c+i -x*q;c+i > x*q; p = p%q = (-x*q + c+i)%q = c+i;
//p = q*n + r; p%q = (q*n+r)%q = r%q;( 0 < r <= q) ==> p = p%q = (c+i)%q;

#include <iostream>
#include <string>

int transToCode(const char ch);
char transToChar(const int code);
int main() {
  int key = 0;
  std::string ciphertext;
  //http://blog.csdn.net/dangwei_90/article/details/8871852
  //http://www.google.com.hk/search?q=cin+%E7%A9%BA%E6%A0%BC&ie=utf-8&oe=utf-8
  while(std::cin >> key) {
    if (key == 0)
      break;
    std::cin >> ciphertext;
    std::string plaintext;
    int i = 0;
    int len = ciphertext.length();
    plaintext.resize(len+1, '\0');
    for(auto c:ciphertext) {
      int ciphercode = transToCode(c);
      int plaincode = (ciphercode + i) % 28;
      char plainchar = transToChar(plaincode);
      plaintext[key * i % len] = plainchar;
      ++i;
    }
    std::cout << plaintext << std::endl;
  }
}


int transToCode(const char ch) {
  int code = -1;
  if (ch == '_') {
    code = 0;
  }
  else if (ch == '.') {
    code = 27;
  }
  else if ('a' <= ch && ch <= 'z') {
    code = ch - 'a' + 1;
  }
  return code;
}


char transToChar(const int code) {
  char ch = '\0';
  if (code == 0) {
    ch = '_';
  }
  else if (code == 27) {
    ch = '.';
  }
  else if (1 <= code && code <= 26) {
    ch = code - 1 + 'a';
  }
  return ch;
}
