/**
 * '题目数据范围不大，可以用一些相对暴力的方法。
 * 
 * 其实这大约也是某种意义上的多层图？
 * 
 * BFS都能写炸，我哭了== 怎么还能段错误的
 * 
 * 能少麻烦点就少麻烦点。
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

const int N = 500+5;
const string ohno = "Oh no";

int n,m,p,k;
char map[N][N];
bool zmbmap[N][N][50];
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
    while(!q.empty())q.pop();
    vis[st.x][st.y][0] = 0;
    q.push({st,0});
    node n;coord c;
    int nt;

    while(q.size())
    {
        n = q.front(); q.pop();
        if(n.p.x==ed.x&&n.p.y==ed.y)
        {
            ans = vis[ed.x][ed.y][n.t];
            break;
        }
        nt = (n.t+1)%T;
        for(int i=0;i<4;++i)
        {
            c = n.p+mov[i];
            if(judge(c,nt)&&vis[c.x][c.y][nt]==-1)
            {
                vis[c.x][c.y][nt] = vis[n.p.x][n.p.y][n.t]+1;
                q.push({c,nt});
            }
        }
    }
    
    return ans;
}

inline int parseDir(string &s)
{
    switch(s[0])
    {
        case 'R':return 3;
        case 'U':return 0;
        case 'L':return 2;
        case 'D':return 1;
        default:exit(-1);break;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n>>m>>p>>k)
    {
        memset(zmbmap,0,sizeof(zmbmap));
        memset(vis,-1,sizeof(vis));
        T = 2 * k - 2;

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
            int dir = parseDir(instr);
            for(int x=1,j=2*k-3;x<k;++x,--j)
            {
                inpos = inpos+mov[dir];
                zmbmap[inpos.x][inpos.y][x] = zmbmap[inpos.x][inpos.y][j] = true;
            }
        }

        int res = bfs();
        if(~res)cout<<res<<endl;
        else cout<<ohno<<endl;
    }

    return 0;
}

coord coord::operator+(const coord& rhs)
{
    return {x+rhs.x,y+rhs.y};
}