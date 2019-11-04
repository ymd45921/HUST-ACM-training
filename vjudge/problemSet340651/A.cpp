#include <iostream>

using namespace std;

bool map[550][550];
int h,w;
char ch;
int counter = 0;
bool foundFlag = false;
bool continueFlag = true;

inline bool caster(char ch)
{
    if(ch=='*')
    {
        ++counter;
        return true;
    }
    else return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>h>>w;
    for(int i=0;i<h;++i)
        for(int j=0;j<w;++j)
        {
            cin>>ch;
            map[i][j]=caster(ch);
        }
    int limh = h-1,limw = w-1;
    
    if(counter<5)
    continueFlag = foundFlag = false;

    if(continueFlag)
    for(int i=1;i<limh;++i)
    {
        for(int j=0;j<limw;++j)
            if(map[i][j])
            {
                if(map[i-1][j]&&map[i+1][j]&&map[i][j-1]&&map[i][j+1])
                {
                    while(--i>=0&&map[i][j]){map[i][j]=false;}
                    while(++i<h&&map[i][j]){map[i][j]=false;}
                    while(--j>=0&&map[i][j]){map[i][j]=false;}
                    while(++j<w&&map[i][j]){map[i][j]=false;}
                    foundFlag = true;
                }
                else
                {
                    foundFlag = false;
                    continueFlag = false;
                    break;
                }
                
            }
        if(!continueFlag)break;   
    }
    if(continueFlag&&foundFlag)
    for(int i=0;i<h;++i)
        if(map[i][0]||map[i][limw])
        {
            foundFlag = false;
            continueFlag = false;
            break;
        }
    if(continueFlag&&foundFlag)
    for(int j=0;j<w;++j)
        if(map[limh][j]||map[0][j])
        {
            foundFlag = false;
            continueFlag = false;
            break;
        }
    if(foundFlag)cout<<"YES";
    else cout<<"NO";

    return 0;
}