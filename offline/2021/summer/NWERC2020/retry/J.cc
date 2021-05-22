/**
 *
 * 首先，如何理解题目？说句实话我没有看懂（
 * - 给定一个图；现在要从这个图中先选出一条 non-self-intersecting path
 * - 这个图剩下来的点被划分为等量的 A 和 B 两组
 * - 现在要求这张图的任何边，都不使得其端点分别来自 A 和 B 的元素
 * 条件，是不是有点宽松？
 * 
 * 因为没有能够理解题意，所以这里是题解做法：
 * + 首先所有节点都属于 A，然后开始 DFS；此时 |A| = n, |B| = 0；
 * + 如果 |A| != |B|（实际上只有 |A| < |B|），重复进行下面操作：
 *   + 如果新访问了一个节点，则将它加入 path 末尾；|A|↓
 *   + 如果处理完了一个节点，回溯时从 path 末尾移出并加入 B；|B|↑
 * + 这样首先可以保证 path 是一个简单路（不知道题目里那个是个啥意思）
 * + 其次，这样也保证了必不可能有 A - B 的边存在（子树级别的划分）
 * 于是，就可以使用标记的数组得到 A 和 B，并在 dfs 的过程中维护得到 path
 * 
 * 看了一些别人的代码；另一种理性的做法是先统计子树大小，然后再 DFS
 * 如果可以完全加入子树，就加入；否则，则递归处理；同样维护 path
 * 始终递归维护重儿子，保证递归处理之后总是可以使得两个组平衡
 * 实际上和题解是一样的，只是题解没有显式地维护这个子树和
 *
 * ……莫非，这是个语文题？
 */
#include <bits/stdc++.h>

using namespace std;
using llong = long long;

#define bigint int
bigint read() {
    bigint ret = 0;
    int f = 0, ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-') f = !f;
    for (; isdigit(ch); ch = getchar())
        ret = ret * 10 + ch - 48;
    return f ? -ret : ret;
}

void write(bigint x) {
    static char str[100];
    if (x < 0) putchar('-'), x = -x;
    int cnt = 0;
    while (x > 9) {
        str[cnt ++] = char(x % 10 + 48);
        x /= 10;
    }
    str[cnt ++] = char(x + 48);
    while (cnt --) putchar(str[cnt]);
}
#undef bigint

const int N = 2e5 + 10;
int belong[N], A, B;
vector<int> path;
bitset<N> vis;

struct fws {

    using edge = pair<int, int>;
    vector<int> head;
    vector<edge> e;

    void renew(size_t siz) {
        head.resize(siz), e.clear();
        fill(head.begin(), head.end(), -1);
    }

    void add_edge(int u, int v) {
        edge tmp(v, head[u]);
        head[u] = (int) e.size();
        e.emplace_back(move(tmp));
    }
} g;

void dfs(int u) {
    if (!vis[u] && A != B) {
        belong[u] = 0;
        path.push_back(u);
        -- A;
    }
    vis[u] = true;
    for (int i = g.head[u]; i >= 0;
        i = g.e[i].second) {
        int v = g.e[i].first;
        if (vis[v]) continue;
        dfs(v);
        if (A != B) {
            path.pop_back();
            belong[v] = -1;
            ++ B;
        }
    }
}

signed main() {
    int n = read(), m = read();
    g.renew(n + 1), g.e.reserve(m * 2 + 5);
    for (int i = m; i --;) {
        int u = read(), v = read();
        g.add_edge(u, v);
        g.add_edge(v, u);
    }
    fill(belong, belong + 1 + n, 1);
    A = n, B = 0, dfs(1);
    vector<int> aa, bb;
    for (int i = 1; i <= n; ++ i)
        if (belong[i] < 0) bb.push_back(i);
        else if (belong[i]) aa.push_back(i);
    cout << path.size() << ' ' << A << endl;
    for (auto i : path) cout << i << ' ';
    cout << endl;
    for (auto i : aa) cout << i << ' ';
    cout << endl;
    for (auto i : bb) cout << i << ' ';
    cout << endl;
    return 0;
}