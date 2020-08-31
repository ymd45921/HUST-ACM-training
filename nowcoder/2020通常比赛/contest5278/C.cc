/**
 *
 */
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
using longs = long long;
using longd = long double;
using ulongs = unsigned long long;

const int inf = 0x3f3f3f3f;
const longs INF = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-8;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s1, s2;
    cin >> s1 >> s2;
    int l1 = s1.length(), l2 = s2.length();
    if (l1 == l2)
    {
        if (s1 == s2) cout << -1;
        else cout << l1;
    }
    else cout << max(l1, l2);
    
    return 0;
}