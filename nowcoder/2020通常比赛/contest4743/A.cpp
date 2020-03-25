#include <iostream>
#include <cstdio>
#include <string>

using namespace std;
typedef long long longs;

string s;
char xq[] = "XiaoQiao";
char xhh[] = "XiaoHuiHui";

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>s;
    auto x = s.find('X');
    if(x==string::npos) // 必须的
    {
        cout<<"emm";
        return 0;
    }
    int ca = 1, cb = 1;
    int lim = s.length();
    for (int i = x; i < lim; ++ i)
    {
        if(s[i]==xq[ca]) if(xq[ca]) ++ca;
        if(s[i]==xhh[cb]) if(xhh[cb]) ++cb;
    }

    if(xq[ca] || xhh[cb]) cout<<"emm";
    else cout<<"Happy";

    return 0;
}