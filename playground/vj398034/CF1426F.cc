/**
 *
 * 基础的 DP
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;
using longd = long double;

#define nextInt nexT<int>
#define nextLongs nexT<longs>
#define next128 nexT<__int128>
#define eprintf(x...) fprintf(stderr, x...)
#define var(x) ""#x" = " << x 
#define lll __int128

template<class T>
inline T nexT()
{
    T x = 0; int f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

namespace In
{
    template <class T>
    inline void read(T &x)
    {
        x = 0;
        int ch = getchar(), f = 1;
        while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
        x = f ? -x : x;
    }

    template <class T, class... Ts>
    inline void read(T &x, Ts &... y)
    {return read(x), read(y...);}
}

const longs mod = 1e9 + 7;
const int N = 2e5 + 5;
int pow3[N], b[N], a[N], suf[N];
#define pre(x) suf[0] - suf[x + 1]

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif

    pow3[0] = 1;
    for (int i = 1; i < N; ++ i)
        pow3[i] = pow3[i - 1] * 3ll % mod;
    string s;
    int n;
    cin >> n;
    while (!s.length()) cin >> s;
    for (int i = n - 1; i >= 0; -- i)
        suf[i] = suf[i + 1] + (bool)(s[i] == '?');
    for (int i = n - 1, cc = 0, c = 0; i >= 0; -- i)
        if (s[i] == 'c') ++ cc;
        else if (s[i] == 'b') b[i] = cc * (longs)pow3[c] % mod;
        else if (s[i] == '?') 
        {
            b[i] = (cc ++) * (longs)pow3[c] % mod;
            ++ c;
        }
    for (int i = n - 1, cb = 0, c = 0; i >= 0; -- i)  
        if (s[i] == 'b') cb = (cb + b[i]) % mod;
        else if (s[i] == 'a') a[i] = cb * (longs)pow3[c] % mod;
        else if (s[i] == '?') a[i] = cb, cb = (cb + b[i]) % mod, ++ c;
    longs ans = 0;    
    for (int i = 0; i < n; ++ i)
        if (s[i] == 'a' || s[i] == '?')
            ans = (ans + a[i]) % mod; 
    // cerr << "a = " << a[0];
    // for (int i = 1; i < n; ++ i)
    //     cerr << ", " << a[i];
    // cerr << endl << "b = " << b[0];
    // for (int i = 1; i < n; ++ i)
    //     cerr << ", " << b[i];    
    // cerr << endl;
    cout << ans << endl;

    return 0;
}

