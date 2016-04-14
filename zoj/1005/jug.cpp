//http://www.cppblog.com/Darren/archive/2008/11/14/66959.html
#include<stdio.h>

int main()
{
    int ca,cb,n;
    while(scanf("%d%d%d",&ca,&cb,&n)!=EOF)
    {
         if(ca==n)
        {
            printf("fill A\n");
            printf("success\n");
            continue;
        }
        if(cb==n)
        {
            printf("fill B\n");
            printf("success\n");
            continue;
        }
        int t=0;
        while(t!=n)
        {
            printf("fill A\n");
            printf("pour A B\n");
            t+=ca;
            if(t>cb)
            {
                t-=cb;
                printf("empty B\n");
                printf("pour A B\n");
            }
        }
        printf("success\n");
    }
    return 0;
}
