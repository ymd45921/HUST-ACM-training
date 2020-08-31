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

    int n, k;
    cin >> n;
    if (n == 1)
    {
        cout << n << endl;
        cout << 1 << endl;
    }
    else if (n == 2)
    {
        cout << 2 << endl;
        cout << 0 << endl;
        cout << "11" << endl;
    }
    else
    {
        k = n - 1;
        cout << k << endl;
        string s = "";
        int len = 2;
        cout << 1 << s << 1 << endl;
        while (len < n)
        {
            ++ len;
            s.append("0");
            cout << 1 << s << 1 << endl;
        }
    }

    return 0;
}