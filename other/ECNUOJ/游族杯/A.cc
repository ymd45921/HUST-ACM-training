/**
 *
 */
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using longs = long long;

constexpr int inf = 0x3f3f3f3f;
constexpr double eps = 1e-8;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; string s;
    cin >> n;
    for (int i = 0; i < n; ++ i)
        cin >> s;
    cin >> m;
    for (int i = 0; i < m; ++ i)
        cin >> s;
    if (n <= m) cout << "Quber CC" << endl;
    else cout << "Cuber QQ" << endl;

    return 0;
}