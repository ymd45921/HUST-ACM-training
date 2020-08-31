
#include <stdio.h>
#include <ctype.h>

typedef long long longs;

inline longs nextLongs()
{
    int f = 0, ch = getchar(); longs x = 0;
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

int main()
{
    longs t, n;
    t = nextLongs();
    while (t --)
    {
        n = nextLongs();
        if (n == 1 || n == 24) printf("Fake news!\n");
        else printf("Nobody knows it better than me!\n");
    }
    return 0;
}