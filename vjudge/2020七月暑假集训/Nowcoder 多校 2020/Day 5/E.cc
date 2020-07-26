/**
 *
 * WA 了，是需要 __int128 吗
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <bitset>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;
using longs = long long;
using uint = unsigned;
using decimal = __int128;

inline int nextInt()
{
    int x = 0, f = 1, ch = getchar();
    while (!isdigit(ch)) if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

ostream &operator <<(ostream &out, __int128 x)
{
    if (x < 0) { out << '-'; x = -x; }
    static char str[40]; int cnt = 0;
    while (x > 9) { str[cnt ++] = (x % 10) ^ 48; x /= 10;}
    str[cnt ++] = x ^ 48;
    while (cnt --) out << str[cnt];
    return out;
}

inline decimal gcd(decimal a, decimal b)
{
    if (a < b) swap(a, b);
    if (!b) return a;
    else return gcd(b, a % b);
}

inline decimal lcm(decimal a, decimal b)
{ return a * b / gcd(a, b); }

const int N = 1e5 + 5;
int p[N], n;
bitset<N> vis;
vector<int> wa;

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    cin >> n;
    wa.clear();
    for (int i = 1; i <= n; ++ i) cin >> p[i];
    for (int i = 1; i <= n; ++ i)
        if (!vis[i])
        {
            vis[i] = true;
            int cnt = 1, cc = i;
            while (!vis[p[cc]])
                cc = p[cc], vis[cc] = true, ++ cnt;
            wa.push_back(cnt);
        }
    decimal ans = 1;
    for (auto & ii : wa) ans = lcm(ans, ii);
    auto mod = (decimal)pow(10, n);
    if (n <= 36) ans %= mod;
    cout << ans << endl;

    return 0;
}