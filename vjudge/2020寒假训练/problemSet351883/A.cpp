/**
 * 唔……我怎么感觉这个只要按照顺序连怎么都不会有问题啊……
 * 
 * 行，答案绝对不是一个算式 return !(sumD-2*(n-1)) 就能是算出来的
 */
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

const string response[] = {"NO","YES"};
int n,D[1050],child[1050];
int sumD = 0;

inline bool solution()
{
    // return !(sumD-2*(n-1))
    int ans = child[1];
    for(int i=2;i<=n;++i)
    {
        ans+=(child[i]-1);
        if(i-n&&!ans)return false;
    }
    return !ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;++i)
    {
        cin>>D[i];
        child[i]=D[i]-1;
        sumD+=D[i];
    }
    ++child[1];

    cout<<response[solution()];
    return 0;
}