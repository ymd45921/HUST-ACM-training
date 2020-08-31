/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <vector>
#include <iomanip>

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

struct wp
{
    int a, d;
    longs t;

    wp(int a, int d): d(d), a(a)
    {
        longs n = 100 / a;
        if (n * a < 100) ++ n;
        t = (n - 1) * d;
    }
};
vector<wp> weapon;

int main()
{
    int t = nextInt(), n;
    cout << fixed << setprecision(6);
    while (t --)
    {
        n = nextInt();
        weapon.clear();
        for (int i = 0; i < n; ++ i)
        {
            int a = nextInt(), d = nextInt();
            weapon.emplace_back(a, d);
        }
        longs ans = 0;
        for (int i = 0; i < n; ++ i)
        {
            longs tmp = 0;
            const auto &ii = weapon[i];
            for (int j = 0; j < n; ++ j)
            {
                const auto &jj = weapon[j];
                if (ii.t < jj.t) tmp += 2;
                else if (ii.t == jj.t) tmp += 1;
                else tmp += 0;
            }
            if (tmp > ans) ans = tmp;
        }
        long double xx = ans / 2.0 / n;
        cout << xx << endl;
    }

    return 0;
}