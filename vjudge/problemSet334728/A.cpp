#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int stat[2];
    int n;
    char c;

    memset(stat,0,sizeof(stat));

    cin >> n;
    while(cin>>c)
    {
        int tmp = c-'n';
        if(tmp<0||tmp>1);
        else ++stat[tmp];
    }

    stat[1]-=stat[0];

    for(int i=0;i<stat[0];++i)cout<<"1 ";
    for(int i=0;i<stat[1];++i)cout<<"0 ";

    return 0;
}