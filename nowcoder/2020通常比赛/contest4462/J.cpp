/**
 *
 * 手打高精度不够熟练
 */
#include <iostream>
#include <string>
#include <cstring>

using namespace std;
typedef long long longs;
typedef long double longd;

const char sk[] = "skipped";
int ans[10010],up=0;
string s;
int n;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        while(n--)
        {
            cin>>s;
//            memset(ans,0,sizeof(ans));
            bool flag = false;
            auto ff = s.find_first_of("+");
            if(ff!=string::npos)
            {
                auto fl = s.find_last_of("+");
                if(ff!=fl)
                {
                    cout<<sk<<endl;
                    flag = true;
                }
            }
            else
            {
                cout<<sk<<endl;
                flag = true;
            }

            if(flag) continue;
            string a = s.substr(0,ff);
            string b = s.substr(ff+1,s.length()-ff-1);
            if(!a.length()||!b.length())
            {
                cout<<sk<<endl;
                continue;
            }
            up = 0; int c = 0;
            for(auto i=a.rbegin();i!=a.rend();++i,++c)
                ans[c] += *i-'0';
            int cc = 0;
            for(auto i=b.rbegin();i!=b.rend();++i,++cc)
                ans[cc] += *i-'0';
            cc = a.length()>b.length()?a.length():b.length();
            c = 0;
            while(c<cc||up||ans[c])
            {
                ans[c] += up;
                up = ans[c]/10;
                ans[c] %= 10;
                ++c;
            }
            for(int i = c-1;i>=0;--i)
            {
                cout<<ans[i];
                ans[i] = 0;
            }
            cout<<endl;
        }
    }

    return 0;
}