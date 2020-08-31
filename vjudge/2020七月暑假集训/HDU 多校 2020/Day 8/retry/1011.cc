/**
 *
 * 你妈的，题目读半天没有读懂；
 * 简要概括题意：
 * - 给你两个序列 a b，a 比 b 长
 * - 选出 a 的一段和 b 登场的连续子序列和 b 配对
 * - 如果对应位置的 a 和 b 属于集合 2S 那么就匹配
 * - 现要求出匹配的子序列乘对应权值的和
 * 集合 2S 的定义： S 的所有子集的异或和组成的集合
 *
 * 因为 2S 是一个很大的集合，求出来肯定不现实
 * …… 我也不知道该怎么说
 *
 * 答案说是要先求出线性基，那就先学习一下线性基的性质：
 * - 和基向量一样，线性基是对于异或问题的一种基
 * - 原数集中任何数字都可以由线性基异或构造出来
 * - 线性基中没有异或和为 0 的非空子集，不会有结果相同的两种构造方案
 * - 线性基是满足上述所有要求的最小集合
 * 线性基的一些应用：
 * - 询问数字是否在当前异或集合中
 * - 线性基合并；询问数集可构造的最大值和最小值
 *
 * 不过说句实话，要不是看着标程我也不太会写这个题目
 * 实际上对着标程写都不太能理解（
 * 其实就是对处理之后的 a 数组使用处理后的 b 数组进行匹配
 * 如果发现一次完整匹配，就标记一下对应的位置
 * 代码（也就是标程中）的 else if 是反向标记避免清空数组
 *
 * WA： KMP 板子是假板子，我爬了
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <vector>
#include <bitset>
#include <algorithm>
#include <cstring>

using namespace std;
using longs = long long;
using uint = unsigned;

template <class T>
inline T next()
{
    T x = 0; int f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

const int N = 2e5 + 5, M = 5e4 + 5, K = 105;
const int mod = 1e9 + 7;
int a[N], b[M], s[K];
bitset<N> match;

namespace LinearBase
{
    using T = int;
    constexpr int bit = 32;
    using U = uint;

    U lb[bit];

    void clear() {memset(lb, 0, sizeof lb);}

    void insert(T x)
    {
        uint ii = bit;
        auto xx = (U)x;
        while (ii --)
            if (xx >> ii & 1u)
            {
                if (!lb[ii])
                {
                    lb[ii] = xx;
                    break;
                }
                xx ^= lb[ii];
            }
    }

    U get(T x)
    {
        uint ii = bit;
        auto xx = (U)x;
        while (ii --)
            if (xx >> ii & 1u)
                xx ^= lb[ii];
        return xx;
    }
}

//void buildKMP(const int *arr, vector<int> &kmp, int length)
//{
//    int i = 0, j = kmp[0] = -1;
//    while(i < length)
//        if(-1 == j || arr[i] == arr[j])
//            kmp[++ i] = ++ j;
//        else j = kmp[j];
//}

void buildKMP(const int *arr, vector<int> &kmp, int length)
{
    kmp[0] = -1;
    for (int i = 1, j = -1; i < length; ++ i)
    {
        while (j != -1 && arr[j + 1] != arr[i]) j = kmp[j];
        if (arr[j + 1] == arr[i]) ++ j;
        kmp[i] = j;
    }
}

void useKMP(const int *target, const int *pattern, const vector<int> &kmp,
           const int tLength = 0, const int pLength = 0)
{
    for (int i = 0, j = -1; i < tLength; ++ i)
    {
        while (j != -1 && pattern[j + 1] != target[i]) j = kmp[j];
        if (pattern[j + 1] == target[i]) ++ j;
        if (j + 1 == pLength) match[i + 1 - pLength] = true, j = kmp[j];
        else if (i >= pLength - 1) match[i + 1 - pLength] = false;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    using ::next;

    int t = next<int>();
    while (t --)
    {
        int n = next<int>(), m = next<int>(),
            k = next<int>();
        LinearBase::clear();
        for (int i = 0; i < n; ++ i)
            a[i] = next<int>();
        for (int i = 0; i < m; ++ i)
            b[i] = next<int>();
        for (int i = 0; i < k; ++ i)
            s[i] = next<int>(),
            LinearBase::insert(s[i]);
        for (int i = 0; i < n; ++ i)
            a[i] = LinearBase::get(a[i]);
        for (int i = 0; i < m; ++ i)
            b[i] = LinearBase::get(b[i]);
        vector<int> kmp;
        kmp.resize(m + 1);
        buildKMP(b, kmp, m);
        useKMP(a, b, kmp, n, m);
        longs ans = 0;
        for (int i = n - m; i >= 0; -- i)
            ans = (2 * ans + match[i]) % mod;
        printf("%lld\n", ans);
    }

    return 0;
}