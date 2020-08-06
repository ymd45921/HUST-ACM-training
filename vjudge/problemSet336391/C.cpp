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
        if(inArray[cur]==ite)
        {
            ++ite;
            ++cur;
        }
        else if(!tmp.empty()&&tmp.top()==inArray[cur])
        {
            ++cur;
            tmp.pop();
        }
        else if(ite<=blockLength)
        {
            tmp.push(ite);
            ++ite;
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
    for(auto i:ans)cout<<i;
    return 0;
}