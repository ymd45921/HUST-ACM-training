/**
 *
 * 瞎几把碰也失败了
 */
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <cstring>

using namespace std;
typedef long long longs;
typedef long double longd;

const int N = 2e5+5;
const int inf = 0x7fffffff;
const longs INF = 0x7fffffffffffffff;
const double eps = 1e-8;

int n, k;
string s;

namespace KMP
{
    int Next[1000010];
    int length;

    inline void buildNextArray()
    {
        Next[0] = -1;
        int i = 0, j = -1;
        length = s.length();
        while(i < length)
        {
            if(-1 == j || s[i] == s[j])
                Next[++ i] = ++ j;
            else j = Next[j];
        }
    }

    inline void printNextArray()
    {
        cerr << "[";
        for (int i = 0; i < length-1; ++ i)
            cerr << Next[i] << ", ";
        cerr << Next[length-1] << "]\n";
    }

    int cnt[N];

    int solve(int k)
    {
        buildNextArray();
        memset(cnt, 0, sizeof(int)*(length+1));
        for (int i = 1; i < length; ++ i)
            if(s[Next[i]] == s[i]) ++ cnt[Next[i]];
        int maxx = 0, kk = k-1;
        for (int i = 1; i < length; ++ i)
            if (cnt[i] >= kk) maxx = i;
        return maxx + 1;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> s;
//    KMP::buildNextArray();
//    KMP::printNextArray();
//    system("pause");

    cout << KMP::solve(k) << endl;

    return 0;
}
