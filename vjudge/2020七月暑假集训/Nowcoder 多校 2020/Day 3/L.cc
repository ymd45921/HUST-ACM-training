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

const int N = 2e5 + 5;
char s[N];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    cin >> s;
    for (int i = 0; i < 6; ++ i) s[i] = tolower(s[i]);
    auto ss = string(s);
    if (ss.length() >= 6 && ss.substr(0, 6) == "lovely") cout << "lovely" << endl;
    else cout << "ugly" << endl;

    return 0;
}