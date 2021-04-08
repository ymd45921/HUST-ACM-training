#include <bits/stdc++.h>

using namespace std;
const auto null = nullptr;

const int N = 2060;
int a[N], tmp[N], in[N];

void operate1(int n) {
    for (int i = 1; i <= n; i += 2)
        swap(a[i], a[i + 1]);
}

void operate2(int n) {
    const auto half = n / 2;
    for (int i = 1; i <= half; ++ i)
        tmp[half + i] = a[i];
    for (int i = half + 1; i <= n; ++ i)
        tmp[i - half] = a[i];
    memcpy(a, tmp, sizeof(int) * (n + 1));
}

bool compare(int nn) {
    for (int i = 1; i <= nn; ++ i)
        if (a[i] != in[i]) return false;
    return true;
}

signed main() {
    ios::sync_with_stdio(false),
    cin.tie(null), cout.tie(null);

    int n, nn;
    cin >> n, nn = n * 2;
    for (int i = 1; i <= nn; ++ i)
        cin >> in[i];
    iota(a, a + nn + 1, 0);
    int lim = n % 2 ? nn : 4, ans = -1;
    for (int i = 1; i <= lim; ++ i) {
        (i % 2 ? operate1 : operate2)(nn);
        if (compare(nn)) {
            ans = min(lim - i, i);
            break;
        }
    }
    cout << ans << endl;
}