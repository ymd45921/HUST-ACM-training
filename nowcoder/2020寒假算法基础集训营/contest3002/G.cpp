/**
 * 
 */
#include <iostream>
#include <cstring>

using namespace std;
typedef long long longs;
typedef long double longd;

int n,k;
char str[1000010];
int Next[1000010];
int length;

inline void buildNextArray()
{
    Next[0] = -1;
    int i = 0, j = -1;
    while(i<length)
    {
        if(-1==j||str[i]==str[j])
            Next[++i] = ++j;
        else j = Next[j];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n>>k)
    {
        cin>>str;
        length = strlen(str);
        
    }

    return 0;
}