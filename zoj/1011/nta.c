nclude<iostream>
#include<vector>
using namespace std;

struct Pair
{
    int a, b;
};

int N, M, K, L;
vector<Pair> table[ 16 ][ 11 ];
int tree[ 2500 ], signalList[ 2500 ][ 17 ];

bool readSignal();
void readTree();
inline bool isAccepted( int x )  {    return ( N - M ) <= x;    }
void check( int node );
bool checkValid();

int main()
{
    int i = 0;
    while ( readSignal() )
    {
        if ( i )
            putchar( '\n' );

        printf( "NTA%d:\n", ++ i );
        while( scanf( "%d", &L ) !=EOF && L != -1 )
        {
            readTree();
            check( 1 );
            if ( checkValid() )
                puts( "Valid" );
            else
                puts( "Invalid" );
        }
    }

    return 0;
}

bool readSignal()
{
    int i, j;
    scanf( "%d %d %d", &N, &M, &K );

    if ( !N && !M && !K )
        return false;

    getchar();

    for ( i = 0; i < N; i ++ )
        for ( j = 0; j < K; j ++ )
        {
            table[ i ][ j ].clear();

            char line[ 1500 ];
            gets( line );

            Pair p;
            int k = 0;
            while ( true )
            {
                p.a = p.b = 0;
                bool mark = false;
                while ( line[ k ] == ' ' ) k ++;
                for ( ; line[ k ] != '\0' && line[ k ] != ' '; k ++ )
                {
                    p.a = p.a * 10 + line[ k ] - '0';
                    mark = true;
                }

                while ( line[ k ] == ' ' ) k ++;
                for ( ; line[ k ] != '\0' && line[ k ] != ' '; k ++ )
                    p.b = p.b * 10 + line[ k ] - '0';

                if ( mark )
                    table[ i ][ j ].push_back( p );

                if ( line[ k ] == '\0' ) break;
            }
        }

    return true;
}

void readTree()
{
    char ch;
    int i;
    for ( i = 1; i <= ( 2 << L )- 1; i ++ )
    {
        cin >> ch;
        if ( ch == '*' )
            tree[ i ] = -1;
        else
            tree[ i ] = ch - 'a';
    }
}


bool findInChild( int leftChild, int rightChild, int k, int l, int curEle )
{
    int iMax = signalList[ leftChild ][ 0 ];
    int jMax = signalList[ rightChild ][ 0 ];
    for ( int i = 1; i <= iMax; i ++ )
            for ( int j = 1; j <= jMax; j ++ )
            {
                int a = signalList[ leftChild ][ i ];
                int b = signalList[ rightChild ][ j ];

                if ( table[ k ][ curEle ][ l ].a == a && table[ k ][ curEle ][ l ].b == b )
                    return true;
            }

    return false;
}
void print( int node )
{
    int max = signalList[ node ][ 0 ];

    cout << endl << endl << "cur Node is " << node << endl;
    for ( int i = 1; i <= max; i ++ )
        cout << signalList[ node ][ i ] << " ";
    cout << endl;
}
void check( int node )
{
    int leftChild = node * 2;
    int rightChild = leftChild + 1;

    int i, j, k, l, curEle = tree[ node ];
    if ( leftChild >= 2 << L || tree[ leftChild ] == -1 && tree[ rightChild ] == -1 )
    {
        signalList[ node ][ 0 ] = 0;
        for ( i = 0; i < N; i ++ )
        {
            bool find = false;
            for ( j = 0; j < table[ i ][ curEle ].size(); j ++ )
                if ( isAccepted( table[ i ][ curEle ][ j ].a ) && isAccepted( table[ i ][ curEle ][ j ].b ) )
                {
                    find = true;
                    break;
                }
           
            if ( find )
                signalList[ node ][ ++ signalList[ node ][ 0 ] ] = i;
        }
    }
    else
    {
        check( leftChild );
        check( rightChild );
       
        signalList[ node ][ 0 ] = 0;
        for ( k = 0; k < N; k ++ )
        {
            bool get = false;
            for ( l = 0; l < table[ k ][ curEle ].size(); l ++ )
                if ( findInChild( leftChild, rightChild, k, l, curEle ) )
                {
                    get = true;
                    break;
                }
           
            if ( get )
                signalList[ node ][ ++ signalList[ node ][ 0 ] ] = k;
        }
    }
}

