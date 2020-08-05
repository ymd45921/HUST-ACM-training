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
    int x = 0, f = 1, ch = getchar();
    while (!isdigit(ch)) if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

const int N = 50050;
struct robot
{
    longs p, a;

    friend istream &operator >>(istream &is, robot &obj)
    { return is >> obj.p >> obj.a; }
    bool operator <(const robot &rhs) const
    { return p == rhs.p ? a > rhs.a : p > rhs.p; }
    bool operator ==(const robot &rhs) const
    { return p == rhs.p && a == rhs.a; }
} rb[N];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    uint t, n;
    cin >> t;
    while (t --)
    {
        cin >> n;
        for (uint i = 0; i < n; ++ i)
            cin >> rb[i];
        sort(rb, rb + n);
        for (int i = 0, j = 0; i < n; ++ i)
        {
            while (rb[i] == rb[j]) ++ i;  
            
        }
        
    }

    return 0;
}