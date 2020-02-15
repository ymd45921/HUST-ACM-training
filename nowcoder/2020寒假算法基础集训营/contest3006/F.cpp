/**
 * 
 */
#include <iostream>

using namespace std;
typedef long long longs;
typedef long double longd;

const longs MOD = 1000000007ll;

int x,q,l,r;

int solution(int l,int r)
{
    longs ans = r-l+1;
    
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>x>>q)
    while(q--)
    {
        cin>>l>>r;
        cout<<solution(l,r)<<endl;
    }

    return 0;
}