/**
 *
 * 草，删除操作是没用的：确实是没用的 ==
 * mlgb
 *
 * 和之前的那个基因匹配题目有什么区别？
 * 可能是因为那个题目插入删除的 cost 不同，那个看 cost
 * 强烈建议找到那个题目进行对比（
 *
 * 所以问题转变成了对于 A 的任何子串求 B 的 LCS
 * 显然，这个可以通过预处理减少每一次询问所用的时间
 * 首先对于 A 串，预处理其所有后缀每个字母第一次出现的时间
 * 然后对于每一次询问，使用 DP 和 B 串进行匹配即可
 *
 * 那么具体怎么利用预处理匹配子串和模式串呢：
 * - f[i][j] 是和 B[1~i] 的公共序列长度达到 j 的最短 A' 前缀长度
 * - i 可以直接外延：f[i][j] = f[i - 1][j] (j < i)
 * - 若当前前缀没有超过字符串，可以尝试拓展当前字符(i)成为子串
 * - 对于模式串的所有字符，对于每一个可能匹配数进行上述的拓展
 * - 扫描最后 dp 数组的下三角，如果该列有符合要求的范围则说明可行
 * 总感觉这个转移有一些奇怪，但是似乎有确凿是正确的 ==
 * 但是反正都是 m²，其实乱搞一通就可以了（
 *
 * 像这种字符串 DP 的题目，往往都从 1 开始计算下标：
 * 因为往往需要一个 -1 位，使用 0 下标会导致不必要的麻烦；
 * 特别是这个题目默认下标从 1 开始………………（
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 1, ch = getchar();
    while (!isdigit(ch)) if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

const int N = 1e5 + 5;
int pos[N][26], f[30][30];
int A[N], B[30];

void process(const int *s, int n)
{
    for (int i = 0; i < 26; ++ i) pos[n + 1][i] = n + 1;
    const auto size = sizeof(pos[n]);
    for (int i = n; i > 0; -- i)
    {
        memcpy(pos[i], pos[i + 1], size);
        pos[i][s[i]] = i;
    }
    memcpy(pos[0], pos[1], size);
}

template <class T>
const T &update(T &a, const T &b)
{ return a > b ? (a = b) : b; }

int dp(int l, int r, const int *p, int m)
{
    for (int i = 0; i <= m; ++ i)
        for (int j = 0; j <= i; ++ j)
            f[i][j] = N;
    f[0][0] = l - 1;
    for (int i = 0; i < m; ++ i)
        for (int j = 0; j <= i; ++ j)
            update(f[i + 1][j], f[i][j]),
            f[i][j] < r &&
            update(f[i + 1][j + 1], pos[f[i][j] + 1][p[i + 1]]);
    for (int i = m; i; -- i)
        for (int j = i; j <= m; ++ j)
            if (f[j][i] <= r) return i;
    return 0;
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t, q, n, m, l, r;
    string a, b;
    cin >> t;
    while (t --)
    {
        cin >> a >> b >> q;
        n = a.length(), m = b.length();
        for (int i = 0; i < n; ++ i) A[i + 1] = a[i] - 'a';
        for (int i = 0; i < m; ++ i) B[i + 1] = b[i] - 'a';
        process(A, n);
        while (q --)
        {
            cin >> l >> r;
            auto len = r - l + 1;
            auto lcs = dp(l, r, B, m);
            cout << len + m - 2 * lcs << endl;
        }
    }

    return 0;
}