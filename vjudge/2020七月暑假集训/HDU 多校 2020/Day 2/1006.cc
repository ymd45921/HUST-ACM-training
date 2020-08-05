/**
 *
 * 最不像签到题的签到题（
 *
 * 我愿称之为绝活，看到 FFT 我就认定我不会做然后没看了
 * 没想到这竟然是他妈的暴力==
 *
 * 首先你需要知道任何正整数可以被拆分成不同的斐波拉契数字之和
 * 当然，用屌想也知道这样子的拆分并不是唯一的（
 * 也就是说，可以使用 01 字符串来表示任何正整数的斐波拉契拆分
 *
 * 题目会将 C = A*B 修改一个位（必定 1 -> 0），求出该位
 * 也就是说会减少一个斐波拉契数
 * 因为数字很大所以要考虑模意义下的计算，保证斐波拉契数字互不同余
 * 然而和字符串哈希一样，ulongs 的 2^64 就可以满足这个要求（斐波拉契数列 2e6 位）
 * 所以这样就可以暴力计算：1e4 组数据，每一次计算是 2e6 的
 *
 * 有一个比这个难的变式题：LOJ-3219；可以去看看==
 * 
 * WA：因为有大量的溢出，所以实际上 fib 并不是一个递增数列，所以说只能遍历去找
 * 所有出现取模意义或者说是整形溢出的情况下都可能出现这样的问题；
 */
#include <iostream>
#include <cstdio>
#include <cctype>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;

inline int nextInt()
{
    int x = 0, f = 1, ch = getchar();
    while (!isdigit(ch)) if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

const int N = 2e6 + 5;
ulongs fib[N] = {1, 1, 2};
auto preFib = []{for (int i = 3; i < N; ++ i) fib[i] = fib[i - 1] + fib[i - 2];};

inline ulongs nextFib()
{
    ulongs ret = 0;
    int len = nextInt();
    for (int i = 1; i <= len; ++ i)
        nextInt() && (ret += fib[i]);
    return ret;
}

int main()
{
    preFib();
    int t = nextInt();
    while (t --)
    {
        auto a = nextFib(), b = nextFib(), c = a * b;
        auto cc = nextFib(), d = c - cc;
        int ptr = 1;
        while (d != fib[ptr]) ++ ptr;
        cout << ptr << endl;
    }
    return 0;
}