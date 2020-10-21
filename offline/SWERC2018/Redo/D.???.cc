/**
 *
 * 中 庸 之 道
 * 虽然感觉挺离谱的，但是似乎确实这么回事
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

template <class T>
void println(const T x)
{puts(to_string(x).c_str());}
void println(const char *s){puts(s);}
void println(const char ch)
{putchar(ch), putchar('\n');}

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
const int inf = 0x3f3f3f3f;
int high[N], low[N];
vector<int> use, xx;

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int w, h, n, x, y;
    scanner(w, h, n);
    memset(high, 0, sizeof(int) * w);
    memset(low, 0x3f, sizeof(int) * w);
    while (n --)
    {
        scanner(x, y);
        maximize(high[x], y);
        minimize(low[x], y);
    }
    for (int i = 0; i < w; ++ i)
        if (high[i] >= low[i]) use.push_back(i);
    const auto count = [&](int y)
    {
        longs ret = 0;
        for (auto x : use)
        {
            if (low[x] > y) ret += 2 * (low[x] - y);
            if (high[x] < y) ret += 2 * (y - high[x]);
        }
        return ret;
    };
    longs solid = w - 1, tmp = 0;
    for (int i : use)
        solid += 2 * (high[i] - low[i]),
        xx.push_back(high[i]),
        xx.push_back(low[i]);
    sort(xx.begin(), xx.end());
    // for (auto ii : xx) eprintf("%d ", ii);
    // eprintf("\n");
    auto mi = xx.size() / 2;  
    longs ans = min(count(xx[mi - 1]), count(xx[mi]));
    ans += solid;    
    println(ans);            

    return 0;
}

