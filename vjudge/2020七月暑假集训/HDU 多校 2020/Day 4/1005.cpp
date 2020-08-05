/**
 * CE 两发。我真的仏了
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <unordered_map>
#include <algorithm>
#include <bitset>
#include <vector>
#include <cstring>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

ulongs pow27[12];

auto pre = []
{
    pow27[0] = 1;
    for (int i = 1; i < 12; ++i)
        pow27[i] = pow27[i - 1] * 27;
};

ulongs hashMachine(const string &s)
{
    auto len = s.length();
    auto cur = 0u;
    ulongs hash = 0;
    for (cur = 0; cur < len; ++ cur)
        hash += pow27[cur] * (s[cur] - 'a');
    return hash;
}

const int N = 1e5 + 5;
const longs mod = 1e9 + 7;
vector<ulongs> sen;
bitset<N> ava;
longs dp[N][2];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    pre();
    int t, n;
    string s;
    cin >> t;
    while (t --)
    {
        sen.clear(), ava.reset();
        cin >> n;
        memset(dp, 0, sizeof(longs) * 2 * (n + 1));
        for (int i = 0; i < n; ++ i)
            cin >> s, sen.push_back(hashMachine(s));
        for (int i = 1; i < n; ++ i)
            ava[i] = sen[i] != sen[i - 1];
        dp[0][1] = 0, dp[0][0] = 1;
        for (int i = 1; i < n; ++ i)
            dp[i][0] = (dp[i - 1][1] + dp[i - 1][0]) % mod,
            dp[i][1] = ava[i] ? dp[i - 1][0] : 0;
        auto ans = (dp[n - 1][1] + dp[n - 1][0]) % mod;
        cout << ans << endl;
    }

    return 0;
}