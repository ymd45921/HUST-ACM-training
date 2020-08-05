/**
 * 
 * WA就算了，怎么0%，而且不是因为longs
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;
typedef long long longs;

int a[405];
int b[405];
int n,m;
size_t s;

longs solve()
{
    memcpy(b,a,s);
    sort(b,b+n);
    priority_queue<int> q;
    longs ans = 0;
    int c = n-1;
    int chance = m - n;
    while(chance--)
    {
        if(q.empty())
        {
            q.push(b[c]>>1);
            q.push(b[c]-(b[c]>>1));
            -- c;
        }
        else if(q.top()>b[c])
        {
            int tmp = q.top();
            q.pop();
            q.push(tmp>>1);
            q.push(tmp-(tmp>>1));
        }
        else
        {
            q.push(b[c]>>1);
            q.push(b[c]-(b[c]>>1));
            -- c;
        }
    }
    while(c>=0)
    {
        ans += (longs)b[c]*b[c];
        -- c;
    }
    while(!q.empty())
    {
        longs hot = q.top();
        ans += hot*hot;
        q.pop();
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q,x,v;
    cin>>n>>m;
    s = sizeof(int)*(n);

    for(int i = 0; i < n; ++ i)
        cin>>a[i];
    cin>>q;
    while(q--)
    {
        cin>>x>>v;
        a[x] = v;
        cout<<solve()<<endl;
    }

    return 0;
}