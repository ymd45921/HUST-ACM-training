#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>

#define vi vertex[i]

using namespace std;
typedef long long longs;
typedef long double longd;

struct point{int x,y;};

int n,x,y;
point vertex[100050];

longd distance(longd xpos)          // 这里也用longd就能AC了
{
    longd tmp = 0.0l;
    longd x2,y2;
    for(int i=1;i<=n;++i)
    {
        y2 = vi.y*vi.y;
        x2 = (vi.x-xpos)*(vi.x-xpos);
        tmp = max(tmp,sqrtl(x2+y2));
    }
    return tmp;
}

longd triple_search(longd left, longd right)
{
    longd midl,midr;
    for(int i=0;i<=100;++i)     // 因为浮点，所以只能通过搜索次数提高精度
    {
        midl = left + (right-left)/3;
        midr = left + 2*(right-left)/3;
        if(distance(midl)>distance(midr))
            left = midl;
        else right = midr;
    }
    return midl;
}

longd binary_search(longd left, longd right)
{
    longd mid;
    for(int i=0;i<=100;++i)
    {
        mid = (left+right)/2;
        if()
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout<<fixed<<setprecision(4);

    while(cin>>n)
    {
        for(int i=1;i<=n;++i)
        {
            cin>>x>>y;
            vertex[i] = {x,y};
        }
        cout<<distance(triple_search(-10000,10000))<<endl;
    }

    return 0;
}