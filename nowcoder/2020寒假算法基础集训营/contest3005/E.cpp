/**
 * 
 */
#include <iostream>
#include <string>
#include <cstring>

using namespace std;
typedef long long longs;
typedef long double longd;

string in;
int cnt[11];

inline void solution()
{
    const int cnt_num = cnt[0]+cnt[1]+cnt[2]+cnt[3]+cnt[4]+cnt[5]+cnt[6]+cnt[7]+cnt[8]+cnt[9];
    const int lon_num = cnt_num % (cnt[10]+1);
    const int sho_num = cnt[10]+1 - lon_num;
    const int sho_len = cnt_num / (cnt[10]+1);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>in)
    {
        memset(cnt,0,sizeof(cnt));
        for(auto ch : in)
        if(ch=='+')++cnt[10];
        else ++cnt[ch-'0'];
        solution();
    }

    return 0;
}