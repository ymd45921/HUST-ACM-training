/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

const int N = 1e5 + 5;
int b[N];

int main()
{
    ios::sync_with_stdio(false);

    int t = nextInt();
    while (t --)
    {
        int n = nextInt(), q = nextInt();
        for (int i = 1; i <= n; ++ i)
            b[i] = nextInt();
        while (q --)
        {
            int op = nextInt();
            if (op == 1)
            {
                int x = nextInt(), y = nextInt();
                if (b[x] < y || b[x + 1] >= y) 
                {puts("0"); continue;}
                longs cnt = 0;
                auto xx = x;
                do cnt += b[xx --] - y + 1;
                while (xx > 0 && b[xx] >= y);
                if (!xx) {puts("0"); continue;}
                while (xx < x)
                {
                    b[xx] += b[xx + 1] - y + 1;
                    b[++ xx] = y - 1;
                }
                printf("%lld\n", cnt);
            }
            else
            {
                int x = nextInt();
                printf("%d\n", b[x]);
            }
        }
        for (int i = 1; i < n; ++ i)
            printf("%d ", b[i]);
        printf("%d\n", b[n]);
    }

    return 0;
}