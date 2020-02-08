/**
 *
 */
#include <iostream>
#include <utility>

#define x first
#define y second
#define min(a,b) (a<b?a:b)

using namespace std;
typedef long long longs;
typedef long double longd;
typedef pair<int,int> point;

int n;
point pli[520];

inline bool isParallel(int i, int j, int k)
{
    point v1,v2;
    v1.x = pli[i].x - pli[k].x;
    v1.y = pli[i].y - pli[k].y;
    v2.x = pli[j].x - pli[k].x;
    v2.y = pli[j].y - pli[k].y;
    return v1.x*v2.y==v1.y*v2.x;
}

inline int innerProduct(int i, int j, int k)
{
    point v1,v2;
    v1.x = pli[i].x - pli[k].x;
    v1.y = pli[i].y - pli[k].y;
    v2.x = pli[j].x - pli[k].x;
    v2.y = pli[j].y - pli[k].y;
    return v1.x*v2.x+v1.y*v2.y;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n1,n2;

    while(cin>>n)
    {
        for(int i=0;i<n;++i)
            cin>>pli[i].x>>pli[i].y;

        int cnt = 0;
        n1 = n-1; n2 = n-2;
        for(int i=0;i<n2;++i)
            for(int j=i+1;j<n1;++j)
                for(int k=j+1;k<n;++k)
                {
                    if(isParallel(i,j,k))continue;
                    int inp = innerProduct(i,j,k);
                    if(inp>=0)inp = min(inp,innerProduct(i,k,j));
                    if(inp>=0)inp = min(inp,innerProduct(j,k,i));
#ifdef mydebug
                    cout<<"point number: "<<i<<", "<<j<<", "<<k<<'\n'
                        <<"Their lowest inner product: "<<inp<<endl;
#endif
                    if(inp<0)++cnt;
                }

        cout<<cnt<<endl;
    }

    return 0;
}