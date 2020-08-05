/**
 *
 *
 */
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;
typedef long long longs;
typedef long double longd;

const int N = 2e6+5;
const int inf = 0x7fffffff;
const longs INF = 0x7fffffffffffffff;
const double eps = 1e-8;

int solve(int n, int m)
{
    if (n == m) return n;
    int x = max(n,m), y = min(n,m);
    if (x == y<<1) return y<<1^1;
    else if (x < y<<1) return x+1;
    else return solve(x,y<<1)+1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, n, m;

    cin >> t;
    while (t --)
    {
        cin >> n >> m;
        cout << solve(n,m) << endl;
    }

    return 0;
}