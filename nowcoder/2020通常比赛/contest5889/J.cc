/**
 *
 * 草，几度WA还是读错题目导致
 */
#define USING_STDIO 0
#if USING_STDIO
#include <cstdio>
#include <cctype>
#else
#include <iostream>
#include <iomanip>
#endif

#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;
typedef long long longs;
using ulongs = unsigned long long;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;
const int mod = 1e9 + 7;

template <typename number>
int compareTo(number x) {return x < -eps ? -1 : x > eps;}
template <typename number>
int compareTo(number a, number b) {return compareTo(a-b);}

ulongs fib(ulongs n)
{
    if (n < 0) return 0;
    ulongs mat[2][2] = {{1, 0}, {0, 1}},
            xx[2][2] = {{1, 1}, {1, 0}},
            ii[2][2];
    while (n)
    {
        if (n & 1u)
        {
            memset(ii, 0, sizeof ii);
            for (int i = 0; i < 2; ++ i)
                for (int j = 0; j < 2; ++ j)
                    for (int k = 0; k < 2; ++ k)
                        ii[i][j] += mat[i][k] * xx[k][j],
                        ii[i][j] %= mod;
            memcpy(mat, ii, sizeof ii);
        }
        memset(ii, 0, sizeof ii);
        for (int i = 0; i < 2; ++ i)
            for (int j = 0; j < 2; ++ j)
                for (int k = 0; k < 2; ++ k)
                    ii[i][j] += xx[i][k] * xx[k][j],
                    ii[i][j] %= mod;
        memcpy(xx, ii, sizeof ii);
        n >>= 1u;
    }
    return mat[1][0] % mod;
}

const ulongs* modFib(ulongs n)
{
    static ulongs cnt[5]; 
    cnt[0] = 0;
    cnt[1] = fib(n - 5);
    cnt[2] = fib(n - 6);
    cnt[3] = fib(n - 2);
    cnt[4] = fib(n - 3);
    return cnt;
}

#if USING_STDIO
inline int nextInt()
{
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
    return x*f;
}
#endif

namespace FastLog2
{
    int mem[256];

    void preLog2()
    {
        for (int i = 1; i < 256; ++ i)
            mem[i] = (int)log2(i);
    }

    ulongs LOG2(ulongs x){
        ulongs ans = 0;
        if (x >= 4294967296ull  ) {ans += 32; x >>= 32u;}
        if (x >= 65536          ) {ans += 16; x >>= 16u;}
        if (x >= 256            ) {ans += 8 ; x >>= 8u ;}
        if (x >= 16             ) {ans += 4 ; x >>= 4u ;}
        return ans + mem[x];
    }
}

namespace UnitTest
{
    void log2Test(ulongs l, ulongs r)
    {
        for (auto i = l; i <= r; ++ i)
            if (FastLog2::LOG2(i) == (ulongs)log2(i)) continue;
            else
            {
                cerr << FastLog2::LOG2(i) << "\t\t!=\t\t" << (ulongs)log2(i) << endl;
                break;
            }
        cerr << "test end." << endl;
    }

    void fibTest3(ulongs x)
    {
        if (fib(x + 1) != (fib(x) + fib(x - 1)) % mod)
            cerr << "Rejected." << endl;
        else cerr << "Accepted." << endl;
    }

    void fibTest(int n = 300)
    {
        static ulongs xx[500], yy[500];
        xx[0] = xx[1] = yy[0] = yy[1] = 1;
        for (int i = 2; i <= n; ++ i)
            xx[i] = xx[i - 1] + xx[i - 2],
                    yy[i] = (yy[i - 1] + yy[i - 2]) % mod;
        for (int i = 1; i < n; ++ i)
            cerr << "fib[" << i << "]:\t\t" << (fib(i) == yy[i - 1] ? ' ' : '!')
                 << fib(i) << "\t\t" << yy[i - 1] << "\t\t" << xx[i - 1] << endl;
        cerr << "test end." << endl;
    }

    void fibTest2(ulongs n = 1e9)
    {
        ulongs xx = 0, yy = 1, now;
        for (auto i = 2ull; i < n; ++ i)
        {
            now = (xx + yy) % mod;
            xx = yy, yy = now;
            auto cc = fib(i);
            if (cc != now)
            {
                cerr << "fib[" << i << "]:\t\t";
                cerr << cc << " != " << now << endl;
                break;
            }
        }
        cerr << "test end." << endl;
    }
}

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif
//    FastLog2::preLog2();
    for (int i = 0; i <= 10; ++ i)
        cerr << fib(i) << endl;

    int t; cin >> t;
    unsigned long long x;
    while (t --)
    {
        cin >> x;
        longs ans = 1;
        if (x > 2)
        {
            ans = fib(x) + (x & 1u ? -1 : 1);
            auto mod5 = modFib(x);
            ulongs m5 = 0;
            for (int i = 1; i < 5; ++ i)
                m5 += i * mod5[i] % mod;
            ans += m5 % mod;
            // TODO: 处理 log2 的累加和
            while (ans < 0) ans += mod;
        }
        cout << ans % mod << endl;
    }

    return 0;
}