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
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

string s, a, p = "abacaba";
bool equals(int ii)
{
    for (int i = 0; i < 7; ++ i)
        if (s[i + ii] == '?' || s[i + ii] == p[i]) continue;
        else return false;
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t, n;
    cin >> t;
    while (t --)
    {
        cin >> n >> s;
        auto aa = s.find(p);
        auto bb = s.rfind(p);
        if (aa != string::npos)
            if (aa != bb) {cout << "No" << endl; continue;}
            else
            {
                a = s;
                for (auto &i : a) i == '?' && (i = 'z');
                cout << "Yes\n" << a << endl;
            }
        else
        {
            a = s;
            auto len = s.length(), lim = len - 6;
            bool found = false;
            for (int i = 0; i < lim; ++ i)
                if (equals(i))
                {
                    a.replace(i, 7, p);
                    for (auto &ii : a) ii == '?' && (ii = 'z');
                    auto aaa = a.find(p), bbb = a.rfind(p);
                    if (aaa != bbb) { a = s; continue; }
                    found = true;
                    break;
                }
            cout << (found ? "Yes\n" + a : "No") << endl;
        }
    }

    return 0;
}