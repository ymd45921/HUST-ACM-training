/**
 *
 *
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

namespace In
{
    template <class T>
    inline void read(T &x)
    {
        x = 0;
        int ch = getchar(), f = 0;
        while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
        x = f ? -x : x;
    }

    template <class T, class... Ts>
    inline void read(T &x, Ts &... y)
    {return read(x), read(y...);}
}
using namespace In;
const int maxn = 2e5 + 10;

char s[maxn];

int main()
{
    // ios::sync_with_stdio(false);
    // std::cin.tie(nullptr);
    // std::cout.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int tcase;
    int n;
    read(tcase);
    while(tcase--)
    {
        read(n);
        cin >> s + 1;
        int ans = 0;
        for(int i = 1; i <= n - 3; i++)
        {
            if(s[i] == 'C' && s[i+1] == 'C' && s[i + 2] == 'P' && s[i + 3] == 'C')
            {
                s[i + 1] = '#';
                s[i + 2] = '#';
                ans++;
            }
        }

        for(int i = 1; i <= n - 2; i++)
        {
            if(s[i] == 'C')
            {
                if(s[i + 1] == 'C')
                {
                    if(s[i + 2] == 'P' || s[i + 2] == 'C')
                    {
                        ans++;
                        break;
                    }
                }
                else if(s[i + 1] == 'P')
                {
                    if(s[i + 2] == 'C')
                    {
                        ans++;
                        break;
                    }
                }
            }
        }

        printf("%d\n", ans);
    }


    return 0;
}

