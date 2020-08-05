/**
 *
 */
#define USING_STDIO 0
#if USING_STDIO
#include <cstdio>
#else
#include <iostream>
#include <iomanip>
#endif

#include <algorithm>
#include <cstring>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;

using number = double;
int compareTo(number x) {return x < -eps ? -1 : x > eps;}
int compareTo(number a, number b) {return compareTo(a-b);}

#if USING_STDIO
inline int nextInt()
{
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
    return x*f;
}
#endif

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif

    double t[5], finale;
    cin >> t[0] >> t[1] >> t[2] >> t[3] >> finale;
    sort(t, t + 4);
    double best = (t[0] + t[1] + t[2]) / 3;
    double worst = (t[1] + t[2] + t[3]) / 3;
    if (compareTo(finale, worst) >= 0) cout << "infinite" << endl;
    else if (compareTo(finale, best) < 0) cout << "impossible" << endl;
    else
    {
        double xx = finale * 3 - t[1] - t[2];
        cout << fixed << setprecision(2) << xx << endl;
    }

    return 0;
}