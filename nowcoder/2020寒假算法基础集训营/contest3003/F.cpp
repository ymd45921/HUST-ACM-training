/**
 * 
 * 这个策略是真的迷惑……我觉得我能试的都试了啊==
 * 
 * 事啊题解说的我有想到啊（）
 * 
 * 日写代码的时候好像没有尝试这个
 */
#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <cstring>

#define val first 
#define num second

using namespace std;
typedef long long longs;
typedef long double longd;
typedef pair<int,int> item;

int n;
item li[200050];
int in;
vector<int> H,T;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        H.clear(); T.clear();

        for(int i=1;i<=n;++i)
        {
            cin>>li[i].val;
            li[i].num = i;
        }
        for(int i=1;i<=n;++i)
        {
            cin>>in;
            li[i].val += in;
        }
        sort(li+1,li+1+n);

        for(int i=1;i<=n;++i)
        {
            if(i&1)
            {
                H.push_back(li[n+1-i].num);
            }
            else
            {
                T.push_back(li[n+1-i].num);
            }
        }

        for(int i:H)
            cout<<i<<' ';
        cout<<endl;
        for(int i:T)
            cout<<i<<' ';
        cout<<endl;  
    }

    return 0;
}