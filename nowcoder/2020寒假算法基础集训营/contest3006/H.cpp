/**
 *
 */
#include <iostream>

// #define mytest

#ifdef mytest
#include <cassert>
#include <cstring>
#include <algorithm>
void test();
#endif

using namespace std;
typedef long long longs;
typedef long double longd;

const int LEN = 6;
const int bit[6] = {26*26*26*26*26,26*26*26*26,26*26*26,26*26,26,1};

int mod;
char s[LEN+1]{0};
char o[LEN+1]{0};
int m[LEN];
int n[LEN];
int ans[6]{0};
int tmp[6]{0};

int* solution(int mod)
{
    // ans[0] = mod/bit[0];
    ans[0] = tmp[0] = 0;
    for(int i=1;i<LEN;++i)
    {
        tmp[i] = mod/bit[i];
        ans[i] = tmp[i] - tmp[i-1]*26;
    }
    return ans;
}

int Hash(char str[])
{
    int res = 0;
    for (int i = 0; i < LEN; i++)
    {
        res = (res * 26 + str[i] - 'a') % mod;
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

#ifdef mytest
    test();
#endif

    while(cin>>s[0])
    {
        m[0] = s[0] - 'a';
        for(int i=1;i<LEN;++i)
        {
            cin>>s[i];
            m[i] = s[i] - 'a';
        }
        cin>>mod;
        solution(mod);
        for(int i=LEN-1;i>0;--i)
        {
            n[i] = m[i]+ans[i];
            ans[i-1] += n[i]/26;
            n[i] %= 26;
        }
        n[0] = m[0] + ans[0];
        if(n[0]<26)
        {
            for(int i=0;i<LEN;++i)o[i]=(char)(n[i]+'a');
            cout<<o<<endl;
#ifdef mytest
        assert(Hash(s)==Hash(o));
        for(int i=0;i<mod;++i)
            next_permutation(s,s+LEN);
        cout<<"rearranged: "<<s<<endl;
//        assert(!strcmp(o,s));
        cout<<"Assertion Passed.\n"<<endl;
#endif
        }
        else cout<<-1<<endl;
    }

    return 0;
}

#ifdef mytest
void print(int a[])
{
    for(int i=0;i<LEN;++i)
        cout<<a[i]<<' ';
    cout<<endl;
}

void test()
{
    while(cin>>s[0])
    {
        m[0] = s[0] - 'a';
        for(int i=1;i<LEN;++i)
        {
            cin>>s[i];
            m[i] = s[i] - 'a';
        }
        cin>>mod;
        cout<<"字符串转化为26进制：";
        print(m);
        solution(mod);
        cout<<"模数转化为26进制：  ";
        print(ans);
        cout<<"上述两数相加结果：  ";
        for(int i=LEN-1;i>0;--i)
        {
            n[i] = m[i]+ans[i];
            ans[i-1] += n[i]/26;
            n[i] %= 26;
        }
        n[0] = m[0] + ans[0];
        print(n);
        cout<<"转化得到的字符串：";
        if(n[0]<26)
        {
            for(int i=0;i<LEN;++i)o[i]=(char)(n[i]+'a');
            cout<<o<<endl;
        }
        else cout<<-1<<endl;
    }
}
#endif