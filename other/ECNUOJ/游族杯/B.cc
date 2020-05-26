/**
 *
 * cao，是子序列，你妈的又读错题目了（
 *
 * 谜之 Runtime Error 到现在还没修好
 */
#include <iostream>
#include <functional>

#define ask cout << "? "
#define chk cout << "! "

using namespace std;
using longs = long long;

constexpr int inf = 0x3f3f3f3f;
constexpr double eps = 1e-8;

const int N = 1050;
using checker = function<bool(int)>;

unsigned binary(unsigned lb, unsigned rb, const checker& func)
{
    auto l = lb, r = rb;
    unsigned ret;
    while (l <= r)
    {
        auto mid = l + r >> 1u;
        if (func(mid)) ret = mid, l = mid + 1;
        else r = mid - 1;
    }
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    /**
     *
     * 第一阶段：测试数量，测试谁多谁少
     */
    int n, response; cin >> n;
    ask << string(n / 2 + 1, '0') << endl;
    cin >> response;
    int major = !response;
    char more = major ? '1' : '0';
    char less = major ? '0' : '1';
    unsigned majority, minority;
    minority = binary(0, n / 2 + 1, [&](int mid)
    {
        if (!mid) return true;
        ask << string(mid, less) << endl;
        cin >> response;
        return static_cast<bool>(response);
    });
    majority = n - minority;

    /**
     *
     * 第二阶段：向少数派中插入多数派数字
     */
    unsigned cnt[N], residue = majority;
    string ans;
    for (unsigned i = 0; i < minority; ++ i)
    {
        cnt[i] = binary(0, residue, [&](int mid)
        {
            ask << ans << string(mid, more) << string(minority - i, less) << endl;
            cin >> response;
            return static_cast<bool>(response);
        });
        ans.append(cnt[i], more).append(1, less);
        residue -= cnt[i]; if (!residue)
        {
            ans.append(minority - 1 - i, less);
            break;
        }
    }
    ans.append(residue, more);

    /**
     *
     * 第三部分：输出答案
     */
     chk << ans << endl;

    return 0;
}