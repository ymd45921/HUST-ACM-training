/**
 *
 * 虽然可以按顺序选择一遍，但是为什么不直接构造呢？
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <bitset>
#include <cassert>
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

const int N = 1060;
int a[N], t, n;
bitset<N> use;

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    cin >> t;
    while (t --)
    {
        cin >> n;
        int cnt0 = 0, cnt1 = 0, k = 0;
        use.reset();
        for (int i = 0; i < n; ++ i)
            cin >> a[i], ++ (a[i] ? cnt1 : cnt0);
        if (cnt0 >= n / 2)
        {
            cout << cnt0 << endl;
            while (cnt0 --) cout << "0 ";
            cout << endl;
        }
        else
        {
            assert(cnt1 > n / 2);
            if (cnt1 % 2) -- cnt1;
            cout << cnt1 << endl;
            while (cnt1 --) cout << "1 ";
            cout << endl;
        }
    }

    return 0;
}