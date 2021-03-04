/**
 *
 * 说句实话，这个题真的不难，，
 * 
 * 唯一需要想到的就是给的是主视图和侧视图
 * 对于高（n）维度无关，每层可以单独分开考虑
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
#define println(num) puts(to_string(num).c_str())

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
    {x = read<T>(), (*this)(y...);}

    int nextInt() {return read<int>();}
    longs nextLongs() {return read<longs>();}  
    lll nextInt128() {return read<lll>();}    
} scanner;

int n, m, h;
const int N = 110;
char nm[N][N], nh[N][N];
struct point
{
    int x, y, z;
    point(int x, int y, int z): x(x), y(y), z(z) {}
    void __println()
    {printf("%d %d %d\n", x, y, z);}
};
deque<int> mm, hh;
vector<point> ans1, ans2;

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    scanner(n, m, h);
    for (int i = 0; i < n; ++ i)
        scanf("%s", nm[i]);
    for (int i = 0; i < n; ++ i)
        scanf("%s", nh[i]);
    bool ok = true;
    for (int i = 0; i < n; ++ i)
    {
        mm.clear(), hh.clear();
        for (int j = 0; j < m; ++ j)
            if (nm[i][j] == '1') mm.push_back(j);
        for (int j = 0; j < h; ++ j)
            if (nh[i][j] == '1') hh.push_back(j); 
        if (mm.empty() != hh.empty()) 
        {ok = false; break;}    
        for (auto ii : mm)
            for (auto jj : hh)
                ans1.emplace_back(i, ii, jj);
        auto msiz = mm.size(), hsiz = hh.size();
        while (msiz > hsiz) 
        {
            ans2.emplace_back(i, mm.front(), hh.front());
            -- msiz, mm.pop_front();
        }
        while (hsiz > msiz)
        {
            ans2.emplace_back(i, mm.front(), hh.front());
            -- hsiz, hh.pop_front();
        }
        while (hsiz && msiz)
        {
            ans2.emplace_back(i, mm.front(), hh.front());
            -- msiz, mm.pop_front();
            -- hsiz, hh.pop_front();
        }
    }
    if (ok)
    {
        println(ans1.size());
        for (auto &ii : ans1)
            ii.__println();
        println(ans2.size());
        for (auto &ii : ans2)
            ii.__println();    
    } else puts("-1");

    return 0;
}

