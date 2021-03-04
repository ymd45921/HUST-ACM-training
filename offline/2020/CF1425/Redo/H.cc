/**
 *
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <bitset>

using namespace std;
using longs = long long;
using uint = unsigned;

#define nextInt nexT<int>
#define nextLongs nexT<longs>
#define next128 nexT<__int128>

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

const char yes[] = "Ya";
const char no[] = "Tidak";

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t = nextInt();
    bitset<4> res;
    int cnt[4];
    while (t --)
    {
        for (int i = 0; i < 4; ++ i)
            cnt[i] = nextInt();
        res.reset();  
        if (cnt[0] || cnt[3]) res[0] = res[3] = true;
        if (cnt[1] || cnt[2]) res[1] = res[2] = true;
        if (cnt[0] + cnt[1] & 1) res[2] = res[3] = false;
        else res[0] = res[1] = false;
        for (int i = 0; i < 4; ++ i)
            printf("%s ", res[i] ? yes : no);
        puts("");    
    }

    return 0;
}