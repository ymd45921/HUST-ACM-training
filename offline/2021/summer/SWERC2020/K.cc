#pragma GCC optimize(3, "Ofast", "inline")
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

const int N = 1050;
int border[N];

template <class T>
void build_kmp(const T *arr, int *kmp, int len) {
    int i = 0, j = kmp[0] = -1;
    while (i < len)
        if (-1 == j || arr[i] == arr[j])
            kmp[++ i] = ++ j;
        else j = kmp[j];
}

struct fws {
    using edge = tuple<int, int, int>;
    vector<int> head;
    vector<edge> e;

    void renew(int siz, int res = N) {
        head.resize(siz), e.clear();
        fill(head.begin(), head.end(), -1);
    }

    void add_edge(int u, int v, int w) {
        edge tmp(v, w, head[u]);
        head[u] = (int) e.size();
        e.emplace_back(move(tmp));
    }
};

struct string_hash {

    using ullong = unsigned long long;

    vector<ullong> val, pow;
    ullong base, off, length;

    string_hash(ullong base, ullong off, ullong length) :
            base(base), off(off), length(length), val(length), pow(length) {
        pow[0] = 1;
        for (int i = 1; i < length; ++ i)
            pow[i] = pow[i - 1] * base;
    }

    void calculate(const string &s) {
        const auto n = s.length();
        for (int i = 1; i <= n; ++ i)
            val[i] = val[i - 1] * base + s[i - 1] - 'a' + off;
    }

    ullong get(int l, int r) {
        const auto len = r - l;
        return val[r] - val[l] * pow[len];
    }
};

signed main() {
#ifndef ONLINE_JUDGE
    freopen("/home/nanami/CLionProjects/untitled/input.txt", "r", stdin);
#endif
    string s;
    cin >> s;
    int len = s.length();
    int l = 1, r = s.length();
    string ans;
    unordered_map<string_hash::ullong, int> cnt;
    string_hash hs(6151, 97, len + 1);
    hs.calculate(s);
    deque<pair<int, int>> res;
    auto check = [&](const int& mid) {
        cnt.clear(), res.clear();
        for(int i = 0, lim = len - mid; i <= lim; ++i) {
            auto tmp = hs.get(i, i + mid);
            cnt[tmp] += 1;
            if(cnt[tmp] == 1) res.emplace_back(i, i + mid);
        }
        for(auto &[ll, rr] : res) {
            if(cnt[hs.get(ll, rr)] == 1) break;
            res.pop_front();
        }
        if(!res.empty()) {
            auto [ll, rr] = res.front();
            ans = s.substr(ll, rr - ll);
            return true;
        }
        return false;
    };

    while(l <= r) {
        int mid = (l + r) >> 1;
        if(check(mid)) r = mid - 1;
        else l = mid + 1;
    }
    cout << ans;
}