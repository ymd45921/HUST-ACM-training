/**
 *
 * 读假题：任何两个好像素点之间的像素点都是好像素
 * 意思就是说没有凹点，没有空心；整体图形是突起的
 * 
 * TODO: 尝试去理解理解
 * 更好的方法是结合凸联通块的性质
 * 对某一行 i 和某个边长 k 可以 O(1) 地检查其是否可以是边长为 k 的正方形的顶边
 * 由于 k 作为答案，若可行只会递增，而 i 也只会递增
 * 因此时间复杂度是 O(N)
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
pair<int, int> g[N];

#define a first
#define b second

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = scanner.nextInt();
    const auto isPerimeter = 
    [&](int i, int k) -> bool
    {
        int ll = g[i].a, rr = g[i].b, 
            bb = i + k - 1;
        if (rr - ll + 1 < k) return false;
        if (bb  > n) return false;
        int ii = max(ll, g[bb].a);
        return rr - ii + 1 >= k && g[bb].b - ii + 1 >= k;
    };
    for (int i = 0; i < n; ++ i)
        scanner(g[i].a, g[i].b);
    int k = 1;
    for (int i = 0; i < n; ++ i)
        while (isPerimeter(i, k + 1)) ++ k;
    println(k);    

    return 0;
}

