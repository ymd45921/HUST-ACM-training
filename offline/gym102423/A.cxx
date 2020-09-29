#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <string>
using namespace std;

typedef long long ll;
const int maxn = 35;
int a[maxn], ans[maxn], d[maxn];
int n;
char s[maxn];

void dfs(int now_digit){
    if( now_digit==n ){
        memset(d,0,sizeof(d));
        for(int j=0; j<now_digit; j++){
            for(int k=0; k<now_digit; k++){
                d[j+k]+=(ans[j]*ans[k]);
                d[j+k]%=10;
            }
        }

        for(int i=0;i<2*now_digit-1;i++){
            if( d[i]!=a[i] ) return ;
        }

        for(int i=0;i<n;i++){
            if( i==n-1 ) printf("%d\n",ans[n-1]);
            else printf("%d",ans[i]);
        }
        exit(0);
    }

    else{
        for(int i=0; i<=9; i++){///注意为什么从0开始记位,而不从1开始记位,
            ///因为从一开始(1+1)==2,算出来没有第1位了
            ans[now_digit] = i;
            memset(d,0,sizeof(d));
            for(int j=0; j<=now_digit; j++){
                for(int k=0; k<=now_digit; k++){
                    if( j+k>now_digit ) break;
                    d[j+k]+=(ans[j]*ans[k]);
                    d[j+k]%=10;
                }
            }

            int flag=0;
            for(int ii=0;ii<=now_digit;ii++){
                if( d[ii]!=a[ii] ) flag=1;
            }
            if( !flag ){///比较快,如果原来是flag==1,判flag==1,用了31ms,判!flag用了15ms
                dfs(now_digit+1);
            }
        }
    }
}

int main()
{
    scanf("%s",s);
    int len = strlen(s);

    for(int i=0;i<len;i++) a[i]=s[i]-'0';
    if( a[len-1]=='2' || a[len-1]=='3' || a[len-1]=='7' || a[len-1]=='8' ) printf("-1\n");///平方数的结果都不可能出现2,3,7,8
    else if( a[0]=='2' || a[0]=='3' || a[0]=='7' || a[0]=='8' ) printf("-1\n");
    else if( !len&1 ) printf("-1\n");///由于不进位,所以任何数的平方数的位数都为奇数
    else{
        n=(len+1)/2;
        dfs(0);
        printf("-1\n");
    }
    return 0;
}
