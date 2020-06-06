/**
 *
 *
 */
#define USING_STDIO 0
#if USING_STDIO
#include <cstdio>
#include <cctype>
#else
#include <iostream>
#include <iomanip>
#endif

#include <algorithm>
#include <cstring>
#include <cctype>
#include <functional>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;

template <typename number>
int compareTo(number x) {return x < -eps ? -1 : x > eps;}
template <typename number>
int compareTo(number a, number b) {return compareTo(a-b);}

#if USING_STDIO
inline int nextInt()
{
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
    return x*f;
}
#endif

string s, a;
auto process = [](int repeat, string &alpha)
{   while (repeat --) a.append(alpha);  };
string subString(int &i)
{
    string ret;
    while (s[i] != ']' && s[i] != string::npos)
    {
        if (isdigit(s[i]))
        {
            auto rep = s[i] - '0';
            i += 2;
            auto sub = subString(i);
            while (rep --) ret.append(sub);
        }
        else if (isalpha(s[i]))
            ret.push_back(s[i]);
        ++ i;
    }
    return ret;
}

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif

    while (cin >> s)
    {
        a = "";
        auto length = s.length();
        for (int i = 0; i < length; ++ i)
            if (isdigit(s[i]))
            {
                auto rep = s[i] - '0';
                auto begin = i += 2;
                auto sub = subString(i);
                process(rep, sub);
            }
            else if (isalpha(s[i]))
                a.push_back(s[i]);
            else ++ i;
        cout << a << endl;
    }

    return 0;
}