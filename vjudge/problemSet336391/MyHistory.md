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

## Problem C

**Version 1** : 模拟错误
```c++
#include <iostream>
#include <stack>
#include <string>
#include <list>

using namespace std;

list<string> ans;
stack<int> tmp;
int blockLength;
int inArray[1010];

inline int processLine(const int blockLength)
{
    cin>>inArray[0];
    if(!inArray[0])return 0;
    else for(int i=1;i<blockLength;++i)cin>>inArray[i];
    bool flag = false;
    int cur = 0;
    for(int i=1;i<=blockLength;++i)
    {
        tmp.push(i);
        if(!tmp.empty()&&tmp.top()==inArray[cur])
        {
            tmp.pop();
            ++cur;
        }
    }
    while(cur<blockLength)
    {
        if(tmp.empty())break;
        if(tmp.top()==inArray[cur])
        {
            tmp.pop();
            ++cur;
        }
        else break;
    }
    if(cur==blockLength)flag = true;
    while(!tmp.empty())tmp.pop();
    if(flag) return 1;
    else return -1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>blockLength)
    {
        if(!blockLength)break;
        int reporter;
        while(reporter=processLine(blockLength))
        {
            if(reporter==1)ans.push_back("Yes\n");
            else ans.push_back("No\n");
        }
        ans.push_back("\n");
    }
    ans.pop_back();
    for(auto i:ans)cout<<i;
    return 0;
}
```

**Version 2** : 
```c++
#include <iostream>
#include <stack>
#include <string>
#include <list>

using namespace std;

list<string> ans;
stack<int> tmp;
int blockLength;
int inArray[1010];

inline int processLine(const int blockLength)
{
    cin>>inArray[0];
    if(!inArray[0])return 0;
    else for(int i=1;i<blockLength;++i)cin>>inArray[i];
    bool flag = false;
    int cur = 0;int ite = 1;
    while(cur<blockLength)
    {
        if(ite<=blockLength)
        {
            if(inArray[cur]==ite)
            {
                ++ite;
                ++cur;
            }
            else
            {
                tmp.push(ite);
                ++ite;
            }
        }
        else if(!tmp.empty()&&tmp.top()==inArray[cur])
        {
            ++cur;
            tmp.pop();
        }
        else break;
    }
    if(cur==blockLength)flag = true;
    while(!tmp.empty())tmp.pop();
    if(flag) return 1;
    else return -1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>blockLength)
    {
        if(!blockLength)break;
        int reporter;
        while(reporter=processLine(blockLength))
        {
            if(reporter==1)ans.push_back("Yes\n");
            else ans.push_back("No\n");
        }
        ans.push_back("\n");
    }
    ans.pop_back();
    for(auto i:ans)cout<<i;
    return 0;
}
```

## Problem D

**Version 1** : RE
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

**Version 2** : WA
```c++
#include <iostream>
#include <stack>
#include <iomanip>
#include <cstring>
#include <list>
#define myTest

using namespace std;

#ifdef myTest
#include <cassert>
#endif

char inString[250];
stack<char> opr;
stack<double> num;
list<double> ans;
double tmp = 0;
bool readNumberFlag = false;
bool calculateNowFlag = false;

inline void resetFlags()
{
    readNumberFlag = false;
    calculateNowFlag = false;
}

inline void calculateNow()
{
    if(opr.empty()||(num.size()<2))return;
    char myOpr = opr.top();
    double rHand = num.top();
    opr.pop(); num.pop();
    double lHand = num.top();
    num.pop();
    switch(myOpr)
    {
        case '+':
            num.push(lHand+rHand);
            break;
        case '-':
            num.push(lHand-rHand);
            break;
        case '*':
            num.push(lHand*rHand);
            break;
        case '/':
            num.push(lHand/rHand);
            break;
        default:
            num.push(lHand);
            num.push(rHand);
            opr.push(myOpr);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(1)
    {
        cin.getline(inString,210,'\n');
        int inLength = strlen(inString);
        if(inLength==1&&inString[0]=='0')break;
        if(inLength==0)continue;
        for(int i=0;i<inLength;++i)
        {
            if(inString[i]>='0'&&inString[i]<='9')
            {
                readNumberFlag = true;
                tmp *= 10;
                tmp += (inString[i]-'0');
            }
            else if(inString[i]==' '&&readNumberFlag)
            {
                num.push(tmp);
                tmp = 0;
                readNumberFlag = false;
                if(calculateNowFlag)
                {
                    calculateNow();
                    calculateNowFlag = false;
                }
            }
            else
            {
                if(inString[i]!=' ')
                    opr.push(inString[i]);
                if(inString[i]=='*'||inString[i]=='/')
                    calculateNowFlag = true;
            }
        }
        num.push(tmp);
        tmp = 0;
        while(!opr.empty()) calculateNow();
#ifdef myTest
        assert(num.size()==1);
        ans.push_back(num.top());
        num.pop();
        assert(num.empty());
#else
        ans.push_back(num.top());
        num.pop();
#endif
        resetFlags();
    }

    cout<<fixed<<setprecision(2);
    for(auto i:ans)cout<<i<<endl;
    return 0;
}
```

