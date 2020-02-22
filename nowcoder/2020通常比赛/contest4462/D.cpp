/**
 * 
 * 因为任意两点的最短路必然在最小生成树上
 * 所以最小生成树是必然要找的——不对。感觉不对劲。
 */
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;
typedef long long longs;
typedef long double longd;

const char mod[] = "The shortest path has length ";

struct coord
{
    int x,y;
    int operator-(const coord& c);
};

int t,N,M,n;
coord st,pp[20];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>t) while(t--)
    {
        cin>>N>>M>>st.x>>st.y;
        cin>>n;
        for(int i=1;i<=n;++i)
            cin>>pp[i].x>>pp[i].y;
        
    }

    return 0;
}

int coord::operator-(const coord& c)
{
    return abs(x-c.x)+abs(y-c.y);
}