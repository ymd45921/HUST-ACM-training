#include <iostream>

using namespace std;

int n,len,m;
int in[10000010];
bool _next[10000010];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    len = n;
    for(int i=1,cur=2;i<=n;++i,++cur)
    {
        cin>>in[i];
        _next[i] = cur;
    }
    _next[n-1]=_next[0]=0;
    cin>>m;
    in[0]=-m;
    int head = 1;
    int cur = head;
    while(_next[cur])
    if(in[_next[cur]]==m)
    {
        _next[cur]=_next[_next[cur]];
        --len;
    }
    else
    {
        cur = _next[cur];
    }
    
    if(in[head]==m)
    {
        head = _next[head];
        --len;
    }

    cout<<n;
    for(int i=1;i<=n;++i)cout<<in[i]<<' ';
    cout<<endl;
    cout<<len;
    cur = head;
    while(_next[cur])
    {
        cout<<in[cur]<<' ';
        cur = _next[cur];
    }
    cout<<in[cur]<<endl;
    return 0;
}