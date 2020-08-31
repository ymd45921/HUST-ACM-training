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

void buildKMP(const int *arr, vector<int> &kmp, int length)
{
    int i = 0, j = kmp[0] = -1;
    while(i < length)
        if(-1 == j || arr[i] == arr[j])
            kmp[++ i] = ++ j;
        else j = kmp[j];
}

void $buildKMP(const int *arr, vector<int> &kmp, int length)
{
    int i = 0, j = kmp[0] = -1;
    while(i < length)
        if(-1 == j || arr[i] == arr[j])
            if (++ i == length || arr[i] != arr[++ j])          // 小心数组越界
                kmp[i] = j;
            else kmp[i] = kmp[j];
        else j = kmp[j];
}

void useKMP(const int *target, const int *pattern, const vector<int> &kmp,
            const int tLength, const int pLength)
{
    int i = 0, j = 0, cnt = 0;
    while (i < tLength)
        if (j == -1 || target[i] == pattern[j])
        {
            ++ i, ++ j;
            if (j == pLength) ++ cnt, match[i - pLength] = true, j = kmp[j];
            else if (i >= pLength) match[i - pLength] = false;
        }
        else j = kmp[j];
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
        $buildKMP(b, kmp, m);
        useKMP(a, b, kmp, n, m);
        longs ans = 0;
        for (int i = n - m; i >= 0; -- i)
            ans = (2 * ans + match[i]) % mod;
        printf("%lld\n", ans);
    }

    return 0;
}