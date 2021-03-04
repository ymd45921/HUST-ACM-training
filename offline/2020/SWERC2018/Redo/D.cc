/**
 *
 * WA: 初始化傻傻分不清楚，n 不是什么东西啊哥（
 * WA: 溢出了？？？确实 1e12 直接炸了
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
set<int> key[N];
bitset<N> ex;

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
        ex[x] = true;
    }
    longs solid = w - 1, tmp = 0;
    for (int i = 0; i < w; ++ i)
        if (ex[i]) 
            key[high[i]].insert(i), 
            key[low[i]].insert(i),
            solid += 2 * (high[i] - low[i]);
    int over = 0, at = 0, below = 0;        
    for (int i = 0; i < w; ++ i)
        if (ex[i])
            if (low[i])
            {
                tmp += 2 * low[i];
                ++ over;
            } else if (high[i] == 0) ++ below;
            else ++ at;
    assert(ex.count() == over + at + below);        
    longs ans = solid + tmp;
    for (int i = 1; i < h; ++ i)
    {
        tmp = tmp - 2 * over + 2 * below;
        for (auto ii : key[i])
        {
            if (high[ii] == low[ii]) 
                ++ below, -- over;
            else if (i == high[ii])
                ++ below, -- at;
            else ++ at, -- over;    
        }
        minimize(ans, solid + tmp);
    }
    println(ans);            

    return 0;
}

