/**
 * 这个样例是怎么算出来的？
 * 
 * 我日还真能17s过，草（）
 * 比起最快的当跑腿员，可以让次快的多跑几次以节约次慢的时间。
 * 具体什么规律……也许可以直接比较把==
 * 
 * Presentation Error还行我日
 */
#include <iostream>
#include <algorithm>

using namespace std;

int t,n,ans,cnt;
int time[1050];

int solution()
{
    int case1,case2;
    if(cnt>4)
    {
        int cn = cnt-1;
        case1 = 2*time[1]+time[cn]+time[cnt];
        case2 = 2*time[2]+time[1]+time[cnt];
        cnt -= 2;
        return min(case1,case2)+solution();
    }
    switch(cnt)
    {
    case 1:return time[1];
    case 2:return time[2];
    case 3:return time[1]+time[2]+time[3];
    case 4:
        case1 = 2*time[1]+time[2]+time[3]+time[4];
        case2 = 3*time[2]+time[1]+time[4];
        return min(case1,case2);
    default:return 0;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>t;
    while(t--)
    {
        cin>>n;
        for(int i=1;i<=n;++i)
        cin>>time[i];
        sort(time+1,time+n+1);
        ans=0;
        cnt=n;
        cout<<solution()<<endl;
    }

    return 0;
}