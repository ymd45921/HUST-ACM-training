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
    cin >> n;
    cout << fixed << setprecision(2);
    const auto apply = [&](double ll, double rr)
    {
        for (int i = 1; i <= n; ++ i)
            a[i].ll = a[i].value + ll,
            a[i].rr = a[i].value + rr;
    };
    for (int i = 1; i <= n; ++ i)
    {
        cin >> a[i].name >> x;
        sum += a[i].value = x;
        a[i].ll = a[i].rr = x;
    }
    bool solved = true;
    if (sum < 100)
    {
        auto d = 100 - sum;
        double ll, rr = 0.49;
        auto res = d - rr * (n - 1);
        if (res >= -0.5 && res < 0.5)
            ll = res;
        else 
        {
            ll = -0.5, rr = (d - ll) / (n - 1);
            if (rr >= 0.5 || rr < -0.5) solved = false;
            else rr = max(min(d - ll, 0.49), rr);
        }
        apply(ll, rr);
    }
    else
    {
        auto d = sum - 100;
        double ll = -0.50, rr;
        auto res = -(d + ll * (n - 1));
        if (res >= -0.5 && res < 0.5)
            rr = res;
        else
        {
            rr = 0.49, ll = (d + rr) / (n - 1);
            if (ll >= 0.5 || ll < -0.5) solved = false;
            else ll = min(max(-0.5, d + rr), ll);
        }
        apply(ll, rr);    
    }
    if (solved)
    {
        for (int i = 1; i <= n; ++ i)
            cout << a[i] << endl;
    } else cout << ng << endl;

    return 0;
}

