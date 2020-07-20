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

template <class T> int sgn(T t)
{ return t ? (t > 0 ? 1 : -1) : t; }

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t, a, b, c, d;
    cin >> t;
    while (t --)
    {
        cin >> a >> b >> c >> d;
        auto cc = sgn(a - c);
        auto dd = sgn(b - d);
        if (cc > dd) cout << "AB//DC" << endl;
        else if (cc < dd) cout << "AB//CD" << endl;
        else
            if (cc > 0)
                if (a > b) cout << "AB//DC" << endl;
                else cout << "AB//CD" << endl;
            else
                if (c > d) cout << "AB//CD" << endl;
                else cout << "AB//DC" << endl;
    }


    return 0;
}