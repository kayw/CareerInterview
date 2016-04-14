#include <iostream>

#include <string.h>

#include <stack>

using namespace std;

 

char sword[11];//

char tword[11];//

char step[100];//

int steplen,sp,tp,n;

//steplen:

//sp:sword

//tp:tword

//n:

 

 

void result(stack<char> &s)

{

    char ch;

    int i;

    if(tp==n)//step

    {

        for(i=0;i<steplen;i++)

        {

            cout<<step[i]<<" ";        

        }

        cout<<endl;

        return;

    }

    

    if(sp<n)//pushsi

    {

        s.push(sword[sp++]);

        step[steplen++]='i';        

        result(s);

        s.pop();

        steplen--;

        sp--;

    }

 

    if(!s.empty())//s

    {              //o

        ch=s.top();

        if(ch==tword[tp])

        {

            s.pop();

            tp++;

            step[steplen++]='o';

            result(s);

            steplen--;

            tp--;

            s.push(ch);

        }

    }

}

 

int main()

{

    stack<char> strtemp;

    while(cin>>sword>>tword)

    {

        cout<<"["<<endl;

        n=strlen(sword);

        if(n==strlen(tword))

        {

            sp=0;tp=0;

            steplen=0;

            result(strtemp);

        }

        cout<<"]"<<endl;

    }

    return 0;

}
