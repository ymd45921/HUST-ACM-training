/**
 *
 *
 */
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;
typedef long long longs;
typedef long double longd;

const int N = 2e6+5;
const int inf = 0x7fffffff;
const longs INF = 0x7fffffffffffffff;
const double eps = 1e-8;

longs ans[N];

void brute(int n = N-1)
{
    ans[0] = 0;
    auto f = [](longs ii) -> bool
    {
        longs vv = ii*ii+1;
        longs xx = vv % (ii+1);
        return xx;
    };
    for (longs i = 1; i < n; ++ i)
        ans[i] = ans[i-1] + f(i);
}


longs query(int ii)
{
    if (!ii) return 0;
    else return ii - 1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

//    brute();
//    system("pause");

    int t, n[1050];
    int maxx = 0;
    cin >> t;
    for (int i = 1; i <= t; ++ i)
    {
        cin >> n[i];
        cout << query(n[i]) << endl;
    }

    return 0;
}