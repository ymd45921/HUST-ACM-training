/**
 * 
 * 用了前缀和还是T了
 * 
 * 如果找到了每个最小的段，用来计算所有0段？
 */
#include <iostream>

using namespace std;
typedef long long longs;
typedef long double longd;

int n;
int in[200050]{0};
int pre[200050]{0};
int tmp,cnt;
int s,t;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        s=0;t=0;
        tmp = cnt = 0;
        for(int i=1;i<=n;++i)
        {
            cin>>in[i];
            pre[i] = pre[i-1]^in[i];
            for(int j=0;j<i;++j)
                if(!(pre[j]^pre[i]))++cnt;
        }
        cout<<cnt<<endl;
    }

    return 0;
}