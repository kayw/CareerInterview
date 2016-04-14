//http://neilsun.googlecode.com/svn/zoj/1003/1003.cpp
//https://code.google.com/p/zoj-acm/source/browse/trunk/1003.cpp
//http://www.cnblogs.com/godhand/archive/2010/04/27/1722357.html
//http://www.cppblog.com/Darren/archive/2008/11/14/66913.html
#include <iostream>

void dfs(const int bigger, const int smaller, const int divisor, bool& bigwin, bool& smallright);

int main(int /*argc*/, char */*argv*/[])
{
  int a = 0;
  int b = 0;
  bool bigwin = false;
  bool smallright = false;
  while(std::cin >> a >> b) {
    bigwin = false;
    smallright = false;
    dfs(std::max(a,b), std::min(a,b), 2, bigwin, smallright);
    if (!bigwin && smallright)
    {
      std::cout << std::min(a,b) << std::endl;
    }
    else
    {
      std::cout << std::max(a,b) << std::endl;
    }
  }
  return 0;
}

void dfs(const int bigger, const int smaller, const int divisor, bool& bigwin, bool& smallright) {
  if (divisor > 100)
    return;
  if (bigger == 1 && smaller == 1)
    bigwin = true;
  if (smaller == 1)
    smallright = true;
  if (!(bigger % divisor) )
    dfs(bigger/divisor, smaller, divisor+1, bigwin, smallright);
  if (!(smaller % divisor) )
    dfs(bigger, smaller/divisor, divisor+1, bigwin, smallright);
  dfs(bigger, smaller, divisor+1, bigwin,smallright);
}



//https://code.google.com/p/xcodexp/source/browse/trunk/zoj/1003.cpp?spec=svn2&r=2
//#include <stdio.h>
//#define NUM 100
//
//int balloon[NUM];
//int hiwin,lowrong;
//
//void lower_routine(int loscore, int hiscore);
//void check(int score);
//
//int main()
//{
//  int i,hiscore,loscore,tmp;
//  
//  while(scanf("%d%d",&hiscore,&loscore) != EOF)
//  {
//    if(hiscore < loscore)
//    {
//      tmp = hiscore;
//      hiscore = loscore;
//      loscore = tmp;
//    }
//    
//    hiwin = 0;
//    lowrong = 1;
//    lower_routine(loscore,hiscore);
//    if(lowrong)
//    {
//      printf("%d\n",hiscore);
//      continue;
//    }
//    printf("%d\n",hiwin?hiscore:loscore);
//  }
//  
//  return 0;
//}
//
//void lower_routine(int loscore, int hiscore)
//{
//  int i;
//  for(i=1; i<NUM; i++)
//  {
//    if(loscore == 1)
//    {
//      lowrong = 0;
//      check(hiscore);
//      return;
//    }
//    
//    if(!(loscore%(i+1)) && !balloon[i])
//    {
//      balloon[i] = 1;
//      lower_routine(loscore/(i+1),hiscore);
//      balloon[i] = 0;
//    }
//  } 
//}
//
//void check(int score)
//{
//  int i;
//  for(i=1; i<NUM; i++)
//  {
//    if(score == 1)
//    {
//      hiwin = 1;
//      return;
//    }
//      
//    if(!(score%(i+1)) && !balloon[i])
//    {
//      balloon[i] = 1;
//      check(score/(i+1));
//      balloon[i] = 0;
//    }
//  }
//}
