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
#define sgn(x) (x < 0 ? -1 : (x > 0))

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

struct date 
{
    int y, m, d;

    int zellerId() const
    {
        auto [y, m, d] = *this;
        if (m < 3) -- y, m += 12;
        return 365 * y + y / 4 - y /100 + y / 400 + (153 * (m - 3) + 2) / 5 + d - 307;
    }

    static date zellerParse(int id)
    {
        int x = id + 1789995, n, i, j, y, m, d;
        n = 4 * x / 146097, x -= (146097 * n + 3) / 4;
        i = (4000 * (x + 1)) / 1461001, x -= 1461 * i / 4 - 31;
        j = 80 * x / 2447, d = x - 2447 * j / 80, x = j / 11;
        m = j + 2 - 12 * x, y = 100 * (n - 49) + i + x;
        return {y, m, d};
    }

    int compareTo(date &rhs)
    {
        if (y != rhs.y) return sgn(y - rhs.y);
        else if (m != rhs.m) return sgn(m - rhs.m);
        else return sgn(d - rhs.d); 
    }

    friend ostream &operator <<(ostream &os, date &d)
    {return os << d.y << '-' << d.m << '-' << d.d;}
};

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
    void operator()(date &x){(*this)(x.y, x.m, x.d);}

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
    int t = scanner.nextInt();
    while (t --)
    {
        date st, ed, tmp;
        scanner(st, ed);
        // cerr << var(st) << ", " << var(ed) << endl;
        longs ans = 0;
        tmp = st;
        // cerr << var(tmp) << endl;
        auto stst = st.zellerId(), eded = ed.zellerId();
        for (int yy = st.y; yy <= ed.y; ++ yy)
        {
            // cerr << var(yy) << endl;
            if (tmp.y / 10 == 202 || tmp.y % 1000 == 202)
            {
                date nxt = {yy, 12, 31};
                if (nxt.compareTo(ed) > 0) nxt = ed;
                ans += nxt.zellerId() - tmp.zellerId() + 1;
            }
            else if (tmp.y % 10 == 2)
            {
                date xx = {yy, 2, 1}, zz = {yy, 3, 1};
                auto xxx = xx.zellerId(), zzz = zz.zellerId() - 1;
                if (xxx < stst) xxx = stst;
                if (zzz > eded) zzz = eded;
                ans += zzz - xxx + 1;
                date bb = {yy, 12, 2};
                if (bb.compareTo(st) >= 0 && bb.compareTo(ed) <= 0) ++ ans;
            }    
            else
            {
                date aa = {yy, 2, 2};
                // cerr << var(aa) << endl;
                if (aa.compareTo(st) >= 0 && aa.compareTo(ed) <= 0) ++ ans;
                date bb = {yy, 12, 2};
                if (bb.compareTo(st) >= 0 && bb.compareTo(ed) <= 0) ++ ans;
            }
            tmp = {yy + 1, 1, 1};
        }
        printf("%lld\n", ans);
    }
    return 0;
}

