/*
 * 
 * 
 */
#include <iostream>

using namespace std;
const int maxInt = 1E5+50;
typedef long long longs;

int n;
longs a[maxInt];
bool hasZero = false;
longs ans = 0;
int minusOne = 0;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    for(int i=0;i<n;++i)
    {
        cin>>a[i];
        if(a[i]<0)
        {
            ++minusOne;
            ans+=(-1-a[i]);
        }
        else if(a[i]>0)
        {
            ans+=(a[i]-1);
        }
        else
        {
            hasZero = true;
            ++ans;
        }
    }
    if(((minusOne&1)&&hasZero) || !(minusOne&1))
        cout<<ans;
    else 
        cout<<ans+2;
    return 0;
}