/**
 *
 * 关于二分图博弈问题：
 * - 有两个人，轮流决策，决策会修改当前的状态
 * - 状态仅分为两类，每次决策会造成状态的转移
 * - 不可以转移到已经访问过的状态
 * - 无法进行转移的一方失败
 * 这种问题的两类状态分别对应了二分图的两侧集合
 *
 * 假设起始条件出现在 X 集中，那么：
 * + 先手只能从 X 移动到 Y 集中；后手相反
 * + 每一次决策对应了 X - Y 集中的一条边
 * + 终局停留在 X，说明先手负；后手相反
 * 对于这个二分图，首先找到一个最大匹配：
 * + 如果起点 S 不属于这个最大匹配
 *   - 那么先手的第一步转移一定会转移到最大匹配中
 *   - 接下来根据最大匹配的增广路来走，最终一定停留在 X 集中，先手必败
 *   - 上述两点必然成立，否则就存在增广路和匹配，与最大匹配冲突
 * + 如果起点 S 属于这个最大匹配
 *   - 将 S 点删除后重新求剩下的图的最大匹配
 *   - 如果最大匹配数不变，则说明某最大匹配不包含 S，和上述情况相同
 *   - 否则，先手沿着最大匹配的增广路前进，则先手必胜
 * 综上所述，得到了二分图博弈的通用解法。
 *
 * 爷的最大流板子被卡常了，吐了（
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;
using longd = long double;
using lll = __int128;

#define minimize(a, b...) ((a) = min({(a), b}))
#define maximize(a, b...) ((a) = max({(a), b}))
#define sgn(x) ((x) < 0 ? -1 : (x) > 0)
#define puti(n) puts(to_string(n).c_str())

#if 1
#define eprintf(x...) fprintf(stderr, x)
#define eputs(str) fputs(str, stderr), fputc('\n', stderr)
#define var(x) ""#x" = " << x
#define watch(...) trace(#__VA_ARGS__, __VA_ARGS__)
#else
#define eprintf(...)
#define eputs(...)
#define watch(...)
#endif

template <class printable>
void trace(const char *name, printable &&value)
{cerr << name << " = " << value << endl;}
template <class printable, class ...args>
void trace(const char *names, printable &&value, args &&...list)
{
    const char *separate = strchr(names + 1, ',');
    cerr.write(names, separate - names) << " = " << value << ',';
    trace(separate + 1, list...);
}

template <class T>
void print(T x)
{
    if (x < 0) { putchar('-'); x = -x; }
    static char str[40]; int cnt = 0;
    while (x > 9) { str[cnt ++] = (x % 10) + 48; x /= 10;}
    str[cnt ++] = x + 48;
    while (cnt --) putchar(str[cnt]);
}
void print(const char *s) {fputs(s, stdout);}
void print(char *s) {fputs(s, stdout);}
void print(string &s) {print(s.c_str());}
void print(char ch) {putchar(ch);}
template <class T, class ...Ts>
void print(T x, Ts ...xs) {print(x), print(xs...);}
void println() {puts("");}
template <class T>
void println(T x)
{print(x), putchar('\n');}

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

    static inline bool isBlank(int x)
    {return x == ' ' || x == '\n';}
public:

    template <class T>
    void operator()(T &x){x = read<T>();}

    template <class T, class... Ts>
    void operator()(T &x, Ts &... y)
    {(*this)(x), (*this)(y...);}
    template <class T, class... Ts>
    void operator()(T &&x, Ts &&... y)
    {(*this)(x), (*this)(y...);}

    void operator()(char *x){scanf("%s", x);}
    void operator()(char &x){do x = (char)getchar(); while (isBlank(x));}

    int nextInt() {return read<int>();}
    longs nextLongs() {return read<longs>();}
    lll nextInt128() {return read<lll>();}
    char nextChar() {char x; (*this)(x); return x;}
} scanner;

const int N = 1e5 + 5, M = N * 12;

struct edge
{
    int v, w, next;
    edge() = default;
    edge(int v, int w, int next) : v(v), w(w), next(next) {}
};

namespace FWS
{
    int head[N];
    int tot;
    edge ee[M * 2];

    void init(int n = N - 1)
    {
        memset(head, -1, sizeof(int) * (n + 1));
        tot = 0;
    }

    int addEdge(int u, int v, int w)
    {
        ee[tot] = edge(v, w, head[u]);
        return head[u] = tot ++;
    }
}

bitset<N> ban, side;
const int state[] = {1, 10, 100, 1000, 10000, 100000};
vector<int> adjoin[N];

void clear()
{
    ban.reset();
}

void initialize()
{
    for (int i = 0; i < 1e5; ++ i)
    {
        int x = i, cnt = 0;
        while (x) cnt += x % 10, x /= 10;
        side[i] = cnt % 2;
        for (int j = 0; j < 5; ++ j)
        {
            int digit = i / state[j] % 10;
            if (digit != 0) adjoin[i].push_back(i - state[j]);
            else adjoin[i].push_back(i + 9 * state[j]);
            if (digit != 9) adjoin[i].push_back(i + state[j]);
            else adjoin[i].push_back(i - 9 * state[j]);
        }
    }
}

namespace MaxFlow
{
    using number = int;
    constexpr auto inf = 0x3f3f3f3f;    // 严格匹配 number，不要自动转型！
    int S, T, total = 0;    // 重新建图之后的节点数
    int sign;               // 标记节点流量的正边：如果该边被使用，则残量减少

    int addEdge(int u, int v, number w)
    {
        int pos = FWS::addEdge(u, v, w);
        FWS::addEdge(v, u, 0);
        return pos;
    }

    namespace Dinic
    {
        number dis[N];
        int cur[N]; // 当前弧优化

        // 先创建分层图
#if ORIGINAL_BFS
        bool bfs()
        {
            using namespace FWS;
            static queue<int> q;
            memset(dis, 0x3f, sizeof(number) * (total + 1));
            q.push(S); dis[S] = 0;
            while (!q.empty())
            {
                int u = q.front(); q.pop();
                for (int cc = head[u]; cc != -1; cc = ee[cc].next)
                {
                    edge& e = ee[cc];
                    int v = e.v; auto w = e.w;
                    cur[u] = head[u];
                    if (!w || dis[v] <= dis[u] + 1) continue;
                    dis[v] = dis[u] + 1; q.push(v);
                }
            }
            return dis[T] != inf;
        }
#else
        bool bfs()
        {
            using namespace FWS;
            static queue<int> q;            //// 避免开全局变量：110ms => 140ms (total +600ms)
            memset(dis, 0x3f, sizeof(number) * (total + 1));
            memcpy(cur, head, sizeof(int) * (total + 1));
            q.push(S); dis[S] = 0;
            while (!q.empty())
            {
                int u = q.front(); q.pop();
                for (int cc = head[u]; cc != -1; cc = ee[cc].next)
                {
                    edge& e = ee[cc];
                    int v = e.v; auto w = e.w;
                    if (!w || dis[v] <= dis[u] + 1) continue;
                    dis[v] = dis[u] + 1; q.push(v);
                    if (v == T) return true;            //// 修改了分层图的返回条件：170ms => 110ms
                }
            }
            return false;
        }
#endif

        number dfs(int u, number inflow)
        {
            using namespace FWS;
            if (u == T) return inflow;
            number outflow = 0, rest = inflow;
            for (int &cc = cur[u]; cc != -1; cc = ee[cc].next)  // 当前弧优化
            {
                edge &e = ee[cc], &r = ee[uint(cc) ^ 1u];
                int v = e.v; auto w = e.w;
                if (!w || dis[v] != dis[u] + 1) continue;
                int t = dfs(v, min(w, rest));
                if (!t) dis[v] = inf;       //// 改动：test 1 - 200ms => 170ms
                outflow += t; e.w -= t; r.w += t; rest -= t;
                if (!rest) break;
            }
            if (!outflow) dis[u] = 0;
            return outflow;
        }

        void buildGraph(int tot, int target)
        {
            S = tot, T = S + 1, total = tot + 1;
            FWS::init(total);
            for (int i = 0, sig; i < tot; ++ i)
            {
                if (ban[i]) continue;
                if (side[i]) sig = addEdge(i, T, 1);
                else
                {
                    sig = addEdge(S, i, 1);
                    for (const auto &ii : adjoin[i])
                        if (ii < tot && !ban[ii])
                            addEdge(i, ii, 1);
                }
                if (i == target) sign = sig;
            }
        }

        number go()
        {
            number maxFlow = 0;
            while (bfs()) maxFlow += dfs(S, inf);
            return maxFlow;
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int t = scanner.nextInt(), n, m, s;
    initialize();
    while (t --)
    {
        clear();
        scanner(m, n, s);
        for (int i = 1; i <= n; ++ i)
            ban[scanner.nextInt()] = true;
        MaxFlow::Dinic::buildGraph(state[m], s);
        int mf = MaxFlow::Dinic::go();
        if (FWS::ee[MaxFlow::sign].w)
            println("Bob");
        else
        {
            ban[s] = true;
            MaxFlow::Dinic::buildGraph(state[m], s);
            int tmp = MaxFlow::Dinic::go();
            println(mf == tmp ? "Bob" : "Alice");
        }
    }
    return 0;
}