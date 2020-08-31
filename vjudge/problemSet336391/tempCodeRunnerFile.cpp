#include <iostream>
#include <stack>
#include <iomanip>
#include <list>
#include <cstring>

using namespace std;
struct ele{char opr;long double num;bool type;};

char inString[250];
stack<char> opr;
stack<long double> num;
list<ele> suffix;
list<long double> ans;

inline long double readNumber(int& i)
{
    long double tmp = 0;
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

inline void pushSuffix(long double num)
{
    suffix.push_back({'\0',num,false});
}

inline void pushSuffix(char opr)
{
    suffix.push_back({opr,0,true});
}

inline long double calculate(long double lhs, long double rhs, char opr)
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

        long double lhs,rhs;
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