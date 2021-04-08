#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
ll read()
{
    ll x = 0; char ch = getchar(); bool f = 1;
    for(; ch > '9' || ch < '0'; ch = getchar()) if(ch == '-') f = 0;
    for(; ch >= '0' && ch <= '9'; ch = getchar())x = (x<<1)+(x<<3)+(ch^48);
    return f? x : -x;
}

const int N = 1e5 + 2;
int n, d;
int a[N];
double f[N][10], g[N][10];
pair<int, int> pre[N][10];
vector<int> shift[10][10];

int main()
{
    for(int i = 0; i < 10; ++i)
        for(int j = 0; j < 10; ++j)
            for(int k = 0; k < 10; ++k)
                if(i * j % 10 == k)
                    shift[i][k].push_back(j);
    n = read(); d = read();
    for(int i = 1; i <= n; ++i) a[i] = read();
    g[1][a[1] % 10] = f[1][a[1] % 10] = log(a[1]);
    for(int i = 2; i <= n; ++i) {
        int digit = a[i] % 10;
        for(int j = 0; j < 10; ++j) {
            for (auto &sh : shift[digit][j]) {
                if(g[i][j] < f[i-1][sh] + log(a[i])) {
                    g[i][j] = f[i-1][sh] + log(a[i]);
                    pre[i][j] = pre[i-1][sh];
                }

            }
            if(f[i-1][j] < g[i][j]) {
                f[i][j] = g[i][j];
                pre[i][j] = pre[i-1][j];
            }
            else {
                f[i][j] = f[i-1][j];
                pre[i][j] = make_pair(i, )
            }
        }
    }
    return 0;
}