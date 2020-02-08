/**
 * 
 */
#include <iostream>

using namespace std;
typedef long long longs;
typedef long double longd;

int n;
int v[200050];

int lowbit(int val)
{
    int ans = 1;
    while(!(val&1))
    {
        val >>= 1;
        ans <<= 1;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        for(int i=1;i<=n;++i)cin>>v[i];
        
    }

    return 0;
}