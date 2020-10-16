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

const int N = 10010;
const char ng[] = "IMPOSSIBLE";

struct spot
{
    string name;
    int value;
    double ll, rr;
} a[N];

ostream &operator<<(ostream &os, spot &sp)
{return os << sp.name << ' ' << sp.ll << ' ' << sp.rr;}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n, x, sum = 0;
    int high = 0, low = 100;
    int cnt100 = 0, cnt0 = 0;
    cin >> n;
    cout << fixed << setprecision(2);
    const auto apply = [&](double ll, double rr, double rr0)
    {
        for (int i = 1; i <= n; ++ i)
            a[i].ll = max(0.0, a[i].value + ll),
            a[i].rr = min(100.0, a[i].value + 
                (a[i].value ? rr : rr0));
    };
    for (int i = 1; i <= n; ++ i)
    {
        cin >> a[i].name >> x;
        sum += a[i].value = x;
        a[i].ll = x, a[i].rr = x;
        high = max(high, x);
        low = min(low, x);
        if (x == 100) ++ cnt100;
        if (x == 0) ++ cnt0;
    }
    bool solved = true;
    if (n == 1)
        solved = (sum == 100);
    else
    {
        auto d = 100 - sum;
        double ll, rr, rr0, xx;
        xx = d - 0.49 * (n - max(1, cnt100));   // 这样的处理是不对的
        if (xx >= 0.5) solved = false;
        else ll = max(-0.5, xx);
        xx = d + 0.50 * (n - cnt0 - 1);
        if (xx < -0.5) solved = false;
        else rr = min(0.49, xx);
        xx = d + 0.50 * (n - cnt0);
        if (xx < -0.5) solved = false;
        else rr0 = min(0.49, xx);
        apply(ll, rr, rr0);
    }
    if (solved)
    {
        for (int i = 1; i <= n; ++ i)
            cout << a[i] << endl;
    } else cout << ng << endl;

    return 0;
}

