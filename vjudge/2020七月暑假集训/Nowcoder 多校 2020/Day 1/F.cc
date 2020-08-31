/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
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

inline longs gcd(longs a, longs b)
{
    if (a < b) swap(a, b);
    if (!b) return a;
    else return gcd(b, a % b);
}

string a, b;

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    while (cin >> a >> b)
        if (a.length() == b.length())
        {
            if (a == b) cout << '=' << endl;
            else if (a < b) cout << '<' << endl;
            else cout << '>' << endl;
        }
        else
        {
//            auto len = min(a.length(), b.length());
//            auto $a = a.substr(0, len), $b = b.substr(0, len);
//            if ($a == $b)
//            {
//
//            }
//            else if ($a > $b) cout << '>' << endl;
//            else cout << '<' << endl;
            longs _a = a.length(), _b = b.length();
            longs ca = 0, cb = 0, cnt = 0;
            longs lim = _a * _b / gcd(_a, _b);
            while (cnt < lim)
            {
                if (a[ca] != b[cb]) break;
                ca = (ca + 1) % _a;
                cb = (cb + 1) % _b;
                ++ cnt;
            }
            if (cnt == lim) cout << '=' << endl;
            else if (a[ca] < b[cb]) cout << '<' << endl;
            else cout << '>' << endl;
        }

    return 0;
}