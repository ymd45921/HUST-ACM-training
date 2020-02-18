/**
 * '题目数据范围不大，可以用一些相对暴力的方法。
 * 
 * 其实这大约也是某种意义上的多层图？
 * 
 * BFS都能写炸，我哭了== 怎么还能段错误的
 */
#include <iostream>
#include <string>
#include <utility>
#include <cstring>
#include <queue>

using namespace std;
typedef long long longs;
typedef long double longd;
struct coord{int x,y;coord operator+(const coord& rhs);};
static const coord mov[4] = {{-1,0},{1,0},{0,-1},{0,1}};
struct node {coord p;int t;};

struct zombie
{
    enum{u,d,l,r} dir;
    coord pos[50];
    void preProcess(int k);
    zombie(coord& st,string& di);
    zombie(coord& st,string& di,int k);
    zombie(){};
};

const int N = 500+5;
const string ohno = "Oh no";
const string up = "UP";
const string down = "DOWN";
const string left = "LEFT";
const string right = "RIGHT";

int n,m,p,k;
char map[N][N];
bool zmbmap[N][N][50];
zombie zmb[55];
coord inpos,st,ed;
string instr;
int T;
int vis[N][N][20];
queue<node> q;

bool judge(coord pos,int now)
{
    if(pos.x<=0||pos.y<=0||pos.x>n||pos.y>m)return false;
    else if(map[pos.x][pos.y]=='&')return false;
    else if(zmbmap[pos.x][pos.y][now])return false;
    else return true;
}

inline int bfs()
{
    int ans = -1;
    while(q.size())q.pop();
    q.push({{st.x,st.y},0});
    vis[st.x][st.y][0] = 0;
    while(q.size())
    {
        node tmp = q.front();
        q.pop();
        if(tmp.p.x==ed.x&&tmp.p.y==ed.y)
        {
            ans = vis[tmp.p.x][tmp.p.y][tmp.t];
            break;
        }
        coord now; int tt = (tmp.t+1) % T;
        for(int i=0;i<4;++i)
        {
            now = tmp.p+mov[i];
            if(judge(now,tt)&&vis[now.x][now.y][tt]==-1)
            {
                vis[now.x][now.y][tt] = vis[tmp.p.x][tmp.p.y][tmp.t]+1;
                q.push({now,tt});
            }
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n>>m>>p>>k)
    {
        memset(zmbmap,0,sizeof(zmbmap));
        memset(vis,-1,sizeof(vis));
        for(int i=1;i<=n;++i)
            for(int j=1;j<=m;++j)
            {
                cin>>map[i][j];
                if(map[i][j]=='A') ed={i,j};
                else if(map[i][j]=='L') st={i,j};
            }
        for(int i=1;i<=p;++i)
        {
            cin>>inpos.x>>inpos.y;
            cin>>instr;
            zmbmap[inpos.x][inpos.y][0] = true;
            zmb[i] = zombie(inpos,instr);
        }
        T = 2 * k - 2;
        for(int i=1;i<=p;++i)
        {
            zmb[i].preProcess(k);
            for(int i=1; i < T; ++i)
                zmbmap[zmb[i].pos[i].x][zmb[i].pos[i].y][i] = true;
        }
        int res = bfs();
        if(~res)cout<<res<<endl;
        else cout<<ohno<<endl;
    }

    return 0;
}

void zombie::preProcess(int k)
{
    for(int i=1,j=2*k-3;i<k;++i,--j)
    {
        pos[i] = pos[i-1]+mov[dir];
        pos[j] = pos[i];
    }
}

zombie::zombie(coord& st,string& di)
{
    pos[0] = st;
    switch(di[0])
    {
        case 'U':dir=u;break;
        case 'D':dir=d;break;
        case 'L':dir=l;break;
        case 'R':dir=r;break;
        default:exit(-1);break;     // 不存在的地方就果断一点
    }
}

zombie::zombie(coord& st,string& di,int k)
{
    zombie(st,di);
    preProcess(k);
}

coord coord::operator+(const coord& rhs)
{
    return {x+rhs.x,y+rhs.y};
}