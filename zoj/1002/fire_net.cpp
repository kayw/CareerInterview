//http://blog.csdn.net/zxy_snow/article/details/5952668
//http://www.mr-naive.com/?p=1586
//http://www.cnblogs.com/phinecos/archive/2008/09/18/1293017.html
#include <iostream>
#include <vector>

//TODO N-queens
bool ablePut(std::vector<std::vector<char> >& city, const int x, const int y) {
  //for(int i = 0; i < N; ++i)
  //  if (city[i][y] == 'X')
  //    return true;
  //for(int j = 0; j < N; ++j)
  //  if (city[x][j] == 'X')
  //    return true;
  //return false;
  for(int i = x - 1; i >= 0; --i) {
    if (city[i][y] == 'O') 
      return false;
    else if (city[i][y] == 'X')
      break;
  }
  for (int j = y - 1; j >= 0; --j) {
    if (city[x][j] == 'O')
      return false;
    else if (city[x][j] == 'X')
      break;
  }
  return true; 
}
void dfs(const int N, std::vector<std::vector<char> >& city, const int coord, const int curhouse, int& maxhouse) {
  if (coord == N*N) {
    if (maxhouse < curhouse)
      maxhouse = curhouse;
    return;
  }
  int x = coord / N;
  int y = coord % N;
  if (city[x][y] == '.' && ablePut(city, x, y) ) {
    city[x][y] = 'O';
    dfs(N, city, coord + 1, curhouse+1, maxhouse);
    city[x][y] = '.';
  }
  dfs(N, city, coord + 1, curhouse, maxhouse);

  //if (max < cur)
  //  max = cur;
  //for (int i = 0; i < N; ++i)
  //  for (int j = 0; j j < N; ++j)
  //    if (!visit(city[i][j]== '.' && ablePut() ) {
  //        city[i][j] = 'O';
  //        dfs(cur+1);
  //        city[i][j] = '.';
  //        }
}

int main() {
  int N = -1;
  std::vector<std::vector<char> > city;
  while(std::cin >> N && N != 0) {
    //http://www.cplusplus.com/forum/general/33546/
    //std::vector<std::vector<char> > city(N, std::vector<char>(N,'0'));
    city.clear();
    city.resize(N);
    for (int i = 0; i < N; ++i)
    {
      city[i].resize(N);
    }
    for (int i = 0; i < N; ++i)
    {
      for (int j = 0; j < N; ++j)
      {
        std::cin >> city[i][j];
      }
    }
    int curhouse = 0;
    int maxhouse = 0;
    dfs(N, city,  0, curhouse, maxhouse);
    std::cout << maxhouse <<std::endl;
  }
  return 0;
}

//http://www.cnblogs.com/lanoo/archive/2008/04/10/1146836.html
