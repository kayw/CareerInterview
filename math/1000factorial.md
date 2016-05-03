//http://blog.csdn.net/cxh342968816/article/details/6787726
题目：1000！末尾有几个0 


1到1000中2的个数远多于5的个数，2*5可得到一个0。

所以求得1到1000中有多少个5就可以求得1000！的末尾有几个0.

 

分析

5的1次幂5的倍数增加1个0 (5,10,15,20,25,30,.....)
5的2次幂25的倍数增加2个0(必然是5的倍数)(25,50,75,100,125.....)
5的3次幂125的倍数增加3个0(必然是25的倍数)(125,250,375,500.....)
5的4次幂625的倍数增加4个0(必然是125的倍数)(625,1250,1875,2500.....)
...........
所以先求出5的倍数
加上25的倍数(2个0,其中1个已记入5的倍数)
加上125的倍数(3个0,其中1个已记入5的倍数1个已记入25的倍数)
加上625的倍数(4个0,其中....................................)

1000/5=200  (1000里面含有200个5的倍数，但同时也包含了25倍数，125的倍数，625的倍数各一次)

1000/25=40(1000里面含有40个25的倍数，同时也含有125的倍数，625的倍数各一次)

1000/125=8(1000里面含有8个125的倍数，同时也含有625的倍数)

1000/625=1（1000里含有1个625的倍数）

 

所以1000！里面含 有0的个数为200+40+8+1=249个

//http://www.cnblogs.com/heyonggang/p/3386289.html
        1、 每隔5个，会产生一个0，比如 5， 10 ，15，20.。。
        2 、每隔 5×5 个会多产生出一个0，比如 25，50，75，100 
        3 、每隔 5×5×5 会多出一个0，比如125.

