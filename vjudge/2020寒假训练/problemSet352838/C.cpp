/**
 * 
 * 语文题，看半天没看懂题面
 * 
 * 不用考虑进球数和失球数目
 * 不用考虑和具体队伍的对战
 */
#include <iostream>

using namespace std;

int n;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n&&n)
    {
        if(n==4)cout<<2<<endl;
        else if(n<4)cout<<1<<endl;
        else cout<<n<<endl;
    }

    return 0;
}