/**
 *
 */
#include <iostream>
#include <stack>
#include <string>

using namespace std;
typedef long long longs;
typedef long double longd;

const char Yes[] = "Yes";
const char No[] = "No";

string in;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>in)
    {
        stack<char> table;
        bool flag = true;
        for(char ch : in)
        {
            switch(ch)
            {
                case '(':case '[':case '{':
                    table.push(ch);
                    break;
                case ')':
                    if(!table.empty() && table.top()=='(')table.pop();
                    else flag=false;
                    break;
                case ']':
                    if(!table.empty() && table.top()=='[')table.pop();
                    else flag=false;
                    break;
                case '}':
                    if(!table.empty() && table.top()=='{')table.pop();
                    else flag=false;
                    break;
                default: break;
            }
            if(!flag) break;
        }
        if(!table.empty()) flag = false;
        if(flag) cout<<Yes<<endl;
        else cout<<No<<endl;
    }

    return 0;
}