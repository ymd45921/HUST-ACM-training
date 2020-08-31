#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long longs;

const char cannot[] = "impossible";

// 疯狂WA：这个写错了，为什么（）
//inline longs judge(longs i)
//{
//    longs in = i<<1;
//    longs sq = sqrtl(in);
//    while(sq*(sq-1)<i) ++sq;
//    if(sq*(sq-1)==in) return sq;
//    else return -1;
//}

inline longs judge(longs i)             // 求01个数
{
    longs i2 = i*2;
    longs sq = 0;
    while(++sq)
        if(sq*(sq-1)>=i2)
            break;
    if(sq*(sq-1)==i2) return sq;
    else return -1;
}

inline string build(longs a,longs b,longs c,longs d)
{
    if(!a&&!b&&!c&&!d) return "0";      // 特判全0
    longs n0 = judge(a);
    longs n1 = judge(d);
    if(n0!=-1&&n1!=-1)                  // 否则必定是假的
    {
        if(n0==1&&n1==1)                // 只有一个0一个1
        {
            if(b&&c) return "";
            else if(b==1) return "01";
            else if(c==1) return "10";
            else return "";
        }
        else if(n0==1) { if(!b&&!c) n0 = 0; }   // 返回1可能要请0
        else if(n1==1) { if(!b&&!c) n1 = 0; }
        if(n0*n1!=b+c)  return "";      // 易证数学关系
        else
        {
            string s;
            const auto lim = n0;
            while(n0--) s.push_back('0');       // 摆0
            longs left01 = b;                   // 剩下的01
            while(n1--)                         // 插1
            {
                longs pos = min(lim,left01);    // 贪心，尽可能向后插
                s.insert(pos,"1");
                left01 -= pos;                  
            }
            return s;
        }
    } else return "";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    longs a,b,c,d;
    while(cin>>a>>b>>c>>d)
    {
        string ans = build(a,b,c,d);
        if(!ans.empty()) cout<<ans<<endl;
        else cout<<cannot<<endl;
    }

    return 0;
}