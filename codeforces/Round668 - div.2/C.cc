/**
 *
 * 虽然代码写的傻逼，但是能 A 就没问题了？
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#include <cstring>

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

const int N = 3e5 + 5;
int t, k, n;
string s;
vector<int> pos;

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    cin >> t;
    while (t --)
    {
        cin >> n >> k >> s;
        bool ok = !(k % 2);
        pos.clear();
        for (int i = 0; i < k; ++ i)
        {
            auto ii = i;
            while (s[ii] == '?' && ii < n) ii += k;
            if (ii >= n) continue;
            auto val = s[ii];
            ii = i;
            while (ii < n)
                if (s[ii] == '?') s[ii] = val, ii += k;
                else if (s[ii] != val) {ok = false; break;}
                else ii += k;
        }
        int cnt0 = 0, cnt1 = 0;
        for (int i = 0; i < k; ++ i)
            if (s[i] != '?') ++ (s[i] == '1' ? cnt1 : cnt0);
        if (cnt0 > k / 2 || cnt1 > k / 2) ok = false;
        if (ok) cout << "YES" << endl;
        else cout << "NO" << endl;
    }

    return 0;
}