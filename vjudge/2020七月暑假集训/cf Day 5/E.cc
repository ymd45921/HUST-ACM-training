/**
 *
 * 洛谷翻译有不周全之处：给的是排列的前面部分
 *
 * 判断不举：
 * - 前 k 个数字是否可以被栈排序
 * - 这个栈排序是严格递增 1 的，不行立马暴毙
 * 就这么多了，再多就不太对了
 *
 * 只要前面的可了，后面是有可操作空间的
 * 虽然不会证明，但是应该是这样子的（
 *
 * 构造字典序最大：
 * - n == 0 的时候可以直接降序
 *
 * 主要就是单调栈模拟，答案可以一遍搞出来
 * 这真的不是紫色题（
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>

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
int n, k, a[N];
vector<int> res;

bool solution()
{
    static stack<int> s;
    int need = 1, cur = k;
    for (int i = 0; i < k; ++ i)
        if (need == a[i])
        {
            res.push_back(a[i]);
            ++ need;
        }
        else if (s.empty() || s.top() > a[i])
            s.push(a[i]);
        else
        {
            while (!s.empty() && s.top() < a[i])
                if (s.top() == need)
                {
                    res.push_back(s.top());
                    s.pop();
                    ++ need;
                }
                else return false;
            s.push(a[i]);
        }
    while (!s.empty())
    {
        int m = s.top() - 1;
        while (m >= need) a[cur ++] = m --;
        need = s.top() + 1;
        s.pop();
    }
    int m = n;
    while (cur < n) a[cur ++] = m --;
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    cin >> n >> k;
    for (int i = 0; i < k; ++ i)
        cin >> a[i];
    bool state = solution();
    if (!state) cout << -1;
    else for (int i = 0; i < n; ++ i)
        cout << a[i] << ' ';
    cout << endl;

    return 0;
}