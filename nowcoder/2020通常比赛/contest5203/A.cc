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

    char s[100];
    cin >> s;
    int x = atoi(s);
    reverse(s, s + strlen(s));
    cout << atoi(s)+x;

    return 0;
}