/**
 *
 * 连续 k 项和相等，那也就是说是循环节；
 * 如果已有种数超过 n，那只能去死了（
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <queue>
#include <vector>
#include <unordered_map>
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

const int N = 1060;
int a[N], r[N];
vector<int> ans;

int solution(int n, int k, queue<int> &que)
{
    static unordered_map<int, int> cnt;
    ans.clear(); cnt.clear();
    for (int i = 0; i < n; ++ i)
        ++ cnt[a[i]];
    if (cnt.size() > k) return -1;
    int ptr = 0, cur = 0;
    for (auto & ii : cnt) r[ptr ++] = ii.first;
    while (ptr < k) r[ptr ++] = r[0];
    while (!que.empty())
    {
        ans.push_back(r[cur]);
        if (r[cur] == que.front()) que.pop();
        cur = (cur + 1) % k;
    }
    return ans.size();
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t, n, k;
    queue<int> que;
    cin >> t; while (t --)
    {
        cin >> n >> k;
        while (!que.empty()) que.pop();
        for (int i = 0; i < n; ++ i)
            cin >> a[i], que.push(a[i]);
        auto xx = solution(n, k, que);
        cout << xx << endl;
        if (xx == -1) continue;
        for (auto & ii : ans) cout << ii << ' ';
        cout << endl;
    }

    return 0;
}