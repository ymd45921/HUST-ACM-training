/**
 * 
 * 这个题目看着还蛮吓人的：又是平面关系又是xyz的
 * 
 * 但是……这个z∈{0,1}，嗯……？
 * 这样的话倒是好办了==可以贪心了
 * 虽然不用像题解那样证明，但是想想也知道这是成立
 * 
 * 这么一说如果只有x和y的话是不是后面的汉诺塔很像？
 * 首先分到几个组，然后这个组里面的是可以互相匹配的
 * 
 * 这出题人可真是个STL大师
 * 
 * 草这个细节，这个题目如果不用自己的结构体重载就会炸
 */
/**
 * 
 */
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long longs;
typedef long double longd;

struct star
{
    int x,y,z;
    const bool operator<(const star& rhs) const;
};

int n,cnt;
star in[100010];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        cnt = 0;
        for(int i=0;i<n;++i)
        cin>>in[i].x>>in[i].y>>in[i].z;
        sort(in,in+n);

        multiset<int> que;
        multiset<int>::iterator it;
        for(int i=0;i<n;++i)
        {
            if(in[i].z)
            {
                it = que.lower_bound(in[i].y);  // 第一个大于等于
                if(it!=que.begin())             // 最大的小于存在
                {
                    --it; 
                    que.erase(it);
                    ++cnt;
                }
            }
            else que.insert(in[i].y);
        }
        cout<<cnt<<endl;
    }

    return 0;
}

const bool star::operator<(const star& rhs) const
{
    if(x==rhs.x) return z<rhs.z;    // 必须保证z=0的都在z=1的前面
    else return x<rhs.x;
}


// #include <iostream>
// #include <algorithm>
// #include <utility>
// #include <vector>
// #include <cstring>

// #define x first.first
// #define y first.second
// #define z second

// using namespace std;
// typedef long long longs;
// typedef long double longd;
// typedef pair<int,int> pos;
// typedef pair<pos,int> star;

// int n,c = 0,cnt = 0;
// star li[100010],ul[100010];
// bool uf[100010];
// // star in;
// // vector<pos> z0l,z1l;

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     while(cin>>n)
//     {
//         cnt = c = 0;
//         memset(uf,0,sizeof uf);
//         // z0l.clear(); z1l.clear();
//         for(int i=1;i<=n;++i)
//         {
//             // cin>>in.x>>in.y>>in.z;
//             cin>>li[i].x>>li[i].y>>li[i].z;
//             // if(in.z) z1l.push_back(make_pair(in.x,in.y));
//             // else z0l.push_back(make_pair(in.x,in.y));
//         }
//         // sort(z0l.begin(),z0l.end());
//         // sort(z1l.begin(),z1l.end());
//         sort(li+1,li+n);
        
//         for(int i=1;i<=n;++i)
//         {
//             if(!li[i].z) ul[++c] = li[i];
//             else
//             {
//                 int ymax=0,no=0;
//                 for(int j=1;j<=c;++j)
//                     if(!uf[j]&&ul[j].y<li[i].y)
//                         if(ul[j].y>ymax)no=j,ymax=ul[j].y;
//                 if(no) uf[no]=true,++cnt;
//             }
//         }
//         cout<<cnt<<endl;
//     }

//     return 0;
// }