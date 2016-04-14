# include<stdio.h>
# include<memory.h>
# define MAXN 501
int dp[MAXN][MAXN],dp2[MAXN][MAXN];
int car[2][100];    //car[0][i]car[1][i] i
int n;    //
int w1,w2,w3,s1,s2,s3,c1,c2,c3,d1,d2,d3,d4;

int min(int a,int b){
    return a<b ? a :b;
}

int compute(int a,int b,int c){    //
    int minnum;
    minnum = min(min(a/c1,b/c2),c/c3);
    return (minnum * d4 + (a- minnum*c1)*d1 + (b- minnum*c2)*d2 + (c- minnum*c3)*d3);
}
#define CEILING_2_POWER(x,a)     ( ((x) + ((a) - 1) ) & ( ~((a) - 1) ) )
int main(){
  printf("xxx:%d\n",CEILING_2_POWER(44, 16));
    int i,j,k,cas=0,x,y;
        int curr_a,curr_b; // 
        while(scanf("%d",&n)==1 && n){
            scanf("%d%d%d%d%d%d%d%d%d%d%d%d%d",
                &w1, &s1, &d1,
                &w2, &s2 ,&d2,
                &w3, &s3, &d3,
                &c1, &c2, &c3, &d4);
            for(i=0;i<n;i++) scanf("%d%d",&car[0][i],&car[1][i]);
            for(i=0; i<MAXN; i++)
                for(j=0; j<MAXN; j++)
                    dp[i][j] = dp2[i][j] = -1;
            curr_a = curr_b = 0;
            dp2[0][0] = 0;
            k = 0;
            while(k < n){
                for(i=0; i<= curr_a; i++)
                    for(j=0; j<=curr_b; j++){
                        dp[i][j] = dp2[i][j];
                        dp2[i][j] = -1;
                    }
                 int r_a =min(car[0][k] / w1, car[1][k] / s1);    //
                 for(i=0; i<=r_a; i++)
                 {
                     int r_aw = car[0][k] - i * w1;    //
                     int r_as = car[1][k] - i * s1;    //
                     int r_b = min(r_aw / w2, r_as / s2);    //
                     for(j=0; j<=r_b; j++)
                     {
                         int r_bw = r_aw - j * w2;    //
                         int r_bs = r_as - j * s2;    //
                         int r_c = min(r_bw / w3,r_bs/s3);    //
                         for(x=0; x<=curr_a; x++)
                             for(y=0; y<=curr_b; y++)
                                 if(dp[x][y] >=0 && dp[x][y] + r_c >dp2[x+i][y+j])
                                     dp2[x+i][y+j] = dp[x][y] +r_c;
                     }
                 }
                 curr_a += min(car[0][k] / w1, car[1][k] / s1);
                 curr_b += min(car[0][k] / w2, car[1][k] / s2);
                 k++;
            }
            int ans =0;
            for(i=0; i<=curr_a; i++)
                for(j=0; j<=curr_b; j++)
                if(dp2[i][j] != -1){
                    int temp = compute(i,j,dp2[i][j]);
                    if(temp > ans) ans = temp;
                }
            if(cas>0) puts("");
            printf("Case %d: %d\n", ++cas, ans);
        }
        return 0;
}
