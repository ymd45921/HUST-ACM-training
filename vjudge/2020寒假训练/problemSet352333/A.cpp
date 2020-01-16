/**
 * @字符串
 *
 * 看毛片，看毛片
 * 其实也不完全算是看毛片
 *
 * 又及：POJ不认识nullptr
 */
#include <cstring>
#define _C_IOSTREAM_

#ifdef _C_IOSTREAM_
#include <cstdio>
#elif defined _CXX_IOSTREAM_
#include <iostream>
#endif

using namespace std;

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
#ifdef _CXX_IOSTREAM_
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>str)
    {
        length = strlen(str);
        if(1==length&&'.'==str[0])
            return 0;
        buildNextArray();
        if(!(length%(length-Next[length])))
            cout<<length/(length-Next[length])<<endl;
        else cout<<1<<endl;
    }
#elif defined _C_IOSTREAM_
    while(scanf("%s",str,1000001))
    {
        length = strlen(str);
        if(1==length&&'.'==str[0])
            return 0;
        buildNextArray();
        if(!(length%(length-Next[length])))
            printf("%d\n",length/(length-Next[length]));
        else printf("1\n");
    }
#endif
    return 0;
}