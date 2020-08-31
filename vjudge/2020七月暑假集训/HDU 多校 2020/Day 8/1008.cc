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

const int std2[] = {2, 3, 4, 5, 1, 5};
const int evens[][2] = {{4, 2}, {3, 1}, {2, 6}, {1, 5}, {6, 4}, {5, 3}};
const int even[][3] = {{4, 3, 1}, {3, 2, 6}, {2, 1, 5}, {1, 6, 4}, {6, 5, 3}, {5, 4, 2}};
const int sneve[][2] = {{2, 5}, {6, 4}, {5, 3}, {4, 2}, {3, 1}, {2, 6}};
const int neve[][3] = {{1, 6, 4}, {6, 5, 3}, {5, 4, 2}, {4, 3, 1}, {3, 2, 6}, {2, 1, 5}};
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
    int len = 4, reversed = 0;
    deque<int> ss;
    for (auto ii : std2) ss.push_back(ii);
    while (len <= goal)
    {
        const auto xx = len - 3;
        if (reversed)
        {
            ss.push_back(3);
            ss.push_back(2);
            ss.push_front(6);
            CountDown(ii, xx - 1)
                ss.push_front(sneve[0][0]),
                ss.push_front(sneve[0][1]);
            ss.push_front(neve[0][0]),
            ss.push_front(neve[0][1]),
            ss.push_front(neve[0][2]);
            for (int i = 1; i < 6; ++ i)
            {
                CountDown(ii, xx)
                    ss.push_front(sneve[i][0]),
                    ss.push_front(sneve[i][1]);
                ss.push_front(neve[i][0]),
                ss.push_front(neve[i][1]),
                ss.push_front(neve[i][2]);
            }
            ss.pop_front();
        }
        else
        {
            ss.push_front(3);
            ss.push_front(2);
            ss.push_back(6);
            CountDown(ii, xx - 1)
                ss.push_back(evens[0][0]),
                ss.push_back(evens[0][1]);
            ss.push_back(even[0][0]),
            ss.push_back(even[0][1]),
            ss.push_back(even[0][2]);
            for (int i = 1; i < 6; ++ i)
            {
                CountDown(ii, xx)
                    ss.push_back(evens[i][0]),
                    ss.push_back(evens[i][1]);
                ss.push_back(even[i][0]),
                ss.push_back(even[i][1]),
                ss.push_back(even[i][2]);
            }
            ss.pop_back();
        }
        len += 2;
        reversed = !reversed;
    }
    if (reversed) while (!ss.empty())
        s.push_back(ss.back() + '0'),
        ss.pop_back();
    else while (!ss.empty())
        s.push_back(ss.front() + '0'),
        ss.pop_front();
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