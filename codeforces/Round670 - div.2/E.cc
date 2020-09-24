/**
 *
 * 简单的想法是先处理质数再处理幂次
 * 但是因为有 9600 个素数所以 10000 次询问不够用
 *
 * 然后考虑到大于 √n 的质数最多 1 个（显然）
 * 所以小于 √n 的部分只能暴力搞定
 * 然后只需要在不爆炸的情况下找大于的部分就可以了
 *
 * 确认每一个质数需要两次询问，但是如果仅在有问题确认，
 * 就可以在绝大多数的情况下只询问一次，就很足够
 * 
 * 也许这就是分块吧：毕竟分块是优雅的暴力
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <vector>
#include <bitset>
#include <cmath>

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

template <int n> vector<int> &EulerSieve()
{
    static vector<int> prime;
    bitset<n> vis;
    for (int i = 2; i <= n; ++ i)
    {
        if (!vis[i]) prime.push_back(i);
        for (auto & pp : prime)
        {
            if ((longs)i * pp > n) break;
            vis[i * pp] = true;
            if (i % pp == 0) break;
        }
    }
    return prime;
}

const int N = 100000;

int askA(int x)
{
    int tmp;
    cout << "A " << x << endl;
    cin >> tmp;
    return tmp;
}

int askB(int x)
{
    int tmp;
    cout << "B " << x << endl;
    cin >> tmp;
    return tmp;
}

void askC(longs x)
{cout << "C " << x << endl;}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, sq; cin >> n;
    const int step = 100;
    auto &p = EulerSieve<N>();
    int size = p.size();
    sq = sqrt(n);
    longs ans = 1;
    for (int i = 0; i < step; ++ i)
    {
        if (ans * p[i] > n) break;
        int a = 1, pro = p[i];
        askB(p[i]);
        do a = askA(pro);
        while (a && (pro *= p[i]) <= n);
        ans *= pro / p[i];
    }
    if (ans == 1)
    {
        int now = askA(1);
        int lim = (size - 1) / step + 1;
        for (int i = 1; i <= lim; ++ i)
        {
            int bs = i * step, bd = min(size, bs + step);
            int del = 0;
            for (int j = bs; j < bd; ++ j)
                if (p[j] > n) break;
                else askB(p[j]), ++ del;
            if (!del) break;
            auto res = askA(1);
            if (now - res != del)
            {
                for (int k = bs; k < bd; ++ k)
                    if (askA(p[k])) {ans *= p[k]; break;}
                askC(ans);
                return 0;
            }
            else now = res;
        }
    }
    else for (int j = step; j < size && p[j] * ans <= n; ++ j)
        if (askB(p[j] * ans))
        {
            askC(p[j] * ans);
            return 0;
        }
    askC(ans);
    return 0;
}