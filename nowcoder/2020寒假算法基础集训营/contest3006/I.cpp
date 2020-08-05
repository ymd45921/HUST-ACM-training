/**
 * 
 */
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
typedef long long longs;
typedef long double longd;

const char Yes[] = "Yes";
const char No[] = "No";
const int I = 9;

int n,m;
int a[20];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n>>m)
    {
        for(int i=1;i<=n;++i)cin>>a[i];
        int Ipass = a[I];
        if((double)Ipass/(double)m>=0.8)cout<<Yes<<endl;
        else
        {
            sort(a+1,a+1+n);
            if(Ipass>=a[n-2])cout<<Yes<<endl;
            else cout<<No<<endl;
        }
    }

    return 0;
}