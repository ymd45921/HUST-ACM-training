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

const int N = 1e6 + 5;
bitset<N> a;

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n, k, x, ans = 0;
    scanner(n, k);
    while (k --)
    {
        x = scanner.nextInt();
        if (x < 1 || x > n) continue;
        for (int i = x; i <= n; i += x)
            a[i].flip();
        ans = max(ans, int(a.count()));          
    }
    println(ans);

    return 0;
}

