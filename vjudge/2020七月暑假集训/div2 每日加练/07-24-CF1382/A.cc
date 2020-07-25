/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <bitset>

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

const int N = 1050;
bitset<N> a;

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t, x, aa, bb;
    cin >> t;
    while (t --)
    {
        cin >> aa >> bb;
        a.reset();
        for (int i = 0; i < aa; ++ i)
            cin >> x, a[x] = true;
        int found = -1;
        for (int i = 0; i < bb; ++ i)
            cin >> x, a[x] && (found = x);
        if (~found) cout << "YES\n1 " << found << endl;
        else cout << "NO" << endl;
    }

    return 0;
}