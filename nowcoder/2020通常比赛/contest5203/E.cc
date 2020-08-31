/**
 *
 * T了还行
 * 这是什么规律题
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <functional>

using namespace std;
using longs = long long;
using longd = long double;
using ulongs = unsigned long long;

const int inf = 0x3f3f3f3f;
const int mod = 1e9+7;
const longs INF = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-8;

const longs ffib[] =
        {
                0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987,
                1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393,
                196418, 317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887,
                9227465, 14930352, 24157817, 39088169, 63245986, 102334155, 165580141,
                267914296, 433494437, 701408733, 1134903170, 1836311903, 2971215073,
                4807526976, 7778742049, 12586269025, 20365011074, 32951280099, 53316291173,
                86267571272, 139583862445, 225851433717, 365435296162, 591286729879,
                956722026041, 1548008755920, 2504730781961, 4052739537881, 6557470319842,
                10610209857723, 17167680177565, 27777890035288, 44945570212853, 72723460248141,
                117669030460994, 190392490709135, 308061521170129, 498454011879264,
                806515533049393, 1304969544928657, 2111485077978050, 3416454622906707,
                5527939700884757, 8944394323791464, 14472334024676221, 23416728348467685,
                37889062373143906, 61305790721611591, 99194853094755497, 160500643816367088,
                259695496911122585, 420196140727489673, 679891637638612258,
                1100087778366101931, 1779979416004714189, 2880067194370816120,
                4660046610375530309, 7540113804746346429
        };
const longs nqueen[] =
        {
                0,
                1, 0, 0, 2, 10,
                4, 40, 92, 352, 724,
                2680, 14200, 73712, 365596, 2279184,
                14772512ll, 95815104ll, 666090624ll, 4968057848ll, 39029188884ll,
                314666222712ll, 2691008701644ll, 24233937684440ll, 227514171973736ll, 2207893435808352ll
        };
const int prime[] =
        {
                1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 47,
                53, 59, 61, 67, 71, 73, 79, 83, 89, 97
        };
#define FIB ffib, ffib+93
#ifndef FIB
longs fib[100];
longs fillfib(int lim = 93)
{
    fib[0] = 0; fib[1] = 1;
    for (int i = 2; i < lim; ++ i)
        fib[i] = fib[i-1] + fib[i-2];
    cout << '{';
    for (int i = 0; i < lim; ++ i)
        cout << fib[i] << ", ";
    cout << '}' << endl;
    return fib[lim-1];
}
#endif

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    longs x, ans;
    int m;

//    ans = 1;
//    for (int i = 1; i <= 30; ++ i)
//    {
//        ans *= i;
//        cerr << i << " : " << (ans%=100000000) << endl;
//    }

    auto brutefact = [&]
    {
        longs fact = 1, xx = x;
        ans = 0;
        while (xx)
        {
            fact *= xx;
            -- xx;
            while (fact % m == 0)
                fact = fact / m, ++ ans;
        }
    };

    function<longs(longs)> solvezero = [&](longs n)
    {
        longs ret = 0;
        int xx = sqrt(m);
        for (int i = 25; i; -- i)
        {
            if (prime[i] < xx) break;
            if (m % prime[i]) continue;
            else
            {
                longs k = n / prime[i];
                ans += k + solvezero(k);
            }
        }
        return ans = ret;
    };

    auto solvequeen = [&]
    {
        longs z = x % min(13, m) + 1;
        ans = nqueen[z];
    };

    cin >> x >> m;
    auto ll = lower_bound(FIB, x);
    auto rr = upper_bound(FIB, x);
    cerr << (brutefact(), ans) << endl;
    if (rr - ll == 1) solvezero(x);
    else solvequeen();
    cout << ans << endl;

    return 0;
}