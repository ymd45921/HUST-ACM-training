/**
 * 
 * 这个也不会……………………爷麻了== 
 * 
 */
#include <iostream>
#include <iomanip>

using namespace std;
typedef long long longs;
typedef long double longd;

int n,sum,ss;
int in[100010];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout<<fixed<<setprecision(2);

    while(cin>>n)
    {
        ss = sum = 0;
        for(int i=0;i<n;++i)
        {
            cin>>in[i];
            sum += in[i];
            ss += in[i]-90;
        }
        cout<<(longd)ss/(9.0l*n+ss)*100.0l<<'%'<<endl;
    }

    return 0;
}