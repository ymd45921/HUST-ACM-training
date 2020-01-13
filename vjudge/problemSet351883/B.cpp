/**
 *
 */
#include <iostream>
#include <vector>

#define max(x,y) (x>y?x:y)
#define PureAB(x) ((x).ab-(x).abc)
#define PureAC(x) ((x).ac-(x).abc)
#define PureBC(x) ((x).bc-(x).abc)
#define Pure_A(x) ((x).a-(x).ab-(x).ac+(x).abc)
#define Pure_B(x) ((x).b-(x).ab-(x).bc+(x).abc)
#define Pure_C(x) ((x).c-(x).ac-(x).bc+(x).abc)

//#define mydebug

using namespace std;
struct data
{
    int a,b,c,ab,bc,ac,abc;
};

int T,N[105]{0};
data input;
vector<data> database[105];
int ans[105]{0};

inline int sum(const data& x)
{
    return Pure_C(x)+Pure_B(x)+Pure_A(x)+PureAB(x)+PureAC(x)+PureBC(x)+x.abc;
}

inline int solution(int i)
{
    int ans = 0;
    for(auto iter : database[i])
    {
#ifdef mydebug
    cout<<"A="<<Pure_A(iter)<<" B="<<Pure_B(iter)
        <<" C="<<Pure_C(iter)<<" AB="<<PureAB(iter)
        <<" BC="<<PureBC(iter)<<" AC="<<PureAC(iter)
        <<" ABC="<<iter.abc<<endl;
#endif
        if (PureAB(iter)<0 || PureBC(iter)<0 ||
            PureAC(iter)<0 || Pure_C(iter)<0 ||
            Pure_B(iter)<0 || Pure_A(iter)<0)
            continue;
        ans = max(ans,sum(iter));
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>T;
    for(int i=0;i<T;++i)
    {
        cin>>N[i];
        for(int j=0;j<N[i];++j)
        {
            cin >> input.a >> input.b >> input.c
                >> input.ab >> input.bc >> input.ac
                >> input.abc;
            database[i].push_back(input);
        }
        ans[i] = solution(i);
    }


    for(int i=0;i<T;++i)
        cout<<ans[i]<<endl;
    return 0;
}