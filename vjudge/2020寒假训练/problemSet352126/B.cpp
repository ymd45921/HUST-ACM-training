/**
 * 我日我怎么觉得这个题目是模拟啊==
 * 看样子有点像要用线段树的样子（）
 *
 * 模拟了就TLE了……果然不是模拟啊==
 */
#include <iostream>
#include <cstring>

using namespace std;

int n,a,b,N;
int ans[100010]{0};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        if(!n)break;
        memset(ans,0,sizeof(ans));
        N=n;
        while(n--)
        {
            cin>>a>>b;
            for(int i=a;i<=b;++i)
                ++ans[i];
        }
        cout<<ans[1];
        for(int i=2;i<=N;++i)
            cout<<' '<<ans[i];
        cout<<endl;
    }

    return 0;
}