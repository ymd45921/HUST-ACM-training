#include <iostream>
#include <list>

using namespace std;

list<int> que;
int ans[3050];
int ansLength;
list<int> buf;
int inProblem;

inline void eraseNum(int n)
{
    auto i = que.begin();
    auto lim = que.end();
    int flag = 1;
    while(i!=lim)
    {
        if(flag==n)
        {
            i = que.erase(i);
            flag = 1;
            if(i==lim)return;
        }
        ++i;++flag;
    }
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for(int i=2;i<50000;++i)
    {
        que.push_back(i);
    }

    for(ansLength=0;ansLength<=3010;++ansLength)
    {
        ans[ansLength] = que.front();
        que.pop_front();
        eraseNum(ans[ansLength]);
    }

    while(cin>>inProblem)
    {
        buf.push_back(ans[inProblem-1]);
    }
    for(auto i : buf)
        cout<<i<<endl;

    return 0;
}