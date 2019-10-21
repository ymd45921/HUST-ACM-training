# HUST-ACM 2019新生B class训练题

专题：数据结构基础 日期：2019-10-19

## Problem A

为什么我总是感觉这个题目有约瑟夫环式的递推公式？

**Version 1** : 没有正确性的瞎jb优化
```c++
#include <iostream>
#include <cstring>

using namespace std;

int N,n;
int theQue[5005];
int theNext[5005];

inline void cut2(int& length)
{
    int lim = length/2;
    int cur = 1;
    for(int i=0;i<lim;++i)
    {
        cur = theNext[cur] = theNext[theNext[cur]];
        if(--length==3)return;
    }
}

inline void cut3(int& length)
{
    int lim = length/3;
    int cur = 1;
    for(int i=0;i<lim;++i)
    {
        cur = theNext[cur];
        cur = theNext[cur] = theNext[theNext[cur]];
        if(--length==3)return;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    theNext[0]=0;

    cin>>N;
    for(int i=0;i<N;++i)
    {
        cin>>n;
        if(n<=3)
        {
            int x = 1;
            while(x<=n)
            {
                cout<<x<<' ';
                x++;
            }
            cout<<endl;
        }
        else if(n-(n>>1)<=3)
        {
            int x = 1;
            while(x<=n)
            {
                cout<<x<<' ';
                x+=2;
            }
            cout<<endl;
        }
        else
        {
            int x = 1,cur = 1;
            while(x<=n)
            {
                theQue[cur]=x;
                theNext[cur]=cur+1;
                ++cur;
                x+=2;
            }
            theNext[--cur]=-1;
            int flag = 1;
            int length = n-(n>>1);
            while(length>3)
            {
                if(flag)cut3(length);
                else cut2(length);
                flag^=1;
            }
            cout<<theQue[1]<<' '<<theQue[theNext[1]]<<' '<<theQue[theNext[theNext[1]]]<<endl;
        }
    }

    return 0;
}
```
错误分析：应该是数组指针没指对地方==改了一下，这个版本应该不至于WA了吧。不对，还是WA了==
查了一下，好像又是个语文题？

**Version 2** : Presentation Error.
```c++
#include <iostream>
#include <cstring>
#define MEMSET0(x) memset(x,0,sizeof(x))

using namespace std;

int N,n;
int theQue[5005];
int theNext[5005];

inline void cut2(int& length)
{
    int lim = length/2;
    int cur = 1;
    for(int i=0;i<lim;++i)
    {
        cur = theNext[cur] = theNext[theNext[cur]];
        --length;
    }
}

inline void cut3(int& length)
{
    int lim = length/3;
    int cur = 1;
    for(int i=0;i<lim;++i)
    {
        cur = theNext[cur];
        cur = theNext[cur] = theNext[theNext[cur]];
        --length;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    theNext[0]=0;

    cin>>N;
    for(int i=0;i<N;++i)
    {
        cin>>n;
        MEMSET0(theNext);
        MEMSET0(theQue);
        if(n<=3)
        {
            int x = 1;
            while(x<=n)
            {
                cout<<x<<' ';
                x++;
            }
            cout<<endl;
        }
        else if(n-(n>>1)<=3)
        {
            int x = 1;
            while(x<=n)
            {
                cout<<x<<' ';
                x+=2;
            }
            cout<<endl;
        }
        else
        {
            int x = 1,cur = 1;
            while(x<=n)
            {
                theQue[cur]=x;
                theNext[cur]=cur+1;
                ++cur;
                x+=2;
            }
            theNext[--cur]=-1;
            int flag = 1;
            int length = n-(n>>1);
            while(length>3)
            {
                if(flag)cut3(length);
                else cut2(length);
                flag^=1;
            }
            cout<<theQue[1]<<' ';
            if(theQue[theNext[1]])cout<<theQue[theNext[1]]<<' ';
            if(theQue[theNext[theNext[1]]])cout<<theQue[theNext[theNext[1]]];
            cout<<endl;
        }
    }

    return 0;
}
```
错误分析：把答案用数组存了一起输出就没问题了。

## Problem B

常规忘记在`while`循环里面移动游标导致死循环…………

## Problem C


## Problem D

学习了`std::istream::getline()`的使用方法。以后也不用谈输入色变了。

**Version 1** : RE还行。这题你写的多丑啊==
```c++
#include <iostream>
#include <stack>
#include <cstring>
#include <iomanip>

using namespace std;
stack<double> num;
stack<char> opr;
char in[250];
int length = 0;
double ans[250];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double tmp = 0;
    bool flag = false;

    while(1)
    {
        cin.getline(in,205,'\n');
        int len;
        if((len=strlen(in))==1)break;
        for(int i=0;i<len;++i)
        {
            if(in[i]>='0'&&in[i]<='9')
            {
                tmp*=10;
                tmp+=(in[i]-'0');
                flag = true;
            }
            else
            {
                switch(in[i])
                {
                    case ' ':
                        if(flag)
                        {
                            flag = false;
                            num.push(tmp);
                            tmp = 0;

                            if(!opr.empty())
                            {
                                switch(opr.top())
                                {
                                    case '*':
                                        opr.pop();
                                        tmp = num.top();
                                        num.pop();
                                        tmp*=num.top();
                                        num.pop();
                                        num.push(tmp);
                                        tmp = 0;
                                        break;
                                    case '/':
                                        opr.pop();
                                        tmp = num.top();
                                        num.pop();
                                        tmp=num.top()/tmp;
                                        num.pop();
                                        num.push(tmp);
                                        tmp = 0;
                                        break;
                                    default:break;
                                }
                            }
                        }
                        break;
                    default:
                        opr.push(in[i]);
                }
            }
        }
        num.push(tmp);
        while(!opr.empty())
        {
            switch(opr.top())
            {
                case '+':
                    opr.pop();
                    tmp = num.top();
                    num.pop();
                    tmp+=num.top();
                    num.pop();
                    num.push(tmp);
                    tmp = 0;
                    break;
                case '-':
                    opr.pop();
                    tmp = num.top();
                    num.pop();
                    tmp=num.top()-tmp;
                    num.pop();
                    num.push(tmp);
                    tmp = 0;
                    break;
                case '*':
                    opr.pop();
                    tmp = num.top();
                    num.pop();
                    tmp*=num.top();
                    num.pop();
                    num.push(tmp);
                    tmp = 0;
                    break;
                case '/':
                    opr.pop();
                    tmp = num.top();
                    num.pop();
                    tmp=num.top()/tmp;
                    num.pop();
                    num.push(tmp);
                    tmp = 0;
                    break;
                default:break;
            }
        }
        ans[length++]=num.top();
        num.pop();
    }

    cout<<fixed<<setprecision(2);
    for(int i=0;i<length;++i)cout<<ans[i]<<endl;
    return 0;
}
```
错误原因：个人建议别找错误了，重新写还来的快些。行加大答案数组之后直接WA了==

