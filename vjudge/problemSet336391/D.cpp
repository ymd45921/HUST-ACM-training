#include <iostream>
#include <stack>
#include <cstring>
#include <iomanip>

using namespace std;
stack<double> num;
stack<char> opr;
char in[250];
int length = 0;
double ans[25025];

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