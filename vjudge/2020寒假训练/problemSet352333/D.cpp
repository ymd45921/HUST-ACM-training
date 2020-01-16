/**
 * 这个……看起来只能搜索啊：（
 *
 * 使用挪移的方法可以降低复杂度的次数
 * 还可以使用hash加快查找速度
 *
 * 但是总感觉搜索必然超时==
 * 可以使用二分进一步加快搜索速度：）
 *
 * 错误原因：方程打错力==
 */
#include <iostream>
#include <algorithm>

#define max(x,y) (x>y?x:y)

using namespace std;

int a1,a2,a3,a4,a5;
int cnt = 0;

int lvalue[1000010];
int _size = 0;
int tmp;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>a1>>a2>>a3>>a4>>a5;

//    for(int i=1;i<=50;++i)
//        for(int j=1;j<=50;++j)
//            for(int k=1;k<=50;++k)
//            {
//                lvalue.push_back(i*a1*a1*a1+j*a2*a2*a2+k*a3*a3*a3);
//                lvalue.push_back(i*a1*a1*a1+j*a2*a2*a2-k*a3*a3*a3);
//                lvalue.push_back(i*a1*a1*a1-j*a2*a2*a2+k*a3*a3*a3);
//                lvalue.push_back(i*a1*a1*a1-j*a2*a2*a2-k*a3*a3*a3);
//                lvalue.push_back(-i*a1*a1*a1+j*a2*a2*a2+k*a3*a3*a3);
//                lvalue.push_back(-i*a1*a1*a1-j*a2*a2*a2+k*a3*a3*a3);
//                lvalue.push_back(-i*a1*a1*a1+j*a2*a2*a2-k*a3*a3*a3);
//                lvalue.push_back(-i*a1*a1*a1-j*a2*a2*a2-k*a3*a3*a3);
//            }
    for(int i=-50;i<=50;++i)
        if(!i)continue;
        else for(int j=-50;j<=50;++j)
            if(!j)continue;
            else for(int k=-50;k<=50;++k)
                if(!k)continue;
                else lvalue[_size++] = (-i*i*i*a1-j*j*j*a2-k*k*k*a3);
    sort(lvalue,lvalue+_size);

//    for(int i=1;i<=50;++i)
//        for(int j=1;j<=50;++j)
//        {
//            tmp = i*a4*a4*a4+j*a5*a5*a5;
//            auto res1 = equal_range(lvalue.begin(),lvalue.end(),tmp);
//            cnt += max(0,res1.second-res1.first);
//
//            tmp = i*a4*a4*a4-j*a5*a5*a5;
//            auto res2 = equal_range(lvalue.begin(),lvalue.end(),tmp);
//            cnt += max(0,res2.second-res2.first);
//
//            tmp = -i*a4*a4*a4+j*a5*a5*a5;
//            auto res3 = equal_range(lvalue.begin(),lvalue.end(),tmp);
//            cnt += max(0,res3.second-res3.first);
//
//            tmp = -i*a4*a4*a4-j*a5*a5*a5;
//            auto res4 = equal_range(lvalue.begin(),lvalue.end(),tmp);
//            cnt += max(0,res4.second-res4.first);
//        }
    for(int i=-50;i<=50;++i)
        if(!i)continue;
        else for(int j=-50;j<=50;++j)
            if(!j)continue;
            else
            {
                tmp = i*i*i*a4+j*j*j*a5;
                auto res = equal_range(lvalue,lvalue+_size,tmp);
                cnt += max(0,(res.second-res.first));
            }
    cout<<cnt;
    return 0;
}