#include <random>
template<int N>
int calcMaxSubSum(int (&a)[N]) {
  int maxsofar = 0;
  int maxcurr = 0;
  for (int i = 0; i < N; ++i) {
    maxcurr += a[i];
    if (maxcurr < 0) {
      maxcurr = 0;
    }
    else if (maxsofar < maxcurr) {
      maxsofar = maxcurr;
    }
  }
  //TODO:http://bbs.csdn.net/topics/350187239#post-360546349
  //1.问这样的子串有多少个。
  //2.如果是首尾相连的，那么最大子串和是多少，有多少个。
  //3.如果是首尾相连的，取两个不相交子串，那么最大子串和是多少。
  return maxsofar;
}

int main(int /*argc*/, char */*argv*/[]) {
  int a[20] = {};
  std::default_random_engine gen((std::random_device())() );
  std::uniform_int_distribution<int> dis(1, 200); 

  for (int i = 0; i < 20; ++i) {
    a[i] = dis(gen);
    printf("%d ", a[i]);
  }
  printf("\n");
  printf("max sub sum:%d\n", calcMaxSubSum(a) );
  return 0;
}
