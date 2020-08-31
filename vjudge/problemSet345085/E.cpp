#include <iostream>
#include <algorithm>

#define max3(a,b,c) ((a>b)?(a>c?a:c):(b>c?b:c))
#define node(x) (elist[x].y)

using namespace std;
typedef int num;
typedef int hue;

struct edge {
    int x,y;
    bool operator<(const edge& rhs) const;
};

int n,x,y,ans = 0;
num total = 0;
edge elist[400050];
hue color[200050]{0};
num head[200050]{0};
num Next[400050]{0};
int cnt[200050]{0};

void addEdge(int x, int y)
{
    ++total;
    Next[total] = head[x];
    head[x] = total;
    elist[total].x = x;
    elist[total].y = y;
    ++cnt[x];
}

void dyeNode(num thisNode, num father)
{
    hue dying = 1;
    num cur = head[thisNode];
    for(;cur;cur=Next[cur])
    {
        while(dying==color[thisNode]||dying==color[father])
            ++dying;
        if(!color[node(cur)])
        {
            color[node(cur)] = dying;
            dyeNode(node(cur),thisNode);
            ++dying;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    int it = n;
    while(--it)
    {
        cin>>x>>y;
        addEdge(x,y);
        addEdge(y,x);
        ans = max3(ans,cnt[x],cnt[y]);
    }

    color[1] = 1;
    dyeNode(1,0);
    ++ans;

    cout<<ans<<endl;
    for(int i=1;i<=n;++i)
    cout<<color[i]<<' ';
    return 0;
}

bool edge::operator<(const edge& rhs) const
{
    if(x-rhs.x) return x<rhs.x;
    else return y<rhs.y;
}