/**
 * 
 */
#include <iostream>

using namespace std;
typedef long long longs;
typedef long double longd;

const longs modl = 1e9 + 7;
const int modi = 1e9 + 7;

int n;
int p[2080];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        for(int i=1;i<=n;++i)
        {
            cin>>p[i];
        }
    }

    return 0;
}