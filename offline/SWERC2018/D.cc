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

#define eprintf(x...) fprintf(stderr, x...)
#define var(x) ""#x" = " << x 
#define lll __int128

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

const int N = 1e5 + 5;
vector<int> pos[N];
int ma[N], mi[N];
bitset<N> ok;

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
    memset(mi, 0x3f, sizeof(int) * (n + 1));
    for (int i = 1; i <= n; ++ i)
    {
        scanner(x, y);
        pos[y].push_back(x);
        ma[x] = max(ma[x], y);
        mi[x] = min(mi[x], y);
    }
    longs step = w - 1, cnt = 0;
    for (int i = 0; i < w; ++ i)
        if (ma[i] >= mi[i]) ok[i] = true, ++ cnt,
            step += 2 * (ma[i] - mi[i]);
    longs ans = 0x3f3f3f3f3f3f3f3f, tmp = 0;
    int over = 0, at = pos[0].size(), below = cnt - at;
    for (int i = 0; i < w; ++ i)
    {
        if (ok[i]) tmp += mi[i];
        if (mi[i]) ++ below; else ++ at;
    }
    for (int i = 1; i < h; ++ i)
    {

    }
    println(ans + step);        

    return 0;
}