**Version 3** : WA
```c++
#include <iostream>
#include <stack>
#include <iomanip>
#include <cstring>
#include <list>
#define myTest

using namespace std;

#ifdef myTest
#include <cassert>
#endif

char inString[250];
list<char> opr;
list<double> num;
list<double> ans;
double tmp = 0;
bool readNumberFlag = false;
bool calculateNowFlag = false;

inline void resetFlags()
{
    readNumberFlag = false;
    calculateNowFlag = false;
}

inline void calculateNow()
{
    if(opr.empty()||(num.size()<2))return;
    char myOpr = opr.back();
    double rHand = num.back();
    opr.pop_back(); num.pop_back();
    double lHand = num.back();
    num.pop_back();
    switch(myOpr)
    {
        case '+':
            num.push_back(lHand+rHand);
            break;
        case '-':
            num.push_back(lHand-rHand);
            break;
        case '*':
            num.push_back(lHand*rHand);
            break;
        case '/':
            num.push_back(lHand/rHand);
            break;
        default:
            num.push_back(lHand);
            num.push_back(rHand);
            opr.push_back(myOpr);
    }
}

inline void calculate()
{
    if(opr.empty()||(num.size()<2))return;
    char myOpr = opr.front();
    double lHand = num.front();
    opr.pop_front(); num.pop_front();
    double rHand = num.front();
    num.pop_front();
    switch(myOpr)
    {
        case '+':
            num.push_front(lHand+rHand);
            break;
        case '-':
            num.push_front(lHand-rHand);
            break;
        case '*':
            num.push_front(lHand*rHand);
            break;
        case '/':
            num.push_front(lHand/rHand);
            break;
        default:
            num.push_front(rHand);
            num.push_front(lHand);
            opr.push_front(myOpr);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(1)
    {
        cin.getline(inString,210,'\n');
        int inLength = strlen(inString);
        if(inLength==1&&inString[0]=='0')break;
        if(inLength==0)continue;
        for(int i=0;i<inLength;++i)
        {
            if(inString[i]>='0'&&inString[i]<='9')
            {
                readNumberFlag = true;
                tmp *= 10;
                tmp += (inString[i]-'0');
            }
            else if(inString[i]==' '&&readNumberFlag)
            {
                num.push_back(tmp);
                tmp = 0;
                readNumberFlag = false;
                if(calculateNowFlag)
                {
                    calculateNow();
                    calculateNowFlag = false;
                }
            }
            else
            {
                if(inString[i]!=' ')
                    opr.push_back(inString[i]);
                if(inString[i]=='*'||inString[i]=='/')
                    calculateNowFlag = true;
            }
        }
        num.push_back(tmp);
        tmp = 0;
        if(calculateNowFlag)
            calculateNow();
        while(!opr.empty()) calculate();
#ifdef myTest
        assert(num.size()==1);
        ans.push_back(num.back());
        num.pop_back();
        assert(num.empty());
#else
        ans.push_back(num.top());
        num.pop();
#endif
        resetFlags();
    }

    cout<<fixed<<setprecision(2);
    for(auto i:ans)cout<<i<<endl;
    return 0;
}
```

