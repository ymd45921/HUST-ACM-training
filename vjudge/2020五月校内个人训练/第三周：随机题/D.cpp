/**
 *
 */
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;
const int N = 1e6 + 5;

int n, a[N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n; bool found = false;
    int l = 1, r = 1; bool nop = false;
    for (int i = 1; i <= n; ++ i) cin >> a[i];
    for (int i = n - 1; i; -- i)
        if (a[i] > a[i + 1])
        {
            auto rr = i + 1;
            while (rr < n && a[rr] == a[rr + 1]) ++ rr;
            for (int j = 1; j <= rr; ++ j)
                if (a[j] > a[rr])
                {
                    auto ll = j;
                    reverse(a + ll, a + rr + 1);
                    bool ok = true;
                    for (int ii = 1; ii < n; ++ ii)
                        ok &= (a[ii] <= a[ii + 1]);
                    if (!ok) nop = true;
                    else l = ll, r = rr;
                    found = true; break;
                }
            if (found) break;
        }
    string s = to_string(l) + " " + to_string(r);
    cout << (nop ? "impossible" : s) << endl;

    return 0;
}