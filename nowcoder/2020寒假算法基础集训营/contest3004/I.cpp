/**
 * 
 */
#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;
typedef long long longs;
typedef long double longd;

longs cnt[3][3];
longs alcnt,n;

void naiveHanoi(int n,int a,int b,int c)
{
    if(n==1) ++cnt[a][c];
    else
    {
        naiveHanoi(n-1,a,c,b);
        ++cnt[a][c];
        naiveHanoi(n-1,b,a,c);
    }
    ++alcnt;
}

void countHanoi(int n,int a,int b,int c)
{
    alcnt = (1LL<<n)-1;
    longs ia=0,ib=1,ic=0,id=0;
    longs dx = 0;
    
    for(int i=1;i<n;++i)
    {
        if(i&1)
        {
            ia += dx+1;
            id += dx;
        }
        else
        {
            ib += dx+1;
            ic += dx;
        }
        dx = (dx<<1)^(i&1);
    }

    cnt[a][b] = cnt[b][c] = ia;
    cnt[a][c] = ib;
    cnt[b][a] = cnt[c][b] = ic;
    cnt[c][a] = id;
    // assert(((ia+ic)<<1)+ib+id == alcnt);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        memset(cnt,0,sizeof(cnt));
        alcnt = 0;
        countHanoi(n,0,1,2);

        cout<<"A->B:"<<cnt[0][1]<<endl
            <<"A->C:"<<cnt[0][2]<<endl
            <<"B->A:"<<cnt[1][0]<<endl
            <<"B->C:"<<cnt[1][2]<<endl
            <<"C->A:"<<cnt[2][0]<<endl
            <<"C->B:"<<cnt[2][1]<<endl
            <<"SUM:"<<alcnt<<endl;
    }

    return 0;
}