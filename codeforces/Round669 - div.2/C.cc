/**
 *
 * 1e4 范围写 1060，真有你的啊
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <vector>
#include <bitset>
#include <cassert>

using namespace std;
using longs = long long;
using uint = unsigned;

#define ask(x, y) cout << "? " << x << ' ' << y << endl; cin
#define ok(vec) cout << "! "; \
for (int i = 1; i <= n; ++ i) cout << vec[i] << ' '; cout << endl

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, cnt = 1, p[10010];
    bitset<10010> tag, use;
    cin >> n;
    if (n == 1) return cout << "! 1" << endl, 0;
    int p1 = 1, p2 = 2, re0, re1;
    while (cnt < n)
    {
        ask(p1, p2) >> re0;
        ask(p2, p1) >> re1;
        if (re0 < re1)
        {
            tag[p2] = true;
//            assert(use[re1] == false);
            use[re1] = true;
            p[p2] = re1;
            while (p1 == p2 || tag[p2]) ++ p2;
        }
        else
        {
            tag[p1] = true;
//            assert(use[re0] == false);
            use[re0] = true;
            p[p1] = re0;
            while (p1 == p2 || tag[p1]) ++ p1;
        }
        ++ cnt;
    }
    int last_ind = 0, last_val = 0;
    for (int i = 1; i <= n; ++ i)
        if (!tag[i]) {last_ind = i; break;}
    for (int i = 1; i <= n; ++ i)
        if (!use[i]) {last_val = i; break;}
    p[last_ind] = last_val, ok(p);

    return 0;
}