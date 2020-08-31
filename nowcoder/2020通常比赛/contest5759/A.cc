/**
 * 
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;
using longs = long long;
using longd = long double;
using ulongs = unsigned long long;

const int inf = 0x3f3f3f3f;
const longs INF = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-8;

const int N = 2e5 + 5;
int n, a[N], pre[N], nex[N];
bool cannot = false;

bool dcDFS(int ll, int rr)
{
    if (ll >= rr) return true;
    auto ii = ll;
    while (ii <= rr)
    {
        if (pre[ii] < ll && nex[ii] > rr)
            return dcDFS(ll, ii - 1) && dcDFS(ii + 1, rr);
        ++ ii;
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    map<int, int> mp;
    a[0] = 0; const int tail = n + 1;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> a[i];
        if (a[i] == a[i - 1]) cannot = true;
        if (mp[a[i]])
        {
            pre[i] = mp[a[i]];
            nex[mp[a[i]]] = i;
        }
        else pre[i] = 0;
        mp[a[i]] = i; nex[i] = tail;
    }
    if (cannot) cout << "fuchong" << endl;
    else
    {
        cannot = !dcDFS(1, n);
        cout << (cannot ? "fuchong" : "chong") << endl;
    }

    return 0;
}