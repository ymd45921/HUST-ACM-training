/**
 * 
 * 一个很简单很基础的问题：
 * 求长度为 n 的，所有的 i != a[i] 的排列 a 的数量
 * 对于 1e9 + 7 取模后输出结果
 * 
 * 这是一个经典的基于递归的双射证明的算法（？
 * !n = (n - 1) * (!(n - 1) + !(n - 2))
 * 
 * 可以有如下的的递推关系：
 * - 从原本的 a[i] = i 的排列中，取出一个位置 m；这里不管选择哪个都是等价的
 * - 再从剩下来的 n - 1 个正确的位置中，选择一个位置 k，放入 m；有 n - 1 种情况
 *   - 如果我们选择 m，那也就是交换了 m 和 k 的位置，那么这两个位置已经错排了
 *     还剩下 n - 2 个位置；那么，问题变成了规模变为 n - 2 的子问题
 *   - 如果选择 m 之外的位置，相当于 k 参加了剩下的规模为 n - 1 的错排
 *     因为如果不选择 m，那么在子问题中 k 就相当于是 m；毕竟错排至少出现两个
 * 综上所述，由加法规则和乘法规则可以得到上述的转移式子；
 * 如果对于这个式子进行整理，还可以继续移项：
 *   !n - n * !(n - 1) = - !(n - 1) + (n - 1) * !(n - 2)
 *   !n - n * !(n - 1) = - (!(n - 1) - (n - 1) * !(n - 2))
 *   令： f(n) = F(n) - nF(n - 1) = !n - n * !(n - 1)
 *     可得：  f(n) = -f(n - 1)
 *       继续展开：  f(n) = F(n) - nF(n - 1) = (-1)^n
 *         移项得：  F(n) = nF(n - 1) + (-1)^n              [*]
 * 对于这个新的递推公式 [*]，我们可以使用母函数方法或容斥原理求通项公式
 * 但是百度百科这个母函数方法我实在是看不懂…… 
 * - https://baike.baidu.com/item/%E9%94%99%E6%8E%92%E9%97%AE%E9%A2%98/3849290#2_2
 * 那么来点阳间证明：
 * - 我们首先假定 G(n) = F(n) / n!，那么 G(n) = G(n - 1) + (-1)^n / n!
 *     那么我们反复展开这个式子，并将等号两侧累加，就可以得到：
 *       G(n) - G(1) = Σ i:[2, n] (-1)^i / i!，其中 G(1) = 0 / 1 = 0
 *     综上所述，可以得到 F(n) = n!G(n) = n! * (Σ i:[2, n] (-1)^i / i!)
 *   进一步：F(n) = Σ i:[2, n] (-1)^i * n! / i! = Σ i:[0, n] (-1)^i * n! / i!
 *     即进行补项，将求和范围从 [2, n] 扩展到 [0, n]，值不变
 *   此时 F(n) = Σ k:[0, n] (-1)^n * nCr(n, k) * (n - k)!
 * - 就算使用一般的母函数展开式，也可以得到相同的结果：
 *   对于一般的生成函数递推式 f(n) = g(n) * f(n - 1) + h(n)
 *   暴力展开： f(n) = Π i:[1, n] g(i) * (f(0) + Σ i:[1, n] {h(i) / Π j:[1, i] g(j)})
 *   对于我们上面已经分析得到的递推式 F(n) = n * F(n - 1) + (-1)^n
 *     显然有 G(n) = n，H(n) = (-1)^n；代入暴力展开的通项公式中，可以得到：
 *       F(n) = n! * (F(1) + Σ i:[2, n] (-1)^i / i!)
 *     上式中 F(1) = 0；当然，也可以再展开 F(1) 得到 F(0)，就和上面的扩增项一样；
 *   显然，这和上面的一种方法求出的通项公式是完全一致的。
 * - 使用容斥原理呢？首先我们的总体思路就是在所有的 n! 种排列中移出不符合条件的情况；
 *   首先，我们假设保证有一个位置 k 满足 p[k] = k，那么一共剩下 n - 1 个位置：(n - 1)! * nCr(n, 1)
 *     但是这样，我们就将两个位置都正确的位置重算了一次，减去 (n - 2)! * nCr(n, 2)
 *   定义 Y(k, n) = (n - k)! * nCr(n, k)；这样推算下去，我们一共要从 n! 中删除：
 *     Y(1, n) - Y(2, n) + Y(3, n) - Y(4, n) + ……
 *     从 n! 中减去就是： F(n) = n! + Σ i:[1, n] (-1)^i * Y(1, n)；
 *   展开表示就是 F(n) = Σ i:[0, n] (-1)^n * (n - i)! * nCr(n, i)；
 *   显然，这个公式也和前两种方法推导得到的公式一样；因此这就是错排数量的通项公式
 * 证明完了非常复杂的通项公式之后，再来点简化后的公式：
 * - 首先考虑 e^x 的泰勒展开（麦克劳林展开 / 幂级数展开）： Σ x^i / i! （x 在 0 的附近？？）
 *     可得：e^(-1) = Σ i:[0, n] (-1)^i / i! + Rn (= e^(-c)(c - 1)^n / (n + 1)!)
 *   所以可以近似认为： e^(-1) = D(n) / n! + Rn，且认为 n! / e - D(n) = n!Rn
 *   又因为 Rn = e^(-c)(c - 1)^n / (n + 1)! (c: [0, 1] | R)，c = 0 时取上界
 *     所以：|Rn| <= Rn(c = 0) = 1 / (n + 1)!，联立上式可得：
 *       |e^(-1) - D(n) / n!| = |Rn| <=  n! / (n + 1)! = 1 / n + 1
 *     而对于可行域 n >= 1 而言，余项上界 1 / n + 1 总是小于等于 1 / 2
 *   所以 D(n) 和最接近 n! / e 的整数可被认为相同，可以写成 D(n) = floor(n! / e + 0.5)
 * 综上所述，我们得到了简化后的通项公式： D(n) = floor(n! / e + 0.5)
 * ======================================================================================
 * 
 * 至此，我们对于错排公式相关的讨论就完成了。
 */
#include <bits/stdc++.h>

struct {
    template <class token>
    auto &operator,(token &x) { return std::cin >> x, *this; }
} input;

struct {
    auto &operator,(std::ostream &(*x)(std::ostream &)) { return std::cout << x, *this; }
    template <class token>
    auto &operator,(token &x) { return std::cout << x, *this; }
    template <class token>
    auto &operator,(token &&x) { return std::cout << x, *this; }
} output;

using namespace std;

using longs = long long;

const auto null = nullptr;

const int mod = 1e9 + 7;
const int N = 1e6 + 5;
int ans[N];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(null), cout.tie(null);

    int n; input, n;
    ans[0] = ans[2] = 1, ans[1] = 0;
    for (longs i = 3; i <= n; ++ i)
        ans[i] = int((ans[i - 1] + ans[i - 2])
                        % mod * (i - 1) % mod);
    output, ans[n], endl;

    return 0;
}