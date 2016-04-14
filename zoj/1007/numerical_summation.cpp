//https://github.com/icyrhyme/zoj
//http://www.cnblogs.com/jaskist/archive/2009/05/03/1448211.html
//http://hi.baidu.com/harrison_d/item/64019f162f8b3a0dd1d66d57
//http://code.google.com/p/neilsun/source/browse/zoj/1007/1007.cpp?r=16
// Inf(x^alpha) = x^(alpha+1)/(alpha+1) +C alpha != -1
#include <iostream>

int main() {
   double step = 0.001;
   for (double i = 0.0; i <= 2.0; i += step) {
     double sum = 0;
     const int n = 10000;
     for(int k = 1; k < n; ++k) {
       sum += 1.0/((k+1)*(k+i)*k);
     }
     sum = sum * (1-i) +  (1 - i)/(2*n*n) + 1.0;
     printf("%5.3f %16.12f\n",i, sum);
   }
   return 0;
}
