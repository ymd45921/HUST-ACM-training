/**
 *
 * 比赛的时候的代码有点不明所以==
 *
 * 走一大圈只有可能是只有一种方向的带子
 * 旁边有静止带子的位置一定可作答案
 * 就这么简单，怎么还能 FST 的
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

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int t; cin >> t;
    while (t --)
    {
        int n; string s;
        cin >> n >> s;
        int cntC = 0, cntA = 0, cntO = 0;
        for (auto i : s)
            switch (i)
            {
                case '<': ++ cntA; break;
                case '-': ++ cntO; break;
                case '>': ++ cntC; break;
                default: break;
            }
        if (cntA && cntC)
        {
            int ans = int(s[n - 1] == '-' || s[0] == '-');
            for (int i = 1; i < n; ++ i)
                if (s[i - 1] == '-' || s[i] == '-') ++ ans;
            cout << ans << endl;
        } else cout << n << endl;
    }

    return 0;
}

