#include <iostream>
#include <list>

using namespace std;
list<int> que;
int N,n;
int flag = 0;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>N;
    for(int i=0;i<N;++i)
    {
        cin>>n;
        for(int j=1;j<=n;++j)
        {
            que.push_back(j);
        }
        auto it = que.begin();
        auto itb = it;
        auto lim = que.end();
        while(que.size()>3)
        {
            if(it==lim)
            {
                it = que.begin();
                flag^=1;
            }
            if(flag)++it;
            ++it;
            it = que.erase(it);
        }
        for(auto elem : que)
        {
            cout<<elem<<' ';
        }
        cout<<endl;
        que.clear();
    }
    return 0;
}