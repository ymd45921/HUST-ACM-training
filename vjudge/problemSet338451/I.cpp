#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
using namespace std;
const int maxn = 800000 + 10;
struct Node{
    int s,t;
    bool operator < (const Node & rhs) const {
        return s < rhs.s;
    }
}p[maxn];
priority_queue<Node>q;
bool cmp(const Node &lhs,const Node & rhs){
    return lhs.t < rhs.t || (lhs.t == rhs.t && lhs.s < rhs.s);
}
int solve(int n){
    while(!q.empty())q.pop();
    int cur = 0;
    for (int i = 0; i < n; ++i){
        if (cur + p[i].s <= p[i].t){
            q.push(p[i]);
            cur += p[i].s;
        }else {
            if (q.empty())continue;
            Node u = q.top();
            if (u.s > p[i].s){
                cur = cur - u.s + p[i].s;
                q.pop();
                q.push(p[i]);
            }
        }
 
    }

    return q.size();
}
int main(){

    int n;
    scanf("%d",&n);
    for (int i = 0; i < n ; ++i){
        scanf("%d%d",&p[i].s,&p[i].t);
    }
    sort(p,p+n,cmp);
    printf("%d\n",solve(n));
 
    return 0;
}
