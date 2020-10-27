/**
 *
 * 样例暗示的不错，，不然我可能会漏情况（
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
    static bool isSeparator(int x)
    {return x == ' ' || x == '\n';}

public:

    template <class T>
    void operator()(T &x){x = read<T>();}

    template <class T, class... Ts>
    void operator()(T &x, Ts &... y)
    {(*this)(x), (*this)(y...);}

    void operator()(char *x){scanf("%s", x);}
    void operator()(char &x){x = (char)getchar();}

    int nextInt() {return read<int>();}
    longs nextLongs() {return read<longs>();}
    lll nextInt128() {return read<lll>();}
    char nextChar()
    {int x = getchar(); while (isSeparator(x)) x = getchar(); return x;}
} sc;

using cmd = pair<char, int>;

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = sc.nextInt(), m = 2 * n;
    vector<cmd> opt;
    int cnt = 0; bool valid = true;
    while (m --)
    {
        auto ch = sc.nextChar();
        if (ch == '+') opt.emplace_back('+', 0), ++ cnt;
        else opt.emplace_back('-', sc.nextInt()), -- cnt;
        if (cnt < 0) valid = false;
    }
    if (!valid) puts("NO");
    else
    {
        stack<int> tab, ans;
        auto end = opt.rend();
        for (auto ii = opt.rbegin(); ii != end; ++ ii)
            if (ii->first == '-')
                valid &= (tab.empty() || tab.top() >= ii->second),
                tab.push(ii->second);
            else ans.push(tab.top()), tab.pop();
        if (valid)
        {
            puts("YES");
            while (!ans.empty()) printf("%d ", ans.top()), ans.pop();
            puts("");
        } else puts("NO");
    }
    return 0;
}

