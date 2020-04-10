/**
 *
 * 就这？暴力就能过？
 */
#include <iostream>
#include <algorithm>
#include <string>
#include <functional>
#include <cstring>
#include <map>

using namespace std;
typedef long long longs;
typedef long double longd;

const int N = 2e6+5;
const int inf = 0x7fffffff;
const longs INF = 0x7fffffffffffffff;
const double eps = 1e-8;

int max4(int a, int b, int c, int d)
{
    return max(a,max(b,max(c,d)));
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int na, nb, nc, nd, m;
    int x, y, p[13];
    for (int i = 0; i <= 12; ++ i)
        p[i] = i;
    function<int(int)> father = [&](int ii) -> int
    {
        if (p[ii] == ii) return ii;
        else return p[ii] = father(p[ii]);
    };
    auto join = [&](int x, int y)
    {
        int px = father(x),
            py = father(y);
        p[px] = py;
    };
    int num[13], cnt = 0, ans = 0;
    map<int,int> mm;

    function<int(int,int,int,int,int)> search =
        [&](int s, int a,int b, int c, int d) -> int
        {
            if (s == cnt) return 1;
            else if (num[s] > max4(a,b,c,d)) return 0;
            int ret = 0;
            if (a >= num[s]) ret += search(s+1,a-num[s],b,c,d);
            if (b >= num[s]) ret += search(s+1,a,b-num[s],c,d);
            if (c >= num[s]) ret += search(s+1,a,b,c-num[s],d);
            if (d >= num[s]) ret += search(s+1,a,b,c,d-num[s]);
            return ret;
        };

    cin >> na >> nb >> nc >> nd >> m;
    while (m --)
    {
        cin >> x >> y;
        join(x,y);
    }
    memset(num,0,sizeof num);
    for (int i = 1; i <= 12; ++ i)
    {
        if (!mm[father(i)])
            mm[p[i]] = ++cnt;
        ++ num[mm[p[i]]];
    }
    cout << search(1,na,nb,nc,nd) << endl;

//    int dp[13][13][13][13][13];
//    memset(dp, 0, sizeof dp);
//    int pre = 0;
//    for (int i = 1; i <= cnt; ++ i)
//    {
//        dp[]
//    }

    return 0;
}