#include <bits/stdc++.h>

using namespace std;

signed main() {
//    freopen("/home/nanami/CLionProjects/untitled/input.txt", "r", stdin);
    string a, b, ans;
    getline(cin, a);
    getline(cin, b);
    auto al = a.length(), bl = b.length();
    set<char> out;
    for (int i = 0, j = 0, k, l; i < al;) {
        for (l = i; l < al; ++ l)
            if (a[i] != a[l]) break;
        for (k = j; k < bl; ++ k)
            if (b[k] != a[i]) break;
        if (k - j > l - i) out.insert(a[i]);
        j = k, i = l;
    }
    for (auto ch : out) putchar(ch);
}