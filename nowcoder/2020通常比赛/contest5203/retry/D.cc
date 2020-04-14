/**
 *
 * 暴力会超时，所以要用到一种奇特但是我不知道名字的方法
 *
 * 游戏开始前需要维护这样的信息：
 * hit[N][0~2]：0-自己被鲨；1-儿子被鲨；2-孙子被鲨
 * dad[v] = u：一个节点的爸爸是谁；树根没有爸爸，加边就可完成
 * 虽然FWS默认记录了v-u，但是并不能快速找到v；所以数组还得开
 * 
 * 那么什么时候节点u会被鲨呢？分情况：
 * - 自己/儿孙被鲨： Σ hit[v][…]
 * - 爸爸/爷爷被鲨： hit[dad[v]][0] + hit[dad[dad[v]]][0]
 * - 亲兄弟姐妹被鲨：hit[dad[v]][1] - hit[v][0]
 * 非常的稳，访问是O(1)的，维护也不麻烦。
 */
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
using longs = long long;
using longd = long double;
using ulongs = unsigned long long;

const int inf = 0x3f3f3f3f;
const longs INF = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-8;

const int N = 8e5;
int n, q, hit[N][3];

struct edge
{
    int u, v;
    int next;

    edge() = default;
    edge(int s, int t, int next)
            : u(s) , v(t) , next(next) {}
};

namespace FWS
{
    int tot = 0;
    edge ee[N << 1];
    int head[N];
    int dad[N];

    void init()
    {
        tot = 0;
        memset(head,-1,sizeof head);
        memset(dad,0,sizeof dad);
    }

    void addedge(int u, int v)
    {
        ee[tot] = edge(u, v, head[u]);     // 偶数正向边
        head[u] = tot ++;
        ee[tot] = edge(v, u, head[v]);
        head[v] = tot ++;
        dad[v] = u;
    }
}

int attack(int u)
{
    using FWS::dad;
    ++ hit[u][0], ++ hit[dad[u]][1],
    ++ hit[dad[dad[u]]][2];
    int ans = hit[u][1] + hit[u][2] + (
              dad[u] ? hit[dad[u]][0] + hit[dad[u]][1] 
                     : hit[u][0]) + (
              dad[dad[u]] ? hit[dad[dad[u]]][0] : 0
    );
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    FWS::init();

    int u, v;
    cin >> n >> q;
    for (int i = 1; i < n; ++ i)
    {
        cin >> u >> v;
        FWS::addedge(u, v);
    }
    while (q --)
    {
        cin >> u;
        cout << attack(u) << endl;
    }
    
    return 0;
}