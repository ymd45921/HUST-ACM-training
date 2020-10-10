/**
 *
 * 还是我自己想的太简单了，正是比赛这样可不行啊（
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

namespace In
{
    template <class T>
    inline void read(T &x)
    {
        x = 0;
        int ch = getchar(), f = 0;
        while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
        x = f ? -x : x;
    }

    template <class T, class... Ts>
    inline void read(T &x, Ts &... y)
    {return read(x), read(y...);}
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    string s;
    cin >> s;
    int cnt[26], ty = 0, xx = 0, ii = 0;
    auto n = s.length() / 2;
    memset(cnt, 0, sizeof cnt);
    for (auto i : s)
        ++ cnt[i - 'a'];
    auto upd = [&](int i) -> void
    {if (cnt[i] > xx) xx = cnt[i], ii = i;};    
    for (int i = 0; i < 26; ++ i)
        (cnt[i] && ++ ty), upd(i);
    if (xx <= n)
    {
        cout << "YES" << endl;
        for (int i = 0; i < 26; ++ i)
            cout << string(cnt[i], char(i + 'a'));
        cout << endl;    
    }
    else if (ty == 1) cout << "NO" << endl; 
    else if (ty == 2)
        if (n * 2 - xx <= 2) cout << "NO" << endl;
        else
        {
            cout << "YES" << endl << string(n, char(ii + 'a'));
            auto sec = 0;
            for (int i = 0; i < 26; ++ i)
                if (i != ii && cnt[i]) {sec = i; break;}
            cout << string(cnt[sec] - 1, char(sec + 'a')) 
                 << string(cnt[ii] - n, char(ii + 'a'))
                 << char(sec + 'a') << endl;
        }   
    else 
    {
        cout << "YES" << endl << string(n, char(ii + 'a'));
        auto nxt = 0;
        for (int i = 0; i < 26; ++ i)
            if (i != ii && cnt[i]) {nxt = i, -- cnt[i]; break;}
        for (int i = 0; i < 26; ++ i)
            if (i != ii && cnt[i]) 
                cout << string(cnt[i], char(i + 'a')); 
        cout << string(cnt[ii] - n, char(ii + 'a')) << char(nxt + 'a') << endl;        
    }   

    return 0;
}

