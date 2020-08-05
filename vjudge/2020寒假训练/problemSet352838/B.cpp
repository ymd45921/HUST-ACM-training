/**
 *
 * 还想建图做的…………也就想想
 * 可以用带权并查集（路径压缩）
 *
 * 话说如果要输出最少的不合理数……岂不是很麻烦==
 *
 * WA: HDU的尿性，有多组测试数据靠EOF结束
 */
#include <iostream>
#include <cstring>

using namespace std;

const int BUF_SIZE = 2000005;

int n,m;
int a,b,s;
int ans = 0;
int father[BUF_SIZE]{0};
int path[BUF_SIZE]{0};

namespace UFS
{
    inline int findFather(int thispoint)
    {
        if(!father[thispoint]) return thispoint;
        else
        {
            int nowfather = father[thispoint];
            father[thispoint] = findFather(nowfather);
            path[thispoint] += path[nowfather];
            return father[thispoint];
        }
    }

    inline bool findUnion(int x,int y,int length)
    {
        int fx = findFather(x);
        int fy = findFather(y);
        if(fx!=fy)
        {
            father[fx] = fy;
            path[fx] = path[y]+length-path[x];
            return true;
        }
        else
        {
            int tmplen = path[x]-path[y];
            if(tmplen==length)return true;
            else return false;
        }
    }
}

inline void initialize()
{
    memset(path,0,sizeof(path));
    memset(father,0,sizeof(father));
    ans = 0;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n>>m)
    {
        initialize();
        while(m--)
        {
            cin>>a>>b>>s;
            if(!UFS::findUnion(a-1,b,s))++ans;
        }
        cout<<ans<<endl;
    }

    return 0;
}