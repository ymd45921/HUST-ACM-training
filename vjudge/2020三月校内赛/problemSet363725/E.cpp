#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long longs;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("easy.in","r",stdin);
    freopen("easy.out","w",stdout);

    int n, k, p, t;
    int v[15][15], c[11], lim = 0;
    while (cin>>n>>k)
    {
        memset(c,0,sizeof c);
        memset(v,-1,sizeof v);
        vector<int> d;
        for (int i = 0; i < n; ++ i)
        {
            cin >> v[i][0];
            lim = max(lim, v[i][0]);
            for (int ii = 1; ii <= v[i][0]; ++ ii)
                cin >> v[i][ii];
        }
        for (int i = 1; i <= lim; ++i)
            for (int j = 0; j < n; ++ j)
                d.push_back(v[j][i]);
        int cnt = 0, sum = 0;
        for (int ii : d)
        {
            if (cnt == k || sum >= 50) break;
            if (ii == -1 && sum <= 50) break;
            if (sum <= ii)
                ++ cnt, sum += ii;
        }
        if (cnt < k) sum += (k - cnt) * 50;
        cout << sum << endl;
    }

    return 0;
}