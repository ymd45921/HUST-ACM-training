/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <bitset>
#include <stack>
#include <algorithm>
#include <cstring>

#define log(x...) fprintf(stderr, x)

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

const int N = 105;
int a[N], tmp[N];
bitset<N> poRelation[N];

bool isFake(int n)
{
    auto last = 0;
    for (int i = 0; i < n; ++ i)
    {
        if (a[i] == -1) {++ last; continue;}
        if (!a[i] || a[i] - last > 1) return true;
        last = a[i];
    }
    return false;
}

int pCompareTo(int u, int v)
{
    if (poRelation[u][v]) return -1;
    else if (poRelation[v][u]) return 1;
    else return 0;
}

void poBuild(int n)
{
    for (int i = 0; i <= n; ++ i)
        poRelation[i].reset();
    static stack<int> mono;
    mono.push(0);
    int now = 2;
    for (int i = 1; i < n; ++ i)
    {
        auto to = now - tmp[i];
        while (to --> 0)
        {
            poRelation[i][mono.top()] = true;
            mono.pop(), -- now;
        }
        if (!mono.empty()) poRelation[mono.top()][i] = true;
        mono.push(i), ++ now;
    }
    for (int k = 0; k < n; ++ k)
        for (int i = 0; i < n; ++ i)
            for (int j = 0; j < n; ++ j)
                if (poRelation[i][k] && poRelation[k][j])
                    poRelation[i][j] = true;
}

int main()
{
    ios::sync_with_stdio(false);

    int t = nextInt();
    while (t --)
    {
        int n = nextInt();
        for (int i = 0; i < n; ++ i)
            tmp[i] = a[i] = nextInt();
        if (isFake(n)) puts("0");
        poBuild(n);

    }


    return 0;
}