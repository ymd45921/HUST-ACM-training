#include <iostream>

using namespace std;
typedef long long longs;

const int md[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

int s,e;

inline bool isLunar(const int y)
{
    if((y&1)||(y>>1&1)) return false;
    else if(y%100) return true;
    else if(y%400) return false;
    else return true;
}

inline bool isLegal(const int dt)
{
    int y = dt/10000;
    int m = dt/100%100;
    int d = dt%100;
    if(m<=0||m>12) return false;
    else if(m==2&&isLunar(y)) 
        if(d<=0||d>29) return false;
        else return true;
    else if(d<=0||d>md[m]) return false;
    else return true;
}

inline int buildInt(const int y)
{
    int ret = y*10000;
    int num[4];
    num[0] = y%10;
    num[1] = y%100/10;
    num[2] = y%1000/100;
    num[3] = y/1000;
    ret+=(num[0]*1000+num[1]*100+num[2]*10+num[3]);
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>s>>e)
    {
        const int y1 = s/10000;
        const int y2 = e/10000;
        int ans = 0;
        for(int i=y1;i<=y2;++i)
        {
            int nd = buildInt(i);
            if(nd<s||nd>e) continue;
            if(isLegal(nd)) ++ans;
        }
        cout<<ans<<endl;
    }

    return 0;
}