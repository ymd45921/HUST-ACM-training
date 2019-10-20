#include <iostream>
#include <list>

using namespace std;
typedef int hito;

list<hito> que;
list<int> ans;
int in;

inline void findAnswer()
{
    if(que.empty())return;
    int tmp = que.front();
    ans.push_back(tmp);
    que.pop_front();
    auto i = que.begin();
    auto lim = que.end();
    int flag=1;
    for(;i!=lim;++i)
    {
        if(flag==tmp)
        {
            i = que.erase(i);
            flag=0;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    for(int i=2;i<50050;++i)
        que.push_back(i);
    while(ans.size()<3050)
    {
        findAnswer();
    }

}