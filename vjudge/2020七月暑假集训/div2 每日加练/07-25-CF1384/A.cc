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

int a[105];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t, n;
    string s(55, 'c');
    cin >> t;
    while (t --)
    {
        cin >> n;
        for (int i = 0; i < n; ++ i)
            cin >> a[i];
        cout << s << endl;
        for (uint i = 0; i < n; ++ i)
        {
            s[a[i]] ^= 1;
            cout << s << endl;
        }
    }

    return 0;
}