## Problem E

这个屌STL题目怕不是在搞我。

**Version 1** : 看来你就是不给我用STL了是吧。
```c++
#include <iostream>
#include <list>

using namespace std;
typedef long long longs;

longs n,m;
longs*in;
list<longs> thelist;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    in = new longs[n];
    for(int i=0;i<n;++i)
    {
        cin>>in[i];
        thelist.push_back(in[i]);
    }
    cin>>m;
    thelist.remove(m);
    cout<<n<<endl;
    for(int i=0;i<n;++i)cout<<in[i]<<' ';
    cout<<endl<<thelist.size()<<endl;
    for(auto i=thelist.begin();i!=thelist.end();++i)
        cout<<*i<<' ';
    return 0;
}
```
那我之好手动重写了。

**Version 2** ： 非STL版本，虽然没过，但是知道这个题是一个语文题了
```c++
#include <iostream>

using namespace std;
typedef long long longs;

longs n,m;
longs*in;
longs length;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    in = new longs[n];
    for(int i=0;i<n;++i)
    {
        cin>>in[i];
    }
    cin>>m;
    length = n;

    for(int i=0;i<n;++i)
    {
        if(in[i]==m)--length;
    }
    cout<<n<<endl;
    for(int i=0;i<n;++i)cout<<in[i]<<' ';
    cout<<endl<<length<<endl;
    for(int i=0;i<n;++i)
    {
        if(in[i]==m);
        else cout<<in[i]<<' ';
    }
    return 0;
}
```
这道题目标准输入会有多组数据，而且输出末尾不可以有空格

## Problem F

**Version 1** : 不是玩素数啊
```c++
#include <iostream>
#include <cstring>
#include <list>

#define mylogx

using namespace std;

int prime[5500];
bool desk[50000];
int maxl = 49980;
list<int> ans;
int input;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(prime,0,sizeof(prime));
    memset(desk,-1,sizeof(desk));
    for(int i=2;i<maxl;++i)
    {
        if(desk[i])
        {
            prime[++prime[0]] = i;
            int tmp;
            for(int j=2;(tmp=j*i)<maxl;++j)
            {
                desk[tmp]=false;
            }
        }
    }
#ifdef mylog
    for(int i=1;i<=prime[0];++i)cout<<prime[i]<<' ';
    cout<<endl;
#endif
    while(cin>>input)ans.push_back(prime[input]);
    for(auto i:ans)cout<<i<<endl;
    return 0;
}
```
要不咱还是乖乖的模拟吧？

妈的这个问题F到底怎么回事，怎么什么代码都过不了。
```c++
#include <iostream>
#include <list>

using namespace std;
typedef int hito;

list<hito> que;
list<int> ans;
int in, tmp;

inline void findAnswer()
{
	if (que.empty())return;
	int tmp = que.front();
	ans.push_back(tmp);
	que.pop_front();
	auto i = que.begin();
	auto lim = que.end();
	int flag = 0;
	for (; i != lim; ++i)
	{
		++flag;
		if (flag == tmp)
		{
			i = que.erase(i);
			flag = 1;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	for (int i = 2; i < 50050; ++i)
		que.push_back(i);
	while (ans.size() < 3050)
	{
		findAnswer();
	}
	auto it = ans.begin();
	auto lim = ans.end();
	while (cin >> in)
	{
		it = ans.begin();
		for (int c = 0; c < in; ++c)
		{
			++it;
		}
		ans.push_back(*it);
	}
	it = ans.begin();
	lim--;
	for (; it != lim; ++it)
	{
		cout << *it << endl;
	}
	cout << *lim;
	return 0;
}
```
乖乖模拟罢了，还比较省事

## Problem G

这个题目不能用`sstream`作为输出缓冲，会只输出一行（也许`\n`就是一个清除缓冲区的标记？）

除了利用`sstream`进行Parse之外，C++也提供了一个类似Java的`to_string()`函数

下次不管`else`或者`if`、`for`后是不是只有一个语句，我都要花括弧括起来==养成好习惯，这简单写法害人不浅（）`while`因为一般要改变状态，永远都不要简写！！

## Conclusion & Summary

这次的练习除了那个语文题都很简单。也有人，甚至是oierDB查不到的人，可以在1.5~2h内AK并且试错次数极少。这是你要追求的：一是快速，二是准确率。建议在洛谷上或者其他的练习中注意这方面。