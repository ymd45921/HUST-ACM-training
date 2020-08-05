/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <unordered_map>
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

const int N = 1e5 + 5;
unordered_map<int, bool> hmp;
int a[N];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t, n, k;
    cin >> t;
    while (t --)
    {
        cin >> n >> k;
        hmp.clear();
        for (int i = 0; i < n; ++ i)
            cin >> a[i];
        int head = 0;
        bool ok = true;
        for (int i = 0; i < n; ++ i)
        {
            if (!hmp[a[i]]) hmp[a[i]] = true;
            else
            {
                if (i - head + 1 > n)
                {
                    head = i;
                    hmp.clear();
                    hmp[a[i]] = true;
                }
                else if (a[head] == a[i])
                {

                }
            }
            if (i - head + 1 > n) {ok &= false; break;}
        }

        cout << (ok ? "YES" : "NO") << endl;
    }

    return 0;
}