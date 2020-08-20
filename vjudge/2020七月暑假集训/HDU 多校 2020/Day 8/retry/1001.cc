/**
 *
 * 简单题？语文题！
 * 对于序列的三种操作 Add，Delete，Replace；需要重写为仅使用 Replace 得到相同的目标串
 * 并且重写要求替换的字符数量最少，其次要求替换操作的次数最少
 *
 * 输出需要替换掉的字符数量和替换操作的次数，并且输出描述这些替换操作
 *
 * 更好的读入姿势原来就是 sstream 🐎
 */
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
using longs = long long;
using uint = unsigned;

const int N = 2060;
int a[N];

void read()
{
    stringstream ss;
    string s;
    vector<int> arr;
    char op;
    int l, r, x;
    do getline(cin, s);
    while (!s.length());
    ss.str(s); ss >> op;
    if (op == 'A')
    {
        ss >> l;
        arr.clear();
        while (ss >> x) arr.push_back(x);
    }
    else if (op == 'R')
    {
        ss >> l >> r;
        arr.clear();
        while (ss >> x) arr.push_back(x);
    }
    else
    {
        ss >> l >> r;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t, n, q;
    cin >> t;
    while (t --)
    {
        cin >> n >> q;
        for (int i = 0; i < n; ++ i) cin >> a[i];

        while (q --)
        {
            read();

        }
    }


    return 0;
}