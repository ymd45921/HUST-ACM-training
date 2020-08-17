/**
 *
 * 标准做法是字符串哈希
 * 标程采用的是多哈希做法
 * 
 * 比 KMP 慢了十倍（
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_set>

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

const int N = 5e6 + 5;
int cnt[26];

namespace StringHash
{
    const int base = 6151;
    const int offset = 11;
    ulongs pow[N], var[N];

    auto idx = [](const char ch){return ch - 'a' + offset;};

    void calculate(const char *s)
    {
        int n = strlen(s);
        for (int i = 1; i <= n; ++ i)
            var[i] = var[i - 1] * base + idx(s[i - 1]);
    }

    void init(int len = N)
    {
        pow[0] = 1;
        for (int i = 1; i < len; ++ i)
            pow[i] = pow[i - 1] * base;
    }

    ulongs getHashCode(int l, int r)
    {
        auto length = r - l;
        return var[r] - var[l] * pow[length];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t, n;
    vector<int> alp;
    string s;
    StringHash::init();
    auto check = [&](int len) -> bool
    {
        using namespace StringHash;
        auto pw = StringHash::pow;
        unordered_set<ulongs> table;
        auto ha = getHashCode(0, len);
        table.insert(ha);
        for (int i = len; i > 1; -- i)
        {
            ha = (ha - idx(s[len - i]) * pw[len - 1]) * base + idx(s[len - i]);
            table.insert(ha);
        }
        auto times = n / len;
        for (int i = 1; i < times; ++ i)
        {
            auto xx = getHashCode(i * len, (i + 1) * len);
            if (!table.count(xx)) return false;
        }
        return true;
    };
    cin >> t;
    while (t --)
    {
        cin >> n >> s;
        alp.clear(), memset(cnt, 0, sizeof cnt);
        for (auto ch : s) ++ cnt[ch - 'a'];
        for (auto ii : cnt) if (ii) alp.push_back(ii);
        auto gcd = alp.front();
        for (auto ii : alp) gcd = __gcd(ii, gcd);
        if (gcd == 1) {cout << "No" << endl; continue;}
        if (gcd == n) {cout << "Yes" << endl; continue;}
        StringHash::calculate(s.c_str());
        bool ok = false;
        for (int i = 2; i <= gcd; ++ i)
            if (gcd % i == 0 && check(n / i))
            {ok = true; break;}
        cout << (ok ? "Yes" : "No") << endl;
    }

    return 0;
}