**Version 4** : 后缀表达式版本，WA
```c++
#include <iostream>
#include <stack>
#include <iomanip>
#include <list>
#include <cstring>

using namespace std;
struct ele{char opr;double num;bool type;};

char inString[250];
stack<char> opr;
stack<double> num;
list<ele> suffix;
list<double> ans;

inline double readNumber(int& i)
{
    double tmp = 0;
    while(inString[i]>='0'&&inString[i]<='9')
    {
        tmp *= 10;
        tmp += (inString[i]-'0');
        ++i;
    }
    return tmp;
}

inline bool isOpreator(char ch)
{
    if(ch==' ')return false;
    else return true;
}

inline void pushSuffix(double num)
{
    suffix.push_back({'\0',num,false});
}

inline void pushSuffix(char opr)
{
    suffix.push_back({opr,0,true});
}

inline double calculate(double lhs, double rhs, char opr)
{
    switch(opr)
    {
    case '+':return lhs+rhs;
    case '-':return lhs-rhs;
    case '*':return lhs*rhs;
    case '/':return lhs/rhs;
    default :return 0;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(1)
    {
        cin.getline(inString,210,'\n');
        int inLength = strlen(inString);
        if(inLength==1&&inString[0]=='0')break;
        if(inLength==0)continue;

        for(int i=0;i<inLength;++i)
        {
            if(inString[i]>='0'&&inString[i]<='9')            
                pushSuffix(readNumber(i));                    
            else
            {
                switch(inString[i])
                {
                case '+': case '-':
                    if(!opr.empty())
                        while(!opr.empty())
                        {
                            pushSuffix(opr.top());
                            opr.pop();
                        }
                    opr.push(inString[i]);
                    break;
                case '*': case '/':
                    if(opr.empty()||opr.top()=='+'||opr.top()=='-')
                        opr.push(inString[i]);
                    else
                    {
                        while(!opr.empty())
                        {
                            if(opr.top()=='+'||opr.top()=='-')break;
                            pushSuffix(opr.top());
                            opr.pop();
                        }
                        opr.push(inString[i]);
                    }
                    break;
                default:
                    break;
                } 
            }
        }
        while(!opr.empty())
        {
            pushSuffix(opr.top());
            opr.pop();
        }

        double lhs,rhs;
        char tmp;
        while(!suffix.empty())
        {
            if(!suffix.front().type)
                num.push(suffix.front().num);
            else
            {
                tmp = suffix.front().opr;
                rhs = num.top();
                num.pop();
                lhs = num.top();
                num.pop();
                num.push(calculate(lhs,rhs,tmp));
            }
            suffix.pop_front();
        }

        ans.push_back(num.top());
        num.pop();
    }

    cout<<fixed<<setprecision(2);
    for(auto i:ans)cout<<i<<endl;
    return 0;
}
```

**Terminate** : 抄的版本，不知道我哪里有问题
```c++
#include<stdio.h>
#include<stack>
#include<algorithm>
using namespace std;

int main()
{
    stack<double> s;
    int n;
    while(~scanf("%d",&n)) {
        char c;
        c = getchar();
        if(c=='\n' && n==0) {
            break;
        }
        s.push(n);
        c = getchar();
        double m;
        while(~scanf("%d",&n)) {
            if(c == '*') {
                m = s.top();
                m *= n;
                s.pop();
                s.push(m);
            }
            if(c == '/') {
                m = s.top();
                m /= n;
                s.pop();
                s.push(m);
            }
            if(c == '+') {
                s.push(n);
            }
            if(c == '-') {
                n = -n;
                s.push(n);
            }
            if(c=getchar() == '\n') {
                break;
            }
            c = getchar();
            }
            double sum = 0;
            while(!s.empty()) {
                sum += s.top();
                s.pop();
        }
        printf("%.2lf\n",sum);
    }
return 0;
} 
```

## Problem E

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