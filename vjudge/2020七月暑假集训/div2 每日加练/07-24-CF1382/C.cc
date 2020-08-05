/**
 *
 * 思维：将 a 和 b 全部变成全 0 字符串：O(n) 小于 2n 的做法
 *
 *
 * 题解 https://codeforces.com/blog/entry/80427 中，
 * 两种难度的题目共计提供了五种做法，还是非常的有意思的，建议每一种都学习
 * 
 * 看来你已经完全忘记 getchar 会读取空格/回车这件事情了(
 */
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <vector>
#include <bitset>

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
bitset<N> a, b;

int main()
{
    int t = nextInt(), n, x;
    vector<int> p, q;
    while (t --)
    {
        a.reset(), b.reset();
        p.clear(), q.clear();
        n = nextInt();
        for (int i = 0; i < n; ++ i)
            x = getchar(), a[i] = (x == '1');
        while (getchar() != '\n');
        for (int i = 0; i < n; ++ i)
            x = getchar(), b[i] = (x == '1');
        while (getchar() != '\n');
        auto len = n - 1;
        for (int i = 0; i < len; ++ i)
            a[i] != a[i + 1] && (p.push_back(i + 1), 0),
            b[i] != b[i + 1] && (q.push_back(i + 1), 0);
        bool aa = a[len], bb = b[len];
        if (aa != bb) p.push_back(n);
        printf("%d", p.size() + q.size());
        for (auto &ii : p) printf(" %d", ii);
        for (auto ii = q.rbegin(); ii != q.rend(); ++ ii)
            printf(" %d", *ii);
        puts("");
    }

    return 0;
}