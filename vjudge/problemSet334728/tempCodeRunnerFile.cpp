#include <iostream>

using namespace std;
typedef long long longs;

longs n,l,r,ans=0;
longs arrayLength;

inline longs calculator(longs n)
{
    if(n==1)return 1;
    else
    {
        longs length = 1;
        longs tmp = 1;
        while(1)
        {
            tmp<<=1;
            length+=tmp;
            if(length>=n)return length;
        }
    }
}

void binarySerach(longs lpos,longs rpos,longs value)
{
    longs mid = ((lpos+rpos)>>1);
    if(lpos>r||rpos<l||lpos>rpos)return;
    if(mid<l)binarySerach(mid+1,rpos,value>>1);
    else if(mid>r)binarySerach(lpos,mid-1,value>>1);
    else
    {
        ans+=(value&1);
        binarySerach(lpos,mid-1,value>>1);
        binarySerach(mid+1,rpos,value>>1);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>l>>r;
    arrayLength = calculator(n);
    binarySerach(1,arrayLength,n);
    cout<<ans;

    return 0;
}