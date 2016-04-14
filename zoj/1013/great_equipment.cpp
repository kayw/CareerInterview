//http://www.cnblogs.com/acm-bingzi/p/3224236.html
//http://www.cnblogs.com/TenosDoIt/archive/2013/04/15/3021989.html
#include <iostream>
#include <vector>

struct TradeLimit {
  int weightLimit;
  int sizeLimit;
};

int main(int /*argc*/, char* /*argv*/[]) {
  //std::vector<TradeLimit> caravs;
  int caravs[2][101];
  int caravNum = 0;
  int w[3] = {0};
  int s[3] = {0};
  int d[3] = {0};
  int combination[4] = {0};
  int dp[2][501][501];
  int caseNum = 0;
  while (std::cin >> caravNum && caravNum) {
    for (int i = 0; i < 3; ++i) {
      std::cin >> w[i] >> s[i] >> d[i];
    }
    for (int i = 0; i < 4; ++i) {
      std::cin >> combination[i];
    }
    //caravs.clear();!!!!!
    for (int i = 0; i < caravNum; ++i) {
      std::cin >> caravs[0][i] >> caravs[1][i];
      //TradeLimit tl;
      //std::cin >> tl.weightLimit >> tl.sizeLimit;
      //caravs.push_back(tl);
    }
    //memset(dp, -1, sizeof(dp));
    //is this below more efficient???
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 501; ++j) {
        for (int k = 0; k < 501; ++k) {
          dp[i][j][k] = -1;
        }
      }
    }
    const int prev = 0; //i & 1;
    const int curr = 1; //(i+1)&1;
    int prev_maxHelm = 0;
    int prev_maxArmor = 0;
    dp[1][0][0] = 0;
    for (int i = 0; i < caravNum; ++i) {

      for (int j = 0; j <= prev_maxHelm; ++j) {
        for (int k = 0; k <= prev_maxArmor; ++k) {
          dp[prev][j][k] = dp[curr][j][k];
          dp[curr][j][k] = -1;
        }
      }

      //int maxHelm = std::min(caravs[i].weightLimit/w[0], caravs[i].sizeLimit/s[0]);
      int maxHelm = std::min(caravs[0][i]/w[0], caravs[1][i]/s[0]);
      for (int j = 0; j <= maxHelm; ++j) {
        //int maxArmor = std::min((caravs[i].weightLimit - j*w[0])/w[1], (caravs[i].sizeLimit - j*s[0])/s[1]);
        int maxArmor = std::min((caravs[0][i] - j*w[0])/w[1], (caravs[1][i] - j*s[0])/s[1]);
        for (int k = 0; k <= maxArmor; ++k) {
          int maxBoot = std::min((caravs[0][i] - j*w[0] - k*w[1])/w[2], (caravs[1][i] - j*s[0] - k*s[1])/s[2]);
          for (int h = 0; h <= prev_maxHelm; ++h) {
            for (int e = 0; e <= prev_maxArmor; ++e) {
              if (dp[prev][h][e] != -1) {// e not k!!!!
                dp[curr][h+j][e+k] = std::max(dp[curr][h+j][e+k], dp[prev][h][e] + maxBoot);
              }
            }
          }
        }
      }

      //prev_maxHelm += std::min(caravs[i].weightLimit/w[0], caravs[i].sizeLimit/s[0]);
      prev_maxHelm += std::min(caravs[0][i]/w[0], caravs[1][i]/s[0]);
      //prev_maxArmor += std::min(caravs[i].weightLimit/w[1], caravs[i].sizeLimit/s[1]);
      prev_maxArmor += std::min(caravs[0][i]/w[1], caravs[1][i]/s[1]);
    }
    //calcualtion sum based on the following link
    //https://github.com/icyrhyme/zoj/blob/master/1013.cpp
    //http://blog.csdn.net/leohxj/article/details/6001183
    int defend = 0;
    int combinDef = std::max(0, combination[3] - combination[0]*d[0] - combination[1]*d[1] - combination[2]*d[2]);
    for (int i = 0; i <= prev_maxHelm; ++i) {
      for (int j = 0; j <= prev_maxArmor; ++j) {
        if (dp[curr][i][j] != -1) {
          int sets = std::min(std::min(i/combination[0], j/combination[1]),dp[curr][i][j]/combination[2]);
          int curDefend = sets*combinDef + i*d[0] + j*d[1] + dp[curr][i][j]*d[2];
          if (defend < curDefend)
            defend = curDefend;
        }
      }
    }
    if (caseNum > 0)
      std::cout << std::endl;
    std::cout << "Case " << ++caseNum << ": " << defend << std::endl;
  }
  return 0;
}
