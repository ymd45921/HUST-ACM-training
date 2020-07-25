/**
 *
 * 测试可用的模数：
 * 常见模数好像没有可以使用的
 */
#include <cstdio>
#include <cctype>

#define MOD 1ull << 63u

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;

inline int nextInt()
{
    int x = 0, f = 1, ch = getchar();
    while (!isdigit(ch)) if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

const int N = 2e6 + 5;
ulongs fib[N] = {1, 1, 2};
const __int128 mod = MOD;
auto preFib = []{for (int i = 3; i < N; ++ i) fib[i] = (fib[i - 1] + fib[i - 2]) % mod;};

inline ulongs nextFib()
{
    ulongs ret = 0;
    int len = nextInt();
    for (int i = 1; i <= len; ++ i)
        nextInt() && (ret = (fib[i] + ret) % mod);
    return ret;
}

int main()
{
    preFib();
    int t = nextInt();
    while (t --)
    {
        __int128 a = nextFib(), b = nextFib();
        __int128 ab = a * b % mod;
        __int128 cc = nextFib(), c = (ulongs)ab;
        int ptr = 1;
        while ((cc + fib[ptr]) % mod != c) ++ ptr;
        printf("%d\n", ptr);
    }
    return 0;
}