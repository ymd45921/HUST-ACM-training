#include <iostream>
#define mylogx

using namespace std;
typedef long long longs;

longs n,l,r;
int son[55];
int num[55];
int _length;

bool treed = false;
int last_treed;
int tmp,cur;
longs l_pref=0,r_pref=0;
int tl,tr;
int _lbound;

int _findPosition;

inline int findPosition(int index)
{
    for(int i=_length-1;i>=0;--i)
        if(index < num[i])return _findPosition=i+1;
    return _findPosition=0;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>l>>r;
    tmp = son[0] = n;
    cur = 1;
    while(tmp) son[cur++] = (tmp>>=1);
    _length = cur - 1;
    tmp = 1; num[--cur] = tmp-1;
    while(cur>0) num[--cur] = (tmp<<=1)-1;
#ifdef mylog
    cout<<"son[] : ";
    for(int i = 0;i<=_length;++i)cout<<son[i]<<' ';
    cout<<"\nnum[] : ";
    for(int i = 0;i<=_length;++i)cout<<num[i]<<' ';
    cout<<endl;
#endif
    tl=l;tr=r;
    while (tl)
    {
        l_pref+=son[findPosition(tl)];
        tl-=num[_findPosition];
        _lbound = 1;
        if(tl>0)
        {
            --tl;
            _lbound = (son[_findPosition-1]&1);
            l_pref += _lbound;
        }
    }
    while (tr)
    {
        r_pref+=son[findPosition(tr)];
        tr-=num[_findPosition];
        if(tr>0)
        {
            --tr;
            r_pref += (son[_findPosition-1]&1);
        }
    }
    cout<<r_pref-l_pref+_lbound;

    return 0;
}