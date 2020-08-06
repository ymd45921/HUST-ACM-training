/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>

#define NUM(x) (isdigit(x) ? ((x)- '0') : ((x) - 'A' + 10))

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

string s, c, a, b;
char op;

longs trans(const string &n, const int base)
{
    longs ans = 0, pow = 1;
    auto rend = n.rend();
    for (auto ii = n.rbegin(); ii != rend; ++ ii)
        ans += NUM(*ii) * pow, pow *= base;
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    while (cin >> s)
    {
        int pose, pop, xx = 1, len = s.length();
        for (int i = 0; i < len; ++ i)
            if (isdigit(s[i]) || isalpha(s[i])) xx = max(xx, NUM(s[i]));
            else if (s[i] == '=') pose = i;
            else pop = i, op = s[i];
        a = s.substr(0, pop);
        b = s.substr(pop + 1, pose - pop - 1);
        c = s.substr(pose + 1);
        if (a.length() == 1 && b.length() == 1 && c.length() == 1)
        {
            longs aa = NUM(a[0]), bb = NUM(b[0]), cc = NUM(c[0]);
            switch (op)
            {
                case '/':
                    if (aa % bb != 0 || aa / bb != cc) xx = 17; break;
                case '+':
                    if (aa + bb != cc) xx = 17; break;
                case '-':
                    if (aa - bb != cc) xx = 17; break;
                case '*':
                    if (aa * bb != cc) xx = 17; break;
                default: break;
            }
            ++ xx;
        }
        else for (++ xx; xx <= 16; ++ xx)
        {
            longs aa = trans(a, xx);
            longs bb = trans(b, xx);
            longs cc = trans(c, xx);
            auto breakSignal = false;
            switch (op)
            {
                case '/':
                if (aa % bb == 0 && aa / bb == cc) breakSignal = true; break;
                case '+':
                if (aa + bb == cc) breakSignal = true; break;
                case '-':
                if (aa - bb == cc) breakSignal = true; break;
                case '*':
                if (aa * bb == cc) breakSignal = true; break;
                default: break;
            }
            if (breakSignal) break;
        }
        if (xx > 16) cout << -1 << endl;
        else cout << xx << endl;
    }

    return 0;
}