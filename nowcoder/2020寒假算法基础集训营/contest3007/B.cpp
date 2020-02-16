/**
 * 
 * T了
 * 
 * 应该使用记忆化搜索——反正你也不知道该怎么记忆化
 * 
 * 我日怎么还能M的
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#include <stack>

using namespace std;
typedef long long longs;
typedef long double longd;

// struct Mystack
// {
//     int mem[1000010]{0};

//     int top(){ return mem[mem[0]];}
//     void pop(){ --mem[0]; }
// };

int n,v[1000010];
bool vis[1000010],in[1000010];
stack<int> t;
int ans = 0,mem[1000010];
int cur,c,cnt;

int mem_dfs(int x)
{
    if(mem[x]) return mem[x];
    else return mem[x] = 1+mem_dfs(v[x]);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        for(int i=1;i<=n;++i) cin>>v[i];
        memset(vis,0,sizeof(bool)*(n+1));
        memset(in,0,sizeof(bool)*(n+1));
        memset(mem,0,sizeof(int)*(n+1));

        for(int i=1;i<=n;++i)
        {
            if(!vis[i])
            {
                cur = i;
                while(!vis[cur])        // 找点
                {
                    t.push(cur);
                    vis[cur] = in[cur] = true;
                    cur = v[cur];
                }
                if(in[cur])             // 找到环
                {
                    c=v[cur],cnt=1;
                    while(c!=cur)       // 求环的大小
                    {
                        c = v[c];
                        ++cnt;
                    }
                    do                  // 存储环的大小
                    {
                        c = v[c];
                        mem[c] = cnt;
                    } while (c!=cur);
                }
                while(t.size())
                {
                    in[t.top()] = false;
                    t.pop();
                }
            }
        }
        for(int i=1;i<=n;++i)
            ans = max(ans,mem_dfs(i));
        cout<<ans<<endl; 
    }

    return 0;
}