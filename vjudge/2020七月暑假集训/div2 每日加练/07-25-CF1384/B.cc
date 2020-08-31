/**
 *
 * 首先特判绝对不可达和安全点——任何时候都不会溺水的位置
 * 然后显然，肯定是退潮时出发更加安全：
 * 而且，显然不存在一种位置涨潮安全而退潮不安全的
 *
 * 接下来在每个安全点之间挪移：
 * - 当退潮的时候，等到下一个位置安全了再前进
 * - 如果下一个位置安全不了了，那显然没戏了：因为等不到下一个潮汐轮回了
 * - 如果是涨潮，那不用等尽快通过：如果下一个位置没戏那就是真的没戏了
 * - 毕竟涨潮的时候等在原地也是死，向前也是死（因为不是安全位置，没有轮回
 * 然后这个题就做出来了，本质上还是一个贪心题，DP 应该都不算的（
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <vector>
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

const int N = 3e5 + 10;
int d[N];
vector<int> pos;

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, k, l, t;
    cin >> t;
    while (t --)
    {
        cin >> n >> k >> l;
        bool pass = true;
        pos.clear(); pos.push_back(0);
        for (int i = 1; i <= n; ++ i)
            cin >> d[i], d[i] > l && (pass &= false),
            d[i] + k <= l && (pos.push_back(i), 0);
        pos.push_back(n + 1);
        if (!pass)
        {
            cout << "No" << endl;
            continue;
        }
        const auto safe = pos.size();
        for (int i = 1; i < safe; ++ i)
        {
            auto st = pos[i - 1], ed = pos[i];
            auto td = k, down = 1;
            for (int j = st + 1; j < ed; ++ j)
            {
                td += down ? -1 : 1;
                if (down) td -= max(0, d[j] + td - l);
                if (td < 0 || d[j] + td > l)
                {
                    pass &= false;
                    break;
                }
                if (!td) down = !down;
            }
        }
        cout << (pass ? "Yes" : "No") << endl;
    }

    return 0;
}