/**
 * 题解：
 * 最大距离最小，很容易想到使用二分或者三分的方法去做
 * 据题解所说，这个题目比起二分三分更好做。
 * 但是说句实话，这个题目待求值没有明显的“单调”
 * 
 * 这个题目，取值是线性的，都是在x轴上，且有确定范围。
 * 虽然不知道怎么求具体点，但是知道点求值是确定时间的。
 * 这样就是满满的二分/三分的气息了。
 * 
 * 已经不太熟悉怎么三分了，需要复习。
 */
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

    // longd max=0;
    // for (int i=1;i<=n;i++)
    // {
    //     longd tmp=sqrtl(vi.y*vi.y+(vi.x-xpos)*(vi.x-xpos));
    //     if (tmp>max) max=tmp;
    // }
    // return max;
}

longd triple_search(longd left, longd right)
{
    longd midl,midr;
    // 因为不是整数，所以终点只能通过搜索次数提高精度
    // 题解给的标程也没有等距离三分
    for(int i=0;i<=100;++i)
    {
        midl = left + (right-left)/3;    // 通过率78%，将循环次数调高之后通过率28%
        midr = left + 2*(right-left)/3;
        // midl=left+(right-left)/2;           // 改成这样之后通过率提升到了92%？为啥？
        // midr=midl+(right-midl)/2;
        if(distance(midl)>distance(midr))
            left = midl;
        else right = midr;
    }
    return midl;

    // longd midl,midr;
    // for(int i=0;i<100;i++){
    //     midl=left+(right-left)/2;
    //     midr=midl+(right-midl)/2;
    //     if(distance(midl)>distance(midr)) //极大值求法
    //         left=midl;
    //     else
    //         right=midr;
    // }
    // return midl;
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