/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;
using longs = long long;
using uint = unsigned;

const char yes[] = "Nobody knows it better than me!";
const char no[] = "Fake news!";

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
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

istream &operator >>(istream &in, __int128 &x)
{
    __int128 xx = 0, f = 1; static char ch;
    ch = in.get();
    while (!isdigit(ch)) { if (ch=='-') f=-1; ch = in.get(); }
    while (isdigit(ch)) { xx=(xx<<1)+(xx<<3)+(ch^48); ch = in.get(); }
    x = (xx * f); return in;
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    __int128 t, n;
    cin >> t;
    while (t --)
    {
        cin >> n;
        __int128 sum = n * (n + 1) * (2 * n + 1) / 6;
        __int128 sq = sqrt(sum);
        cerr << sum << endl;
        if(sq * sq == sum) cout << "Fake news!" << endl;
        else cout << "Nobody knows it better than me!" << endl;
    }

    return 0;
}