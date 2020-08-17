/**
 * 何佳林使用的 KMP 做法
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

void buildKMP(const string &s, vector<int> &kmp, int len = 0)
{
    int i = 0, j = kmp[0] = -1;
    auto length = len ? len : s.length();
    while(i < length)
        if(-1 == j || s[i] == s[j])
            kmp[++ i] = ++ j;
        else j = kmp[j];
}

const int N = 5e6 + 5;
int cnt[26];
char tmp[N];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t, n; string s;
    vector<int> kmp, alp;
    auto check = [&](int k)
    {
        if (n % k) return false;
        auto len = n / k, nn = 2 * len;
        buildKMP(s, kmp, len);
        bool ok = false;
        for (int x = 1; x < k; ++ x)
        {
            for (int i = 0; i < len; ++ i)
                tmp[i] = tmp[i + len] = s[x * len + i];
            int i = 0, j = 0;
            while (i < nn && j < len)
                if (j == -1 || tmp[i] == s[j]) ++ i, ++ j;
                else j = kmp[j];
            ok |= (j == len);
            if (!ok) break;
        }
        return ok;
    };
    cin >> t;
    while (t --)
    {
        cin >> n >> s;
        kmp.clear(), alp.clear();
        kmp.resize(n + 1);
        memset(cnt, 0, sizeof cnt);
        for (auto ch : s) ++ cnt[ch - 'a'];
        for (auto ii : cnt) if (ii) alp.push_back(ii);
        auto gcd = alp.front(), find = 0;
        for (auto ii : alp) gcd = __gcd(ii, gcd);
        if (gcd == 1) {cout << "No" << endl; continue;}
        if (gcd == n || check(gcd)) {cout << "Yes" << endl; continue;}
        const int sq = sqrt(gcd);
        for (int i = 2; i <= sq; ++ i)
            if ((gcd % i == 0) && (check(i) || check(gcd / i)))
            {find = 1; break;}
        cout << (find ? "Yes" : "No") << endl;
    }

    return 0;
}