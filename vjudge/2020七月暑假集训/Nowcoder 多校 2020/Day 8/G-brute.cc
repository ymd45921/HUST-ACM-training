/**
 * 暴力做法
 * 
 * 似乎写错了
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <vector>
#include <functional>

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

const int N = 300;
char s[5][20];
uint map[N], match[N], cnt = 0;
vector<int> deck;

const static uint msk[] = {3, 12, 48, 192};
// [*] => 0; [...] => 1, 2, 3;
// color | shading | shape | number
uint deckHash()
{
    auto ret = 0;
    auto l1 = strlen(s[0]), l2 = strlen(s[1]), l3 = strlen(s[2]), l4 = strlen(s[3]);
    if (l1 == 5) ret += 3;                              // three
    else if (l1 == 3) ret += (s[0][0] == 'o' ? 1 : 2);  // one : two
    if (l2 == 7) ret += 1 * 4;                          // diamond
    else if (l2 == 8) ret += 2 * 4;                     // squiggle
    else if (l2 == 4) ret += 3 * 4;                     // oval
    if (l3 == 7) ret += 1 * 16;                         // striped
    else if (l3 == 5) ret += 2 * 16;                    // solid
    else if (l3 == 4) ret += 3 * 16;                    // open
    if (l4 == 6) ret += 1 * 64;                         // purple
    else if (l4 == 5) ret += 2 * 64;                    // green
    else if (l4 == 3) ret += 3 * 64;                    // red
    return ret;
}

uint nextDeck(uint a, uint b)
{
    auto ret = 0;
    for (uint i = 0; i < 4; ++ i)
    {
        const auto off = i << 1u;
        auto aa = (a & msk[i]) >> off, bb = (b & msk[i]) >> off;
        if (!aa || !bb);
        else if (aa == bb) ret += aa << off;
        else ret += (6 - aa - bb) << off;
    }
    return ret;
}

bool isMatch(uint nxt, uint c)
{
    for (unsigned int i : msk)
    {
        if ((nxt & i) || (c & i)) continue;
        else if ((nxt & i) ^ (c & i)) return false;
    }
    return true;
}

bool isWild(uint card)
{
    for (auto m : msk) if (!(card & m)) return true;
    return false;
}

void nextCard()
{
    int ch = getchar(), cur = 0;
    for (int i = 0; i < 4; ++ i)
    {
        while (ch != '[') ch = getchar();
        cur = 0, ch = getchar();
        while (ch != ']')
        {
            s[i][cur ++] = (char)ch;
            ch = getchar();
        }
        s[i][cur] = 0;
    }
}

void logCard(uint card)
{
    fprintf(stderr, "[%u]: %u | %u | %u | %u\n",
            card,
            (card & msk[3]) >> (3u << 1u),
            (card & msk[2]) >> (2u << 1u),
            (card & msk[1]) >> (1u << 1u),
            (card & msk[0]) >> (0u << 1u));
}

int main()
{
    ios::sync_with_stdio(false);

    const int t = nextInt();
    for (int cases = 1; cases <= t; ++ cases)
    {
        memset(map, 0, sizeof map);
        deck.clear();
        int n = nextInt();
        for (int i = 1; i <= n; ++ i)
        {
            nextCard();
            const auto card = deckHash();
            map[card] = i, deck.push_back(card);
        }
        auto a = 0, b = 0, c = 0;
        for (int i = 0; i < n; ++ i)
        {
            for (int j = i + 1; j < n; ++ j)
            {
                auto nxt = nextDeck(deck[i], deck[j]);
                logCard(nxt);
                for (int k = j + 1; k < n; ++ k)
                    if (isMatch(nxt, deck[k]))
                    {
                        logCard(deck[k]);
                        a = map[deck[i]];
                        b = map[deck[j]];
                        c = map[deck[k]];
                        break;
                    }
                if (a && b && c) break;
            }
            if (a && b && c) break;
        }
        printf("Case #%d: ", cases);
        if (a && b && c) printf("%d %d %d\n", a, b, c);
        else printf("-1\n");
    }

    return 0;
}