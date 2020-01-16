/**
 * 这个……看起来只能搜索啊：（
 * 
 * 使用挪移的方法可以降低复杂度的次数
 * 还可以使用hash加快查找速度
 * 
 * 但是总感觉搜索必然超时==
 * 可以使用二分进一步加快搜索速度：）
 */
#include <iostream>
#include <vector>
#include <algorithm>

#define max(x,y) (x>y?x:y)

using namespace std;

int a1,a2,a3,a4,a5;
int x1,x2,x3,x4,x5;
int cnt = 0;

vector<int> lvalue;
int tmp;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>a1>>a2>>a3>>a4>>a5;

    for(int i=1;i<=50;++i)
    for(int j=1;j<=50;++j)
    for(int k=1;k<=50;++k)
    {
        lvalue.push_back(i*a1+j*a2+k*a3);
        lvalue.push_back(i*a1+j*a2-k*a3);
        lvalue.push_back(i*a1-j*a2+k*a3);
        lvalue.push_back(i*a1-j*a2-k*a3);
        lvalue.push_back(-i*a1+j*a2+k*a3);
        lvalue.push_back(-i*a1-j*a2+k*a3);
        lvalue.push_back(-i*a1+j*a2-k*a3);
        lvalue.push_back(-i*a1-j*a2-k*a3);
    }
    sort(lvalue.begin(),lvalue.end());

    for(int i=1;i<=50;++i)
    for(int j=1;j<=50;++j)
    {
        tmp = i*a4+j*a5;
        auto res1 = equal_range(lvalue.begin(),lvalue.end(),tmp);
        cnt += max(0,res1.second-res1.first);

        tmp = i*a4-j*a5;
        auto res2 = equal_range(lvalue.begin(),lvalue.end(),tmp);
        cnt += max(0,res2.second-res2.first);

        tmp = -i*a4+j*a5;
        auto res3 = equal_range(lvalue.begin(),lvalue.end(),tmp);
        cnt += max(0,res3.second-res3.first);

        tmp = -i*a4-j*a5;
        auto res4 = equal_range(lvalue.begin(),lvalue.end(),tmp);
        cnt += max(0,res4.second-res4.first);
    }
    cout<<cnt;
    return 0;
}