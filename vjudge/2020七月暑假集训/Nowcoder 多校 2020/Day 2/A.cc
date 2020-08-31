/**
 *
 * 没啥人做这个题目…… 没想到是个哈希暴力（
 *
 * 牛客不准 unsigned 和 signed 比较 ==
 * 牛客的 g++ 14 编译抛出了 Assembler Error（
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <vector>

using namespace std;
using longs = long long;
using ulongs = unsigned long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 1, ch = getchar();
    while (!isdigit(ch)) if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

const uint N = 1e6 + 5;
const uint M = 1e5 + 5;
const uint mod = 998244353;

namespace StringHash
{
    using hashArray = vector<ulongs>;

    struct hashMachine
    {
        int base, offset;
        hashArray pow;

        static int idx(const char ch){return ch - 'a';}

        explicit hashMachine(int n, int b = 233, int k = 5): base(b), offset(k)
        {
            pow.resize(n);
            pow[0] = 1;
            for (int i = 1; i < n; ++ i)
                pow[i] = pow[i - 1] * base;
        }

        void make(const char *s, hashArray &var) const
        {
            int n = strlen(s);
            for (int i = 1; i <= n; ++ i)
                var[i] = var[i - 1] * base + idx(s[i - 1]) + offset;
        }

        ulongs get(hashArray &var, int l, int r) const
        {
            if (!l) return var[r];
            auto len = r - l;
            return var[r] - var[l] * pow[len];
        }
    };
}

void buildKMP(const string &s, vector<int> &kmp)
{
    kmp[0] = -1;
    int i = 0, j = -1;
    int length = s.length();
    while(i < length)
    {
        if(-1 == j || s[i] == s[j])
            kmp[++ i] = ++ j;
        else j = kmp[j];
    }
}

char s[N];
unordered_map<ulongs, uint> $map;
vector<int> $next[M];
vector<ulongs> $hash[M];
ulongs cnt[N], ans = 0;

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    auto hm = StringHash::hashMachine(N, 6151);
    auto handleHash = [&](int ii)
    {
        auto len = strlen(s);
        $next[ii].resize(len + 1);
        $hash[ii].resize(len + 1);
        buildKMP(s, $next[ii]);
        hm.make(s, $hash[ii]);
        for (uint i = 0; i < len; ++ i)
            ++ $map[hm.get($hash[ii], i, len)];
    };
    int n; cin >> n;
    for (int i = 0; i < n; ++ i)
        cin >> s, handleHash(i);
    for (int i = 0; i < n; ++ i)
    {
        auto length = $hash[i].size() - 1;
        auto &kmp = $next[i];
        for (uint j = 1; j <= length; ++ j)
        {
            cnt[j] = $map[hm.get($hash[i], 0, j)];
            if (kmp[j] != -1) cnt[kmp[j]] -= cnt[j];
        }
        for (uint j = 1; j <= length; ++ j)
            ans = (ans + cnt[j] * j % mod * j) % mod;
    }
    cout << ans << endl;

    return 0;
}