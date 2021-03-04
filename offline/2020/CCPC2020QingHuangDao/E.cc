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

#define a first
#define b second

const int N = 2e5 + 5;

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int t = scanner.nextInt();
    for (int i = 1; i <= t; ++ i)
    {
        int n, p, a, b;
        scanner(n, p);
        auto ratio = p / 100.0;
        // vector<pair<int, int>> stu;
        vector<pair<int, int>> info;
        while (n --)
        {
            scanner(a, b);
            // stu.emplace_back(a, b);
            info.emplace_back(a, n);
            info.emplace_back(b, n);
        }
        info.emplace_back(-100, 0x3f3f3f3f);
        sort(info.rbegin(), info.rend());
        unordered_map<int, int> cnt, out;
        double pass = ratio * info[0].first;
        int st = 0, cur = 0;
        while (info[cur].first >= pass)
        {
            ++ cnt[info[cur].second];            
            ++ cur;
        }
        int ans = cnt.size();
        bool nxt = info[cur].first >= 0;
        while (nxt)
        {
            ++ out[info[st].second];
            if (out[info[st].second] >= 2) break;
            else if (!-- cnt[info[st].second]) 
                cnt.erase(info[st].second);
            pass = ratio * info[++ st].first;
            while (info[cur].first >= pass)
            {
                ++ cnt[info[cur].second];            
                ++ cur;
            }
            maximize(ans, (int)cnt.size());
        }
        printf("Case #%d: %d\n", i, ans);
    }

    return 0;
}

