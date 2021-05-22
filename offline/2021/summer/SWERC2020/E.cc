#include <bits/stdc++.h>

using namespace std;

const int N = 12;

signed main() {
    int n, a, b;
    cin >> n;
    int ans = 1e9;
    while (n --) {
        cin >> a >> b;
        ans = min(ans, b / a);
    }
    cout << ans << endl;
}