/**
 *
 * TODO: 二进制分组是什么……搞不懂（
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

const int N = 300, lim = 30;
int a[N], b[N];
#define array(s, n) for (int i = s; i <= n; ++ i) cout << ' ' << a[i]; cout << endl

int diff(int n)
{
    auto t = n * (n - 1) / 2, xx = 0, x = 0;
    while (t --) cin >> x, xx = max(x, xx);
    return xx;
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n, x; cin >> n;
    if (n < lim)
    {
        for (int i = 1; i <= n; ++ i)
        {
            cout << "1 " << i << endl;
            cin >> a[i];
        }
        cout << "3";
        array(1, n);
    }
    else
    {
        cout << "2 " << n;
        array(1, n);
        const auto d = diff(n);
        int l = 2, r = n;
        while (r > l)
        {
            auto mid = l + r >> 1;
            cout << "2 " << mid;
            array(1, mid);
            if (diff(mid) == d) r = mid;
            else l = mid + 1;
        }
        const auto pos = l;
        unordered_multiset<int> st[20];
        unordered_set<int> all;
        for (int i = 1, lg = 0; i <= n; i <<= 1, ++ lg)
        {
            vector<int> list;
            for (int j = 1; j <= n; ++ j)
                if (!(i & j) || j == pos) continue;
                else list.push_back(j);
            if (list.empty()) continue;
            auto siz = list.size();
            cout << "2 " << siz + 1 << ' ' << pos;
            for (auto ii : list) cout << ' ' << ii;
            cout << endl;
            auto t = siz * (siz + 1) / 2;
            while (t --) cin >> x, st[lg].insert(x);
            if (siz > 1)
            {
                cout << "2 " << siz;
                for (auto ii : list) cout << ' ' << ii;
                cout << endl;
                auto t = siz * (siz - 1) / 2;
                while (t --) cin >> x, st[lg].erase(st[lg].find(x));
            }   
            for (auto ii : st[lg]) all.insert(ii);
        }
        int lg = 0, npos = -1;
        while ((1 << lg) <= n) ++ lg;
        for (auto ii : all)
        {
            int t = 0;
            for (int i = 0; i < lg; ++ i)
                if (st[lg].count(ii)) t |= (1 << i);
            b[t] = ii;
            if (ii == d) npos = t;
        }
        cout << "1 " << pos << endl;
        cin >> a[pos];
        cout << "1 " << npos << endl;
        cin >> a[npos];
        int sgn = a[pos] < a[npos] ? 1 : -1;
        cout << "3 ";
        for (int i = 1; i <= n; ++ i)
        {
            if (i != pos) a[i] = a[pos] + sgn * b[i];
            cout << ' ' << a[i];
        }
        cout << endl;
        return 0;
    }
    return 0;
}

