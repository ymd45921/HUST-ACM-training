/**
 * 
 * 这就是真正的思维题吗？这其实也是贪心
 * 
 * 为啥我就是纸上模拟没有模拟出来啊
 */
#include <iostream>
#include <algorithm>

using namespace std;

inline int best(int n, int x, int y)
{
    return min(max(x-n+y+1,1),n);
}

inline int worst(int n, int x, int y)
{
    return min(max(x+y-1,1),n);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t,n,x,y;
    cin>>t;
    while(t--)
    {
        cin>>n>>x>>y;
        cout<<best(n,x,y)<<' '<<worst(n,x,y)<<endl;
    }

    return 0;
}

/*
inline int best(int n, int x, int y)
{
    int gx = x-1;
    int gy = y-1;
    int lx = n-x;
    int ly = n-y;
    int back = 0;
    if(lx>0&&ly>0)++back,--lx,--ly;
    if(gy<=lx) return 1;
    else 
    {
        if(gy-lx==1)++gy;
        return gy-lx+1;
    }
}

inline int worst(int n, int x, int y)
{
    int gx = x-1;
    int gy = y-1;
    int lx = n-x;
    int ly = n-y;
    
}

*/