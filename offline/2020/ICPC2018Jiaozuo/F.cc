/**
 * 
 * F 傻逼模拟，真的恶心
 * 可以跑过样例，但是就是过不了测试
 * 辛辛苦苦建图转换不如直接在图上跑，模拟的姿势学到了🐎？
 * 了解了 cin 的读行法，虽然很傻逼就是了（
 * 
 * TODO: 未完成，也许不会再 debug 了
 * WA: 大量的测试样例输出 -1，但实际上是有解的
 */
#include <iostream>
#include <algorithm>
#include <cmath>
#include <bitset>
#include <vector>
#include <queue>
#include <cassert>
#include <cstring>

using namespace std;

using longs = long long;

#define $peek "cin.peek = " << '\'' << (char)cin.peek() << "\' (" << cin.peek() << ")"

const int N = 1e6 + 5, M = 6060;
char line[M];

namespace FWS
{
    struct edge
    {
        int u, v, next;
        edge() = default;
        edge(int u, int v, int next) : u(u), v(v), next(next) {}
    };

    int head[N], tot, deg[N];
    edge ee[N * 24];

    void init(int n)
    {
        memset(head, -1, sizeof(int) * (n + 1));
        memset(deg, 0, sizeof(int) * (n + 1));
        tot = 0;
    }

    void addEdge(int u, int v)
    {
        ee[tot] = edge(u, v, head[u]);
        head[u] = tot ++; ++ deg[u];
    }

    template <class fun>
    void forEach(int u, const fun recurrence)
    {
        for (auto c = head[u];
            c != -1;
            c = ee[c].next)
            if (recurrence(ee[c])) continue;
            else break;
    }
}

int dis[N];
int bfs(int s, int t, int lim)
{
    queue<int> q;
    memset(dis, 0, sizeof(int) * (lim + 1));
    q.push(s), dis[s] = 1;
    using namespace FWS;
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        if (u == t) return dis[u];
        for (auto c = head[u];
             c != -1;
             c = ee[c].next)
        {
            const auto &[_, v, $] = ee[c];
            if (dis[v]) continue;
            dis[v] = dis[u] + 1;
            q.push(v);
        }
    }
    return -1;
}

//#define LOG_INPUT_DEBUG
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int T, r, c, n, m, lim, s, t;
    const auto parseCore = [&](int row, int col)
    {
        if (row < 1 || col < 1 || row > n || col > m) return 0;
        int rows = (row + 1) / 4, cols = (col + 1) / 6;
        assert((col + 1) % 6 == 0);
        assert((row + 1) % 4 == (cols % 2) ? 0 : 2);
        return rows * c + cols - c;
    };
    const auto parseSlash = [&](int row, int col)
    {
        bool a = (row / 2) % 2, b = ((col + 4) / 6) % 2;
        if (!(a ^ b)) return make_pair(
                parseCore(row - 1, col - 3),
                parseCore(row + 1, col + 3));
        else return make_pair(
                parseCore(row + 1, col - 3),
                parseCore(row - 1, col + 3));
    };
    const auto evenLine = [&](int row, int lim)
    {
        for (int i = 2; i <= lim; i += 6)
        {
            if (line[i] == ' ')
            {
                auto [a, b] = parseSlash(row, i);
                if (!a || !b || a > lim || b > lim) continue;
                FWS::addEdge(a, b), FWS::addEdge(b, a);
            }
        }
    };
    const auto oddLine = [&](int row, int lim)
    {
        int sign = (row + 1) / 2 % 2;
        for (int i = 5, j = 1; i <= lim; i += 6, j = !j)
            if (j != sign)
                if (line[i] == 'S') s = parseCore(row, i);
                else if (line[i] == 'T') t = parseCore(row, i);
                else continue;
            else if (line[i] == '-') continue;
            else
            {
                int a = parseCore(row - 2, i),
                    b = parseCore(row + 2, i);
                if (!a || !b || a > lim || b > lim) continue;
                FWS::addEdge(a, b), FWS::addEdge(b, a);
            }
    };
    const auto check = [&](int id)
    {
        int rows = id / c + 1, cols = id % c;
        if (!cols) -- rows, cols = c;
        int y = 6 * cols - 1, x = 4 * rows - 1 + (cols % 2 ? 0 : 2);
        int route = 6;
        
    };
    cin >> T;
    while (T --)
    {
        cin >> r >> c;
        n = 4 * r + 3, m = 6 * c + 3;
        lim = r * c;
        FWS::init(lim + 1), s = t = 0;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        for (int i = 1; i <= n; ++ i)
        {
            cin.getline(&line[1], m + 1, '\n');
#ifdef LOG_INPUT_DEBUG
            cerr << (line + 1) << " | " << $peek << endl;
#endif
            const auto siz = strlen(line + 1);
            assert(siz <= m);
            if (i % 2) oddLine(i, siz); else evenLine(i, siz);
        }
#ifdef LOG_INPUT_DEBUG
        cerr << "S = " << s << ", T = " << t << endl;
        assert(FWS::tot % 2 == 0);
        for (int i = 0; i < FWS::tot; i += 2)
            cerr << "Edge:: " << FWS::ee[i].u
                 << "<----->" << FWS::ee[i].v << endl;
        cerr << "Total " << FWS::tot / 2 << " edges" << endl;
#endif
        assert(s > 0 && s <= lim && t > 0 && t <= lim && s != t);
        auto ret = bfs(s, t, lim);
        cout << ret << endl;
    }
    return 0;
}