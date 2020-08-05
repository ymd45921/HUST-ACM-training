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
    int n, r1[100], r2[100];
    memset(r1, 0, sizeof r1);
    memset(r2, 0, sizeof r2);
    cin >> s1 >> s2 >> n;
    for (int i = 0; i < s1.length(); ++ i)
        ++ r1[s1[i] - 'A'];
    for (int i = 0; i < s2.length(); ++ i)
        ++ r2[s2[i] - 'A'];
    for (int i = 3; i <= n; ++ i)
    {
        int *src = (i & 1) ? r2 : r1;
        int *des = (i & 1) ? r1 : r2;
        for (int ii = 0; ii < 100; ++ ii)
            des[ii] += src[ii];
    }
    int *now = (n & 1) ? r1 : r2;
    for (int ii = 0; ii < 100; ++ ii)
    {
        if (!now[ii]) continue;
        cout << (char)(ii+'A') << ": " << now[ii] << endl;
    }

    return 0;
}