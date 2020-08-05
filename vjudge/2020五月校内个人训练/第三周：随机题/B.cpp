/**
 *
 */
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    unordered_map<int, int> mm;
    int n, a, v;
    for (int i = 0; i < 2; ++ i)
    {
        cin >> n;
        while (n --)
        {
            cin >> a >> v;
            mm[a] = max(mm[a], v);
        }
    }
    longs ans = 0;
    for (auto ii : mm)
        ans += ii.second;
    cout << ans << endl;

    return 0;
}