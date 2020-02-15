/**
 * 
 */
#include <iostream>

using namespace std;
typedef long long longs;
typedef long double longd;

int n,sum;
int in[100010];
longd avr;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        sum = 0;
        for(int i=0;i<n;++i)
        {
            cin>>in[i];
            sum += in[i];
        }
        avr = (longd)sum / (longd)n;
    }

    return 0;
}