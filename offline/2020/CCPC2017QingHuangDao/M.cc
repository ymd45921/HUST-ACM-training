/**
 *
 *
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
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
        int ch = getchar(), f = 0;
        while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
        x = f ? -x : x;
    }

    template <class T, class... Ts>
    inline void read(T &x, Ts &... y)
    {return read(x), read(y...);}
}


const int N = 110;
struct {int x, y;} p[N];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    using In::read;

    int t, n, R, r;
    longs x, y;
    read(t);
    while (t --)
    {
        read(n, R, r);
        if (R == r)
        {
            auto nn = n;
            while (nn --) read(x, y);
            printf("%d\n", n);
            for (int i = 1; i < n; ++ i)
                printf("%d ", i);
            printf("%d\n", n);
            continue;    
        }
        map<longs, vector<int>> m;
        int id = 1;
        longs xx = R - 2 * r;
        xx *= xx;
        while (n --)
        {
            read(x, y);
            auto rr = x * x + y * y;
            m[max(rr, xx)].push_back(id);
            ++ id; 
        }
        int siz = (*m.begin()).second.size();
        printf("%d\n", siz);
        auto &vec = (*m.begin()).second;
        printf("%d", vec[0]);
        for (int i = 1; i < siz; ++ i)
            printf(" %d", vec[i]);
        puts("");      
    }

    return 0;
}

