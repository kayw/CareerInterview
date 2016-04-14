//http://hi.baidu.com/sheep_finalfreedom/blog/item/819111502e70fb050cf3e3a3.html
//http://hi.baidu.com/xiaoxianxi_acm/blog/item/1e8cad3391d01a47ad4b5f11.html
//
//http://bbs.csdn.net/topics/20335071
#include <iostream>
#include <vector>
struct Square {
  int top;
  int right;
  int bottom;
  int left;
  bool operator==(const Square& rhs) const {
    return top == rhs.top && right == rhs.right
      && bottom == rhs.bottom && left == rhs.left;
  }
};

bool constraint(const int squarex, const int squarey, const std::vector<std::vector<Square>> &travex, const Square& cmp) {
  if (squarex > 0) {//there is a square above 
    if (cmp.top != travex[squarex - 1][squarey].bottom)
      return false;
  }
  if (squarey > 0) {//there is a square lefthand
    if (cmp.left != travex[squarex][squarey - 1].right)
      return false;
  }
  return true;
}

bool dfs(const int squarePos, const int N, const std::vector<Square>& distinctSquares, std::vector<int>& travexStat, std::vector<std::vector<Square>>& travex) {
  if (squarePos == N*N) {
    return true;
  }
  int x = squarePos/N;
  int y = squarePos%N;
  int size = travexStat.size();
  bool result = false;
  for (int i = 0; i < size; ++i) {
    if (travexStat[i] == 0) // prune
      continue;//no same lrtb
    if (constraint(x, y, travex, distinctSquares[i]) ) {
      travex[x][y] = distinctSquares[i];
      --travexStat[i];
      result =  dfs(squarePos+1, N, distinctSquares, travexStat, travex);
      ++travexStat[i];
    }
  }
  return result;
}

int main() {
  int N = 0;
  int game = 0;
  while (std::cin >> N && N != 0) {
    std::vector<std::vector<Square>> travex;
    travex.resize(N, std::vector<Square>() );
    for(int i = 0; i < N; ++i) {//auto range not resizable
      //http://www.cprogramming.com/c++11/c++11-ranged-for-loop.html
      //std::vector<Square>& :
      travex[i].resize(N);
    }
    Square sq;
    std::vector<Square> distinctSquares;
    std::vector<int> travexStat;
    const int len = N*N;
    for(int i = 0; i < len; ++i) {
      std::cin >> sq.top >> sq.right >> sq.bottom >> sq.left;
      bool found = false;
      int j = 0;
      for(auto dsq : distinctSquares) {
        if (sq == dsq ) {
          found = true;
          ++travexStat[j];
          break;
        }
        ++j;
      }
      if (!found) {
        distinctSquares.push_back(sq);
        travexStat.push_back(1);
      } else {
      }
    }
    if (game > 1)
      std::cout << std::endl;
    std::cout << "Game " << ++game << ": ";
    if (dfs(0, N, distinctSquares, travexStat, travex) ) {
      std::cout << "Possible" << std::endl;
    } else {
      std::cout << "Impossible" << std::endl;
    }
  }
}
