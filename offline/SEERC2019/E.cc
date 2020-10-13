/**
 *
 * 必然是要先按年龄排序；然后将所有的村民划分为司机和乘客
 * 最优解必然是 C 人开车，M = n - Ck 人骑车
 * 
 * 因为存在申必的续命膜法，所以不管是什么人都可以贡献自己的生命
 * 对于司机，可以根据寿命分成两类：
 * - 自身寿命大于驾驶工具需要的寿命，还可以提供寿命给其他人
 * - 自身寿命小于驾驶工具所需的寿命，需要别人提供寿命
 * 对于村民，都可以提供 min(a - 1, d) 的寿命
 * 
 * 因为状况数量是有限的，所以可以枚举来求出最优解
 * 对于每种情况所需的费用，可以通过预处理而快速的求出
 * 对于每一种最优做法，一定是年龄最大的开车，次大的骑车
 * 
 * TODO: 一种神秘的双指针做法的博客，代码我还没有读：
 * https://blog.csdn.net/weixin_43918473/article/details/103102089
 * 
 * WA: (Accepted) 没有处理全部坐车的情况（可能有车坐不满）
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;
using longd = long double;

#define eprintf(x...) fprintf(stderr, x...)
#define var(x) ""#x" = " << x 
#define lll __int128
#define println(num) puts(to_string(num).c_str())

static class Scanner 
{
    template<class T>
    inline T read()
    {
        T x = 0; int f = 0, ch = getchar();
        while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
        return f ? -x : x;
    }

public:

    template <class T>
    void operator()(T &x){x = read<T>();}

    template <class T, class... Ts>
    void operator()(T &x, Ts &... y)
    {x = read<T>(), (*this)(y...);}

    int nextInt() {return read<int>();}
    longs nextLongs() {return read<longs>();}  
    lll nextInt128() {return read<lll>();}    
} scanner;

int n, k, lc, pc, lm, pm, t, d;
const int N = 1e5 + 5;
const longs inf = 0x3f3f3f3f3f3f3f3f;
int a[N];
longs ca[N], ma[N], ct[N], mt[N], su[N];

template <class T>
T $(const T *arr, int lClose, int rOpen)
{
    if (lClose >= rOpen) return (T)0;
    return arr[lClose] - arr[rOpen];
}



int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    scanner(n, k);
    scanner(lc, pc, lm, pm);
    scanner(t, d);
    for (int i = 1; i <= n; ++ i)
        a[i] = scanner.nextInt();
    sort(a + 1, a + 1 + n); 
    a[n + 1] = 0x3f3f3f3f;
    for (int i = n; i; -- i)
    {
        su[i] = su[i + 1] + min(d, a[i] - 1);
        ca[i] = ca[i + 1] + min(d, max(0, a[i] - lc));
        ma[i] = ma[i + 1] + min(d, max(0, a[i] - lm));
        ct[i] = ct[i + 1] + min(d, max(0, lc - a[i]));
        mt[i] = mt[i + 1] + min(d, max(0, lm - a[i]));
    }   
    longs cost = inf;
    const auto process = [&](longs c, longs m)
    {
        // passenger: [1, mm), rider: [mm, cc), driver: [cc, n]
        int cc = n + 1 - c, mm = cc - m;
        longs supply = $(ca, cc, n + 1) + $(su, 1, mm) + $(ma, mm, cc);
        longs need = $(ct, cc, n + 1) + $(mt, mm, cc);
        auto dd = min(supply, (longs)d);
        if (a[mm] + dd < lm || a[cc] + dd < lc) return;
        if (supply >= need) cost = min(cost, need * t + c * pc + m * pm);
    };
    for (longs c = 0; c * k <= n; ++ c)
    {
        const longs m = n - c * k;
        process(c, m);
    }
    process(n / k + bool(n % k), 0);
    if (cost == inf) cost = -1;
    println(cost);

    return 0;
}

