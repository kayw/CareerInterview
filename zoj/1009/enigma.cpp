//http://www.cnblogs.com/hoodlum1980/archive/2008/10/20/1315471.html

#include <iostream>
#include <string>
#include <assert.h>

//clockwise rotation , status backwards
void rotateRotor(const int m, int (&rotorStatus)[3] ) {
  //r0 = r0%m;
  //r1 = (r1/m)%m;
  //r2 = (r2/m/m)%m;
  if (--rotorStatus[0] == 0 ) {
    rotorStatus[0] = m;
    if (--rotorStatus[1] == 0) {
      rotorStatus[1] = m;
      if (--rotorStatus[2] == 0) {
        rotorStatus[2] = m;
      }
    }
  }
}
int main() {
  std::string cipher;
  int keynum = 0;
  char rotor[3][26] = {{0}};
  int casenum = 0;
  while(std::cin >> keynum && keynum) {
    std::string rotorStatus;
    if (casenum++) std::cout << std::endl;
    for (int i = 0; i < 3; ++i) {
      std::cin >> rotorStatus;
      assert(rotorStatus.size() == keynum);
      for(int j = 0; j < keynum; ++j) {
        char ch = rotorStatus[j];
        rotor[i][ch - 'A'] =  j - (ch - 'A');
      }
    }
    int cipherNum = 0;
    std::cin >> cipherNum;
    std::string plaintext;
    for (int i = 0; i < cipherNum; ++i) {
      std::cin >> cipher;
      int rotorConvert[3] = {keynum};
      for (auto ch : cipher) {
        int diff = ch - 'A';
        for(int j = 2; j >= 0; --j) {
          diff += rotor[j][(diff + rotorConvert[j])%keynum];
          diff = (diff + keynum)%keynum;
        }
        plaintext += 'a' + diff;
        rotateRotor(keynum, rotorConvert);
      }
    }
    std::cout << "Enigma " << casenum << ":" << std::endl;
    std::cout << plaintext << std::endl;
  }
}
