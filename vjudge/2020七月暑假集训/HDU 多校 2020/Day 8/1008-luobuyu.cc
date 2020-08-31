/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <deque>
#include <cassert>
#include <cstring>

#define CountDown(I, T) for (auto I = T; I; -- I)

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

const char ss2[] = "262345";
const char evens[][3] = {"51", "62", "13", "24", "35", "46"};
const char even[][4] = {"562", "613", "124", "235", "346", "451"};
const char ss3[] = "231342453564612654";
const char num[][2] = {"0", "1", "2", "3", "4", "5", "6"};
const char odds[][3] = {"42", "31", "26", "15", "64", "53"};
const char odd[][4] = {"431", "326", "215", "164", "653", "542"};

void constructOdd(int goal, string &s)
{
    int len = 5;
    s = ss3;
    while (len <= goal)
    {
        s.append(num[5]);
        const auto xx = len - 3;
        for (int i = 0; i < 6; ++ i)
        {
            CountDown(ii, xx) s.append(odds[i]);
            s.append(odd[i]);
        }
        s.pop_back(), len += 2;
    }
}

void constructEven(int goal, string &s)
{
    int len = 4;
    s = ss2;
    while (len <= goal)
    {
        s.push_back('4');
        const auto xx = len - 3;
        for (int i = 0; i < 6; ++ i)
        {
            CountDown(ii, xx) s.append(evens[i]);
            s.append(even[i]);
        }
        s.pop_back(), len += 2;
    }
}

int main()
{
    ios::sync_with_stdio(false);

    int t = nextInt();
    while (t --)
    {
        int n = nextInt();
        string s;
        if (n % 2) constructOdd(n, s);
        else constructEven(n, s);
        assert(s.length() == (3 * n - 1) * n - (2 * n - 1) - 1);
        puts(s.c_str());
    }

    return 0;
}