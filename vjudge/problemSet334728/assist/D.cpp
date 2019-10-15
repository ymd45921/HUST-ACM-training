#include <iostream>
#include <stdio.h>

using namespace std;

const int toSelect[] = {4, 8, 15, 16, 23 ,42};

int main()
{
    for(int i=0;i<6;++i)
    {
        for(int j=0;j<6;++j)
            printf("%-6d",toSelect[i]*toSelect[j]);
        printf("\n");
    }
}