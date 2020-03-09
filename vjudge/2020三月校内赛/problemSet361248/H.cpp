/**
 * 我哪里有问题啊草
 * 
 * …………
 */
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;
typedef long long longs;

char s1[65],s2[65];

longs gray(int n, char* str)
{
    if(n==1) return str[0]-'0';
    if(str[0]=='1')
    {
        longs ans = (1<<n)-1;
        return ans - gray(n-1,str+1);
    }
    else
    {
        return gray(n-1,str+1);
    }
}

longs process(longs x)
{
    longs tmp = x;
    longs xx = x;
    while(xx>>=1) tmp^=xx;
    return tmp;
}

longs turn(char* s, int n)
{
    longs ret = 0;
    for(int i=0;i<n;++i)
        if(s[i]=='1')
        ret += 1ll<<(n-i-1);
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin>>n;

    for(int i=0;i<n;++i)
        cin>>s1[i];
    for(int i=0;i<n;++i)
        cin>>s2[i];
    s1[n] = s2[n] = 0;
    longs v1 = turn(s1,n);
    longs v2 = turn(s2,n);

    cout<< abs(process(v2)-process(v1))-1 <<endl;

    return 0;
}