/**
 *
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;
using longs = long long;
using longd = long double;
using ulongs = unsigned long long;

const int inf = 0x3f3f3f3f;
const longs INF = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-8;

vector<int> ss;
#define sss ss.begin(), ss.end()

void makelist(int lim = 1e9+7)
{
    int n = sqrt(lim);
    for (int i = 0; i <= n; ++ i)
    {
        ss.push_back(i*i);
    }
}

int query(int l, int r)
{
    auto ll = lower_bound(sss, l);
    auto rr = upper_bound(sss, r);
    return rr - ll;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, l, r;
    makelist();
    cin >> t;
    while (t --)
    {
        cin >> l >> r;
        cout << query(l,r) << endl;
    }

    return 0;
}