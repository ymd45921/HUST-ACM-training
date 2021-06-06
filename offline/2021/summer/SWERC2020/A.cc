#include <bits/stdc++.h>

using namespace std;
using llong = long long;

#define bigint int
bigint read() {
    bigint ret = 0;
    int f = 0, ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-') f = !f;
    for (; isdigit(ch); ch = getchar())
        ret = ret * 10 + ch - 48;
    return f ? -ret : ret;
}
#undef bigint

const int N = 1e5 + 5;
int cnt[N], tim[N], x[N];

signed main() {
#ifndef ONLINE_JUDGE
    freopen("/home/nanami/CLionProjects/untitled/input.txt", "r", stdin);
#endif
    int n = read(), k = read(), tot = 0;
    unordered_map<string, int> xx;
    vector<string> get({""});
    string s;
    xx.reserve(n * 10);
    for (int i = 1; i <= 3 * n; ++ i) {
        getline(cin, s);
        if (!xx[s]) {
            xx[s] = ++ tot;
            get.push_back(s);
        }
        tim[xx[s]] = i, ++ cnt[xx[s]];
    }
    iota(x, x + tot, 1);
    sort(x, x + tot, [](int a, int b) {
        if (cnt[a] == cnt[b]) return tim[a] > tim[b];
        else return cnt[a] > cnt[b];
    });
    for (int i = 0; i < k; ++ i)
        cout << get[x[i]] << endl;
    return 0;
}