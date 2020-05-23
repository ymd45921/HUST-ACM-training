/**
 *
 */
#include <iostream>
#include <algorithm>
#include <deque>
#include <cstring>

using namespace std;
using longs = long long;

constexpr int inf = 0x3f3f3f3f;
constexpr double eps = 1e-8;

const char ask[] = "? ";
const char chk[] = "! ";

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int length, response;
    cin >> length;
    int max0 = 0, max1 = 0;
    bool has0 = false, has1 = false;
    bool f0t1 = false, f1t0 = false;
    cout << ask << 0 << endl;
    cin >> response; has0 = response;
    cout << ask << 1 << endl;
    cin >> response; has1 = response;
    max0 = has0; max1 = has1;
    if (has0 && !has1)
    {
        cout << chk;
        for (int i = 0; i < length; ++ i)
            cout << 0;
        cout << endl;
        exit(0);
    }
    else if (!has0 && has1)
    {
        cout << chk;
        for (int i = 0; i < length; ++ i)
            cout << 1;
        cout << endl;
        exit(0);
    }
    else
    {
        cout << ask << "01" << endl;
        cin >> response;
        f0t1 = response;
        cout << ask << "10" << endl;
        cin >> response;
        f1t0 = response;
    }

    int l = 2, r = length;
    if (has0)
    {
        l = 2, r = length;
        while (l <= r)
        {
            auto mid = l + r >> 1;
            cout << ask;
            for (int j = 0; j < mid; ++ j) cout << 0;
            cout << endl; cin >> response;
            if (response)
            {
                max0 = mid;
                l = mid + 1;
            }
            else r = mid - 1;
        }
    }
    if (has1)
    {
        l = 2, r = length;
        while (l <= r)
        {
            auto mid = l + r >> 1;
            cout << ask;
            for (int j = 0; j < mid; ++ j) cout << 1;
            cout << endl; cin >> response;
            if (response)
            {
                max1 = mid;
                l = mid + 1;
            }
            else r = mid - 1;
        }
    }

    int head = -1, tail = -1;
    if (f0t1 && !f1t0)
    {
        cout << chk;
        for (int i = 0; i < max0; ++ i) cout << 0;
        for (int i = max0; i < length; ++ i) cout << 1;
        cout << endl;
        exit(0);
    }
    else if (f1t0 && !f0t1)
    {
        cout << chk;
        for (int i = 0; i < max1; ++ i) cout << 1;
        for (int i = max1; i < length; ++ i) cout << 0;
        cout << endl;
        exit(0);
    }
    else
    {
        cout << ask << 1;
        for (int i = 0; i < max0; ++ i)
            cout << 0;
        cout << endl; cin >> response;
        if (!response) head = 0;

        cout << ask;
        for (int i = 0; i < max0; ++ i)
            cout << 0;
        cout << 1 << endl; cin >> response;
        if (!response) tail = 0;

        cout << ask << 0;
        for (int i = 0; i < max1; ++ i)
            cout << 1;
        cout << endl;  cin >> response;
        if (!response) head = 1;

        cout << ask;
        for (int i = 0; i < max1; ++ i)
            cout << 1;
        cout << 0 << endl; cin >> response;
        if (!response) tail = 1;
    }

    auto residue = length;
    residue -= ~head ? (head ? max1 : max0) : 0;
    residue -= ~tail ? (tail ? max1 : max0) : 0;
    if (residue == 1)
    {
        
    }
    else if (residue == 2)
    {
        if (~head)
        {
            cout << chk;
            auto maxHead = head ? max1 : max0;
            auto maxTail = length - maxHead - 2;
            for (int i = 0; i < maxHead; ++ i) cout << head;
            cout << !head << head;
            for (int i = 0; i < maxTail; ++ i) cout << !head;
            cout << endl;
        }
        else if (~tail)
        {
            cout << chk;
            auto maxTail = tail ? max1 : max0;
            auto maxHead = length - maxTail - 1;
            for (int i = 0; i < maxHead; ++ i) cout << !tail;
            cout << tail << !tail;
            for (int i = 0; i < maxTail; ++ i) cout << tail;
            cout << endl;
        }
        else
        {
            
        }
    }
    else
    {
        
    }

    return 0;
}