#include <iostream>
#include <cstdio>

using namespace std;
typedef long long longs;

struct number
{
    char n[N];
    static int lim;

    void setInf();
    void setZero();
    void setNull();
    static void setLim(int n){ lim=n; }
    bool operator<(const number& rhs) const;
    bool operator>(const number& rhs) const;
};

const int N = 405;

int n,m;
number num[45];
number dp[45][45];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin>>n>>m)
    {
        num[0].setZero();
        for(int i=1;i<=n;++i)
        {
            for(int j=0;j<m;++j)
            {
                cin>>num[i].n[j];
            }
        }
        number::setLim(n);

    }
    

    return 0;
}

bool number::operator<(const number& rhs) const
{
    for(int i=0;i<lim;++i)
    {
        if(n[i]!=rhs.n[i])
            return n[i]<rhs.n[i];
        else continue;
    }
    return false;
}

void number::setInf()
{
    for(int i=0;i<lim;++i)
        n[i] = '9';
    return;
}

void number::setZero()
{
    for(int i=0;i<lim;++i)
        n[i] = '0';
    return;
}

void number::setNull()
{
    for(int i=0;i<lim;++i)
        n[i] = 0;
    return;
}

bool number::operator>(const number& rhs) const
{
    for(int i=0;i<lim;++i)
    {
        if(n[i]!=rhs.n[i])
            return n[i]>rhs.n[i];
        else continue;
    }
    return false;
}