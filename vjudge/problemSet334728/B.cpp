#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char s[105];
    int letter[26];
    bool flag = true;

    memset(letter,0,sizeof(letter));

    for(int i=0;i<2;++i)
    {
        cin>>s;
        int cur = 0;
        while(s[cur]!='\0') 
        {
            ++letter[s[cur]-'A'];
            ++cur;    
        }
    }
    cin>>s;
    int cur = 0;
    while(s[cur]!='\0') 
    {
        --letter[s[cur]-'A'];
        ++cur;
    }

    for(int i=0;i<26;++i)
        if(letter[i])
        {
            flag = false;
            break;
        }

    if(flag) cout<<"YES";
    else cout<<"NO";
    return 0;
}