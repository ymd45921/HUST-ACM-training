/**
 *
 * 好家伙，秦皇岛你会双指针这你就不会了？
 * 甚至还不需要单调队列维护 RMQ ==
 * 拒绝偷鸡摸狗（）
 * 
 * 草我好不会写双指针啊
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
#define let const auto

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
    void operator()(char &x){x = (char)getchar();}

    int nextInt() {return read<int>();}
    longs nextLongs() {return read<longs>();}
    lll nextInt128() {return read<lll>();}
    char nextChar() {return (char)getchar();}
} scanner;

const int N = 1e5 + 5;

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int a[7]; vector<int> b;
    for (int i = 1; i <= 6; ++ i)
        a[i] = scanner.nextInt();
    int n = scanner.nextInt();
    while (n --) b.push_back(scanner.nextInt());
    n = b.size();
    unordered_map<int, int> cnt;
    vector<pair<int, int> > arr;
    for (int i = 1; i <= 6; ++ i)
        for (int j = 0; j < n; ++ j)
            arr.emplace_back(b[j] - a[i], j);
    sort(arr.begin(), arr.end());
    let nn = arr.size();
    let inc = [&](int id){id = arr[id].second; ++ cnt[id];};
    let dec = [&](int id){id = arr[id].second; if (!-- cnt[id]) cnt.erase(id);};
    let calc = [&](int r, int l){return arr[r].first - arr[l].first;};
    let kind = [&](){return cnt.size();};
    int ans = 0x3f3f3f3f, cur = 0;
//    for (auto ii : arr) cerr << "(" << ii.first << ", " << ii.second << ") ";
    for (int lim = 0; lim < nn; ++ lim)
    {
        while (cur < nn && kind() < n) inc(cur ++);
        if (kind() != n) break;
        minimize(ans, calc(cur - 1, lim)); dec(lim);
    }
    println(ans);
    return 0;
}

