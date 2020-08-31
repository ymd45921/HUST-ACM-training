# HUST-ACM 2019新生训练题

专题：寒假七天乐 Day 1 日期：2020-1-13

## Problem D @HDU-3183 A Magic Lamp
这是一个RMQ模板题，数据量不大，不要求高性能，就算向我那样子憨批的优先级队列也是可以过的（）

自己写的优先级队列的版本过不了，再网上抄了一个贪心下来，过了，原因不明（）

贪心最后过的版本：
```c++
#include<iostream>
#include<string>

using namespace std;

string n;
int m;
char ans[1050]{0};
int upper,lower,anslen;
int zeropos;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n>>m)
    {
        int len = n.length();
        bool flag = false;
        upper = 0;
        lower = m;
        anslen = len-m;

        for(int i=0;i<anslen;++i)
        {
            char min = n[upper];
            for(int j=upper+1;j<=lower;++j)
                if(n[j]<min)
                {
                    min = n[j];
                    upper = j;
                }
            ++lower;
            ++upper;
            if(!flag)
            {
                ans[i] = min;
                flag = true;
            }
            else ans[i] = min;
        }
        ans[anslen] = '\0';
        if(!flag)
            cout << "0";
        else
        {
            zeropos = 0;
            while(ans[zeropos]=='0')++zeropos;
            if(ans[zeropos]=='\0')cout<<"0";
            else cout<<ans+zeropos;
        }
        cout << endl;
    }

    return 0;
}
```
我不觉得我的思路和他的有什么区别，但是就是我没有过，就非常的鬼畜。有时间再好好研究吧==
