/**
 *
 *
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;
using longd = long double;

#define eprintf(x...) fprintf(stderr, x)
#define var(x) ""#x" = " << x
#define lll __int128
#define minimize(a, b) (a = min(a, b))
#define maximize(a, b) (a = max(a, b))

void print(__int128 x)
{
    if (x < 0) { putchar('-'); x = -x; }
    static char str[40]; int cnt = 0;
    while (x > 9) { str[cnt ++] = (x % 10) ^ 48; x /= 10;}
    str[cnt ++] = x ^ 48;
    while (cnt --) putchar(str[cnt]);
}
template <class T>
void println(T x) {puts(to_string(x).c_str());}
void println(const char *s) {puts(s);}
void println(const char ch)
{putchar(ch), putchar('\n');}
void println(const lll x)
{lll xx = x; print(xx), putchar('\n');}

static class Scanner
{
    template<class T>
    inline T read()
    {
        T x = 0; int f = 0, ch = getchar();
        while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
        return f ? -x : x;
    }

public:

    template <class T>
    void operator()(T &x){x = read<T>();}

    template <class T, class... Ts>
    void operator()(T &x, Ts &... y)
    {(*this)(x), (*this)(y...);}

    void operator()(char *x){scanf("%s", x);}
    void operator()(char &x){x = getchar();}

    int nextInt() {return read<int>();}
    longs nextLongs() {return read<longs>();}
    lll nextInt128() {return read<lll>();}
    char nextChar() {return getchar();}
} scanner;

const int N = 1e6 + 5;

#define h first
#define v second

namespace AdjacencyList
{
    using edge_t = int;

    array<vector<edge_t>, N> adj;

    void init(int n)
    {
        for (int i = 0; i <= n; ++ i)
            adj[i].clear();
    }

    void addEdge(int u, int v, int w = 0)
    {adj[u].push_back(v);}
}

int height[N];

int dfsHeight(int u, int fa)
{
    using namespace AdjacencyList;
    for (auto &ii : adj[u])
    {
        if (ii == fa) continue;
        maximize(height[u], dfsHeight(ii, u) + 1);
    }
    return height[u];
}

const auto cmp = [](const int &a, const int &b)
{
    return height[a] < height[b];
};

int dfs(int u, int fa, int depth)
{
    using namespace AdjacencyList;
    int siz = adj[u].size(), last = 0;
    sort(adj[u].begin(), adj[u].end(), cmp);
    int ans = 0;
    for (auto ii : adj[u])
    {
        if (ii == fa) continue;
        ans += min(last, depth);
        ans += dfs(ii, u, depth + 1) + 1;
        last = height[ii] + 1;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int t = scanner.nextInt();
    for (int $ = 1; $ <= t; ++ $)
    {
        int n = scanner.nextInt();
        memset(height, 0, sizeof(int) * (n + 1));
        AdjacencyList::init(n);
        for (int u = 2; u <= n; ++ u)
        {
            int v = scanner.nextInt();
            AdjacencyList::addEdge(u, v);
            AdjacencyList::addEdge(v, u);
        }
        dfsHeight(1, 0);
        int ans = dfs(1, 0, 0);
        printf("Case #%d: %d\n", $, ans);
    }

    return 0;
}

