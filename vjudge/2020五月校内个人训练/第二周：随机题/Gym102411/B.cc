/**
 *
 * 看懂了题目真的就没东西了……
 * 710 这个数字是抄的 hjl 巨佬的代码，不如问问是怎么构造的
 *
 * 不知道了，自己看吧测试吧
 *
 */
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

void logger(int lb, int rb)
{
    static const long double pi = 3.1415926535897932384626;
    static const long double bd = pi / 2.0;
    static const long double dpi = 2.0 * pi;
    cerr << fixed << setprecision(9);
    long double last_raw = 0;
    for (int i = lb; i <= rb; ++ i)
    {
        auto integer = 710 * i;
        long double raw = integer;
        while (raw < -bd) raw += dpi;
        while (raw > bd) raw -= dpi;
        auto addition = raw + dpi;
        auto delta = raw - last_raw;
        cerr << 710 * i << "\t\t" << raw << "\t\t"
             << addition << "\t\t" << delta << endl;
        last_raw = raw;
    }
    cerr << (pi / 50000) << endl;
}

constexpr long double eps = 1e-4;
template <typename number>
int compareTo(number x) {return x < -eps ? -1 : x > eps;}
template <typename number>
int compareTo(number a, number b) {return compareTo(a-b);}

void tester()
{
    static const long double pi = 3.1415926535897932384626;
    static const long double dpi = 2.0 * pi;
    static const long double delta = pi / 70000.0;
    cerr << "delta: " << delta << endl;
    auto xx = delta; int cnt = 0;
    while (compareTo(xx + cnt * dpi, ceil(xx + cnt * dpi))) ++ cnt;
    cerr << "found: " << fixed << setprecision(9) << xx + cnt * dpi << endl;
}

namespace brute
{
    template <typename number>
    class comparable : binary_function<number, number, bool>
    {
        number eps = 1e-8;
        int compareTo(number x) const {return x < -eps ? -1 : x > eps;}

    public:
        explicit comparable(number eps) : eps(eps) {}
        int compareTo(number a, number b) const {return compareTo(a-b);}
        int operator()(number a, number b) const {return compareTo(a-b);}
    };

    long double calcDelta(long double precision, unsigned count)
    {
        static const long double pi = 3.1415926535897932384626;
        static const long double dpi = 2.0 * pi;
        comparable<long double> cmp(precision);
        const long double delta = pi / count;
        cerr << fixed << setprecision(10) << "delta: " << delta << endl;
        long double xx = delta, ans = xx; int cnt = 0;
        while (cmp(ans, ceil(ans))) ++ cnt, ans = xx + cnt * dpi;   // 不要在函数括号里给 ans 赋值：unsequenced modification and access to "ans"
        return cerr << "found: " << ans << endl, ans;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    logger(-100, 100);
    tester();

    int n; cin >> n;
    for (int i = 0; i < n; ++ i)
        cout << 710 * (i - 25000) << endl;


    return 0;
}