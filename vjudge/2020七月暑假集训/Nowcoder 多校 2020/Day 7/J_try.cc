/**
 *
 * 虽然说是说这是一个暴力模拟，但是还是需要一些策略
 *
 * 好吧是我太菜了，看了题解依然不知道怎么实现比较合理
 * 只好对着标程敲代码了…… 一个大写的菜字
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <bitset>
#include <cstring>
#include <vector>
#include <unordered_set>
#include <cassert>

#define OBJ(x) (x / 2)
#define FIELD(x) (x % 26)
#define BASE(x) (x / 26 - 2)
#define INDEX(c) ((c - 'A') * 2 + 1)
#define REF(c) (c - 'a')
#define HASH(o, f) (52 + o * 26 + f)
#define PTR(x) (x * 2 + 1)

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

const int N = 205;
using edge = pair<int, int>;
vector<edge> $store, $alloc, $load;
vector<int> $assign[N];

// 0 ~ 52: a, A, b, B, ...
// 52 ~ *: a.a, a.b, a.c, a.d ...
// A.x => same hash index <= a.x
bitset<26> tag[26 * 26 + 52 + 5];
enum type{ALLOC, ASSIGN, STORE, LOAD};      // P = o, P = O, O.f = P, P = O.f
enum symbol{OBJECT, FIELD, POINTER, MEMBER};// o, o.f, P, P.m

symbol getSymbol(const char *s, int &in$)
{
    auto len = strlen(s);
    assert(len == 1 || len == 3);
    assert(isalpha(s[0]));
    if (s[0] >= 'a' && s[0] <= 'z')
    {
        assert(len == 1);
        in$ = (s[0] - 'a') * 2;
        return OBJECT;
    }
    else if (len == 1)
    {
        in$ = INDEX(s[0]);
        return POINTER;
    }
    else
    {
        assert(s[1] == '.' && isalpha(s[2]));
        in$ = 52 + (s[0] - 'A') * 26 + (s[2] - 'a');    // like macro HASH
        return MEMBER;
    }
}

type getExprType(symbol ll, symbol rr)
{
    if (ll == MEMBER) return STORE;
    else if (rr == OBJECT) return ALLOC;
    else if (rr == POINTER) return ASSIGN;
    else return LOAD;
}

void runInfinitely()
{
    unordered_set<int> mq;
    for (auto & e : $alloc)
        tag[e.first][OBJ(e.second)] = true,
        mq.insert(e.first);
    while (!mq.empty())
    {
        while (!mq.empty())
        {
            auto rv = *mq.begin();
            mq.erase(mq.begin());
            for (auto & lv : $assign[rv])
                if ((tag[lv] | tag[rv]) != tag[lv])
                    tag[lv] |= tag[rv], mq.insert(lv);
        }
        for (auto & e : $store)
        {
            auto obj = PTR(BASE(e.first)), f = FIELD(e.first);
            for (auto fd = 0; fd < 26; ++ fd)
                if (tag[obj][fd]) tag[HASH(fd, f)] |= tag[e.second];
        }
        for (auto & e : $load)
        {
            auto ptr = PTR(BASE(e.second)), f = FIELD(e.second);
            for (auto fd = 0; fd < 26; ++ fd)
                if (tag[ptr][fd])
                {
                    auto pos = HASH(fd, f);
                    auto &target = tag[pos];
                    if ((tag[e.first] | target) != tag[e.first])
                        tag[e.first] |= target, mq.insert(e.first);
                }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);

    int n = nextInt();
    char ll[50], rr[50];
    auto process = [&](int &lv$, int &rv$)
    {
        symbol le = getSymbol(ll, lv$), re = getSymbol(rr, rv$);
        return getExprType(le, re);
    };
    while (n --)
    {
        scanf("%s = %s", ll, rr);
        int lll, rrr;
        auto ty = process(lll, rrr);
        switch (ty)
        {
            case ALLOC:
                $alloc.emplace_back(lll, rrr);
                break;
            case ASSIGN:
                $assign[rrr].push_back(lll);
                break;
            case STORE:
                $store.emplace_back(lll, rrr);
                break;
            case LOAD:
                $load.emplace_back(lll, rrr);
                break;
        }
    }
    runInfinitely();
    for (auto ch = 'A'; ch <= 'Z'; ++ ch)
    {
        printf("%c: ", ch);
        for (auto i = 'a'; i <= 'z'; ++ i)
            if (tag[INDEX(ch)][REF(i)]) putchar(i);
        puts("");
    }

    return 0;
}