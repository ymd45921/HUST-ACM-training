#include <bits/stdc++.h>

using namespace std;
//typedef long long longs;

int n, state;
bool msg[1050];
string ch;

inline void initArray()
{
    ch = "";
    for (int i = 0; i < n; ++ i)
        ch.push_back((rand()&1)+'0');
}

inline void printArray()
{
    cout << ch << endl;
}

inline void inverseArray()
{
    for (int i = 0; i < n; ++ i)
        ch[i] = (ch[i]=='0') ? '1' : '0';
}

inline void applyArray()
{
    for (int i = 0; i < n; ++ i)
        if (msg[i]) ch[i] = (ch[i]=='0') ? '1' : '0';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    srand(time(0));
    if (n == 1)
    {
        cout << 1 << endl;
        cin >> state;
        if (state == n) return 0;
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
    msg[0] = true; ch[0] = (ch[0]=='0') ? '1' : '0';
    for (int i = 1; i < n; ++ i)
    {
        ch[i] = (ch[i]=='0') ? '1' : '0';
        printArray();
        cin >> state;
        msg[i] = !state;
        ch[i] = (ch[i]=='0') ? '1' : '0';
    }
    ch[0] = (ch[0]=='0') ? '1' : '0';
    applyArray();
    printArray();
    cin >> state;
    if (state == n) return 0;
    inverseArray();
    printArray();
    cin >> state;
    if (state == n) return 0;
    ch[0] = (ch[0]=='0') ? '1' : '0';
    printArray();
    cin >> state;
    if (state == n) return 0;
    inverseArray();
    printArray();
    cin >> state;

    return 0;
}