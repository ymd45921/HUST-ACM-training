// TLE 26 38
#include <bits/stdc++.h>

using namespace std;
typedef long long longs;

int n, state;
int str[1050];
bool msg[1050];
char ch[1050];

inline void initArray()
{
    srand(time(nullptr));
    for (int i = 0; i < n; ++ i)
        str[i] = (rand()&1);
}

inline void printArray()
{
    for (int i = 0; i < n; ++ i)
        ch[i] = str[i] + '0';
    cout << ch << endl;
}

inline void inverseArray()
{
    for (int i = 0; i < n; ++ i)
        str[i] ^= 1;
}

inline void applyArray()
{
    for (int i = 0; i < n; ++ i)
        str[i] ^= msg[i];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

//    memset(msg, 0, sizeof msg);
    cin >> n;
    ch[n] = 0;
    if (n == 1)
    {
        cout << 1 << endl;
        cin >> state;
        if (!state)
        {
            cout << 0 << endl;
            cin >> state;
        }
        return 0;
    }
    do
    {
        initArray();
        printArray();
        cin >> state;
    } while (!state);

    if (state == n) return 0;
    msg[0] = true; str[0] ^= 1;
    for (int i = 1; i < n; ++ i)
    {
        str[i] ^= 1;
        printArray();
        cin >> state;
        msg[i] = !state;
        str[i] ^= 1;
    }
    str[0] ^= 1;
    applyArray();
    printArray();
    cin >> state;
    if (state == n) return 0;
    inverseArray();
    printArray();
    cin >> state;
    if (state == n) return 0;
    str[0] ^= 1;
    printArray();
    cin >> state;
    if (state == n) return 0;
    inverseArray();
    printArray();
    cin >> state;

    return 0;
}