/**
 * 
 */
#include <iostream>
#include <cmath>

using namespace std;
typedef long long longs;
typedef long double longd;

const longd root3 = 0.33333333333333333333333333333l;

int t,a,b;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>t)
    while(t--)
    {
        cin>>a>>b;
        longd cnt = 0;
        longd tmp;
        if(!a) cout<<abs(b)<<endl;
        else if(!b)
        {
            if(a<0)a=-a;
            longd now = a;
            while(now-(tmp=pow(now,root3))>1)
            {
                cnt+=1.0l;
                now = tmp;
            }
            cnt += now;
        }
        if((a>0&&b>0)||(a<0&&b<0))
        {
            a = abs(a);
            b = abs(b);
            if(b>a)cout<<(b-a)<<endl;
            longd now = a;
            while(now-(tmp=pow(now,root3))>1)
            {
                if(tmp-b>now-b)break;
                
            }
        }
    }

    return 0;
}