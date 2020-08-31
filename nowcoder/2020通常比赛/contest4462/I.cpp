/**
 *
 * 这个题目就比较的有意思，就是整人啊
 *
 * 但是真要说涉及浮点到这种程度到也确实容易死==
 *
 * 对于每一个点，确定一个范围，这个范围内可以处理到它；
 * 我们设这个角度区间是[angle±delta]
 *
 * 原来写炸的原因：
 * 重写了sort之后的部分就A了，原因不详
 * 我日，取消了C++构造器简写换成一般构造函数就A了？
 * 下次比赛还是少整这些没用的东西（）
 */
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long longs;
typedef long double longd;
enum bound {st=0,ed=1};

const double EPS = 1e-8;
const double PI = 3.1415926535897932384626;
const double PI2 = 2*PI;

struct ray
{
    int num;
    double angle;
    bound type;

    ray(int n,double ag,bound typ);
    bool operator<(const ray &r) const;
    bool operator<(const ray &&r) const;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t,n,d,x,y;
    int cnt;

    while(cin>>t) while(t--)
        {
            cin>>n>>d;
            vector<ray> v;
            longs d2 = d*d;
            longd r2;
            cnt = 0;
            for(int i=1;i<=n;++i)
            {
                cin>>x>>y;
                r2 = x*x+y*y;
                if(r2-EPS <= d2) continue;      // 原点周围d内必命中
                longd angle = atan2(y,x);
                longd delta = asin(d/sqrt(r2));
                ++cnt;
                v.emplace_back(cnt,angle-delta,st); // Clang-Tidy:原地构造
                v.emplace_back(cnt,angle+delta,ed); // 代替 push_back+构造
            }
            if(!cnt)
            {
                cout<<1<<endl;                  // 全在周围，一次解决
                continue;
            }
            sort(v.begin(),v.end());            // 逆时针，先开始边界再关闭边界
            int vs = v.size();
            int ans = cnt;
            for(int i=0;i<vs;++i)               // 以射线i作为起点，确保了所有可能
            {
                vector<bool> mark(cnt+1,false);
                vector<int> list;
                int c = 0;
                for(int j=0;j<vs;++j)           // 贪心：每道光尽可能消灭更多
                {
                    auto &vj = v[(i+j)%vs];
                    if(!vj.type)                // 找到开始边界
                    {
                        mark[vj.num] = true;
                        list.push_back(vj.num);
                    }
                    else if(mark[vj.num])       // 找到记录中的关闭边界
                    {
                        ++c;                    // 在一个边界之间，可以一束光解决
                        for(auto li : list)
                            mark[li] = false;
                        list.clear();
                    }
                }
                c += list.size();               // 队伍里残留的尚未处理的点（可能存在的未关闭节点
                if(c<ans) ans = c;
            }
            cout<<ans<<endl;
        }

    return 0;
}

bool ray::operator<(const ray &r) const
{
    if(fabs(angle-r.angle)>EPS)
        return angle < r.angle;
    return type < r.type;           // 开始边界在结束边界前
}

bool ray::operator<(const ray &&r) const
{
    return *this < r;
}

ray::ray(int n, double ag, bound typ)
{
    num = n;
    type = typ;
    angle = fmod(ag+PI2,PI2);       // 转变到[0,2π]范围内
}
