#include <iostream>
#include <cstring>

using namespace std;

char in[1050];
int ans[10010];
int length = 0;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tmp,cur;
    bool flag = false;

    while(cin>>in)
    {
        flag=tmp=cur=0;
        while(in[cur])
        {
            if(flag)break;
            switch(in[cur])
            {
                case '(':++tmp;break;
                case ')':--tmp;break;
                case 'B':
                    ans[length] = tmp;
                    flag = true;
                    break;
                default:break;
            }
            ++cur;
        }
        ++length;
    }

    for(int i=0;i<length;++i)cout<<ans[i]<<endl;
    return 0;
}