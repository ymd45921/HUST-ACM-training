#include <cstdio>
#include <cstring>

using namespace std;

const int toSelect[] = {4, 8, 15, 16, 23 ,42};
const int power[] = {32,60,64,92,168,120,128,184,336,240,345,630,368,672,966};
const int mem1[] = {0,0,0,0,0,1,1,1,1,2,2,2,3,3,4};
const int mem2[] = {1,2,3,4,5,2,3,4,5,3,4,5,4,5,5};
const char*question[] = {"? 1 2","? 2 3","? 4 5","? 5 6"};
int out[6];
int select[6];
int in[4],res;
int length = 15;
int number[2] = {-1,-1};

inline int found(int in)
{
    for(int i=0;i<15;++i)if(power[i]==in)return i;
}

int main()
{
    memset(select,0,sizeof(select));
    for(int i=0;i<4;++i)
    {
        printf("%s\n",question[i]);
        fflush(stdout);
        scanf("%d",&in[i]);
        res = found(in[i]);
        select[mem1[res]]+=1;
        select[mem2[res]]+=1;
        if(i&1)
        {
            for(int j=0;j<6;++j)
            {
                if(j!=number[0]&&select[j]==2)
                {
                    number[i>>1]=j;
                    break;
                }
            }
        }
    }

    out[1] = toSelect[number[0]];
    out[4] = toSelect[number[1]];
    out[0] = in[0]/out[1];
    out[2] = in[1]/out[1];
    out[3] = in[2]/out[4];
    out[5] = in[3]/out[4];

    printf("!");
    for(int i=0;i<6;++i)printf(" %d",out[i]);
    printf("\n");
    fflush(stdout);

    return 0;
}