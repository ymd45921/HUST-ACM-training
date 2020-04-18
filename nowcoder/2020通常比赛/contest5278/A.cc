/**
 *
 * 这还吃罚时，离谱
 */
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
using longs = long long;
using longd = long double;
using ulongs = unsigned long long;

const int inf = 0x3f3f3f3f;
const longs INF = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-8;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int in[4];
    for (int i = 0; i < 4; ++ i)
        cin >> in[i];
    sort(in,in+4);
    cout << abs(in[0]+in[3]-in[1]-in[2]) << endl;
    
    return 0;
}