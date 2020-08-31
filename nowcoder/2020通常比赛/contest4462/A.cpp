/**
 * 
 * 对于map，查询就是新增默认值。
 * 这个题目需要擦除的
 *
 * 可以平衡树在线解决（题解）
 */
#include <bits/stdc++.h>
using namespace std;
const char sk[] = "skipped";
int main()
{
    int n,t,c;
    map<int,int> pool;
    string l;
    stringstream ss;

    cin>>n;
    while(n--)
    {
        l="";
        while(!l.length())getline(cin,l);
        ss.clear();
        ss.str(l);
        ss>>t;
        if(~t)
        {
            if(ss>>c)
            {
                auto it = pool.lower_bound(t-30);
                if(it==pool.end()||it->first>t+30)
                {
                    pool[t]+=c;
                }
            }
            else
            {
                cout<<pool[t]<<endl;
                if(!pool[t])pool.erase(t);
            }
        }
        else
        {
            if(pool.empty())cout<<sk<<endl;
            else
            {
                cout<<pool.begin()->second<<endl;
                pool.erase(pool.begin()->first);
            }
        }
    }
}