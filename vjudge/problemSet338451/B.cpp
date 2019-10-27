#include <iostream>

using namespace std;

int n,k;
int in[1050];
int tmp,ans;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        cin>>k;
        for(int i=0;i<=k;++i)cin>>in[i];
        int cur = 0;
        tmp = n; ans = 0;
#ifdef mydebug
        cout<<"n = "<<n<<"; k = "<<k<<";\n";
        cout<<in[0];
        for(int i = 1;i<=k;++i)cout<<", "<<in[i];
        cout<<endl;
#endif
        while(cur<=k)
        {
            if(n<in[cur])
            {
                ans = -1;
                break;
            }
            else if(tmp>=in[cur]) tmp-=in[cur];
            else 
            {
                tmp = n-in[cur];
                ans++;
            }
            ++cur;
        }
        if(ans>0)cout<<ans<<endl;
        else cout<<"No Solution!"<<endl;
    }

    return 0;
}