/**
 *
 * 硬要说的话确实是这个理。怎么快怎么走
 *
 * 但是真的不需要考虑各种情况吗
 *
 * 有一种情况是判明的：就是如果到直接走了，那就再也不用开立方了
 *
 * 特别注意：开立方只能用pow的1/3，但是如果被pow的数字是负数会输出NaN，要手动处理。
 *
 * 怎么还T了（）难道是因为longd的原因？
 * 卡的原因无他，就是IO，使用C的IO就不会有问题。
 * 
 * 但是看一下这题目，IO的数据量并不大啊……
 * 正式情况下还是乖乖C的IO吧……找个时间做一个实验验证一下
 * 
 * 不对还是觉得不对劲，这个题目不应该是卡IO的感觉啊……
 * 而且我自己写的代码看起来逻辑一致啊，换成CIO不是照样炸（）
 */
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
typedef long long longs;
typedef long double longd;

const double root = 1.0/3.0;

int t,a,b;

//int main()
//{
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
//    cout<<fixed<<setprecision(9);
//
//    while(cin>>t)
//        while(t--)
//        {
//            cin>>a>>b;
//            double cnt = 0;
//            double al=a,bl=b;
//            double tmp;
//            while(1)
//            {
//                if(al<0) tmp = -pow(-al,root);
//                else tmp = pow(al,root);
//                // tmp = cubt(al);          // 不包装成函数，20%->40%
//                if(abs(tmp-bl)+1.0<abs(al-bl))
//                {
//                    cnt += 1.0;
//                    al = tmp;
//                }
//                else
//                {
//                    cnt += abs(al-bl);      // 这句话放进去，40%->80%
//                    break;
//                }
//            }
//            cout<<cnt<<endl;
//        }
//
//    return 0;
//}

int main()
{
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
//    cout<<fixed<<setprecision(9);

    int T; 
    while(cin>>T)
    while(T--){
        int a, b; scanf("%d%d", &a, &b);
        double ans = 0;
        double ca = a, cb = b;
        double p = 1.0/3.0;
        while(1){
            double na;
            if(ca < 0) na = -pow(-ca,p);
            else na = pow(ca, p);
            if(abs(na-cb)+1.0 < abs(ca-cb)) ans += 1.0, ca = na;
            else {
                ans += abs(ca-cb); break;
            }
        }
        printf("%.9f\n", ans);
    }
}