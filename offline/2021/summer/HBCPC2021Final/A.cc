#include <bits/stdc++.h>

using namespace std;
using llong = long long;

const int N = 30000;
char hs[][5] = {
        "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111",
        "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"
};
char a[N], b[N], c[N];

int hexToInt(char ch) {
    if (isdigit(ch)) return ch - '0';
    else return ch - 'A' + 10;
}

void toBinaryString() {
    int nb = strlen(b);
    for (int i = 0; i < nb; ++ i)
        strcpy(c + i * 4, hs[hexToInt(b[i])]);
    c[nb * 4] = 0;
}

int clzOffset(const char *s) {
    auto t = s;
    while (*t == '0') ++ t;
    return int(t - s);
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen(R"(C:\Users\dell\CLionProjects\untitled\input.txt)", "r", stdin);
#endif
    int T;
    cin >> T;
    while (T --) {
        cin >> a >> b;
        int na = strlen(a), nb = strlen(b);
        int k = na - 1;
        toBinaryString();
        //// cerr << c << endl, b[na] = 0;
        fill(c + nb * 4, c + nb * 4 + k, '0');
        c[nb * 4 + k] = 0;
        int nc = strlen(c), st = clzOffset(c);
        while (true) {
            if (st + k >= nc) break;
            auto x = c + st;
            //// cerr << ' ' << x << endl;
            //// cerr << '^' << a << endl;
            for (int i = 0; i < na; ++ i)
                b[i] = x[i] == a[i] ? '0' : '1';
            //// cerr << '=' << b << endl;
            for (int i = 0; i < na; ++ i)
                x[i] = x[i] == a[i] ? '0' : '1';
            st += clzOffset(x);
        }
        //// cerr << "c = " << c << endl;
        //// cerr << "x = " << (c + st) << endl;
        puts(c + nc - k);
    }
}
