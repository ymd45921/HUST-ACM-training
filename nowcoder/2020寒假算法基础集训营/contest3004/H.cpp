/**
 * 
 */
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
typedef long long longs;
typedef long double longd;

int n,m,k;
int cnt[100010];
int arr[100010];
bool is[100010];
vector<longs> prime;
longs tmp;

inline void preProcess(int n)
{
    memset(arr,0,sizeof(int)*(n+5));
    memset(cnt,0,sizeof(int)*(n+5));
    memset(is,0,sizeof(bool)*(n+5));
    prime.clear();
    for(int i=2;i<=n;++i)
    {
        if(!is[i])
        {
            prime.push_back(i);
            for(auto num : prime)
            {
                tmp = num*i;
                if(tmp>n) break;
                is[tmp] = true;
                if(i%num==0)break;
            }
        }
        else 
        {
            ++cnt[++arr[i]];
            for(int j=1;(tmp=j*i)<=n;++j)
            {
                is[tmp] = true;
                ++arr[tmp];
            }
        }
    }
}

inline int query(int k)
{
    return cnt[k];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n>>m)
    {
        preProcess(n);
        while(m--)
        {
            cin>>k;
            cout<<query(k)<<endl;
        }
    }

    return 0;
}