bool checkValid()
{
    int max = signalList[ 1 ][ 0 ];
    int i;

    for ( i = 1; i <= max; i ++ )
        if ( signalList[ 1 ][ i ] == 0 )
            return true;
    return false;
}



****************************************************************************************
 * 
   
   4 2 3   //n,m,k 
   1 2    //n*k
   2 1    //
   1 0
   2 2
   0 2 1 0
   3 2
   2 2
   2 3
   1 2
   1 2
   2 1
   3 2
   3    //
   a    //
   b c
   a b c b
   b a b a c a * *
   2
   b
   a b
   b c * *
   -1    //-1case
   0 0 0   //
   nm
   
   
 * dp,d[i][j]ijivalid,
   d[i][j]=1,d[i][j]=0
   
   1)ix,y
   x>=n-m&&y>=n-m,d[i][j]=1,d[i][j]=0;
   2)ix,y
   d[2*i][x]&&d[2*i+1][y],d[i][j]=1,d[i][j]=0
 * vector<vector<vector<int> > > transition_table(n,vector<vector<int> >(k+1));
   ac,vector<vector<vector<int> > > transition_table(n,vector<vector<int> >(k));
   segmention fault ,why? 
   n,m,k0
 * 2008-11-01
****************************************************************************************
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main()
{
// ifstream cin("in.txt");
 int n,m,k,caseNum=0,x,y,i,j,q,L,kt,len;
 string s;
 char tree[2048];
 while(cin>>n>>m>>k)
 {  
  if(n==0&&m==0&&k==0)
   break;
  caseNum++;
  if(caseNum>1)
   cout<<endl;
  cout<<"NTA"<<caseNum<<":"<<endl;
  vector<vector<vector<int> > > transition_table(n,vector<vector<int> >(k+1));
  cin.ignore();   //
  for(i=0;i<n;i++)
   for(j=0;j<k;j++)
   {
    getline(cin,s);
    istringstream in(s);
    while(in>>x>>y)
    {
     transition_table[i][j].push_back(x);
     transition_table[i][j].push_back(y);
    }
   }
  while(cin>>L&&L!=-1)
  {
   kt=(1<<(L+1))-1;
   for(i=1;i<=kt;i++)
    cin>>tree[i];
   if(n==0||m==0||k==0)
   {
    cout<<"Invalid"<<endl;
    continue;
   }
   vector<vector<int> > d(kt+1,vector<int>(n,0));
   for(i=kt;i>=1;i--)
   {
    if(tree[i]=='*')
     continue;
    if(2*i>kt||tree[2*i]=='*')    //
    {
     for(j=0;j<n;j++)
     {
      len=transition_table[j][tree[i]-'a'].size();
      for(q=0;q<len;q+=2)
      {
       x=transition_table[j][tree[i]-'a'][q];
       y=transition_table[j][tree[i]-'a'][q+1];
       if(x>=n-m&&y>=n-m)
       {
        d[i][j]=1;
        break;
       }
      }
     }
    }
    else
    {
     for(j=0;j<n;j++)
     {
      len=transition_table[j][tree[i]-'a'].size();
      for(q=0;q<len;q+=2)
      {
       x=transition_table[j][tree[i]-'a'][q];
       y=transition_table[j][tree[i]-'a'][q+1];
       if(d[2*i][x]&&d[2*i+1][y])
       {
        d[i][j]=1;
        break;
       }
      }
     }
    }    
   }
   if(d[1][0])
    cout<<"Valid"<<endl;
   else
    cout<<"Invalid"<<endl;
  }
 }
 return 0;
}

