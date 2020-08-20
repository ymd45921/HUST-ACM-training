/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <bitset>
#include <array>
#include <map>

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

const int N = 30;
array<bitset<N>, N> g;
void clear() {for (auto &ii : g) ii.reset();}
int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[] = {1, 1, 0, -1, -1, -1, 0, 1};
int count(int x, int y)
{
    int ret = 0;
    for (int i = 0; i < 8; ++ i)
        if (g[x + dx[i]][y + dy[i]]) ++ ret;
    return ret;
}

pair<int ,pair<int, int>> tbl[] =
        {
                {0,  {1, 1}},
                {1,  {2, 1}},
                {2,  {3, 1}},
                {3,  {4, 1}},
                {4,  {5, 1}},
                {5,  {6, 1}},
                {6,  {7, 1}},
                {7,  {8, 1}},
                {8,  {9, 1}},
                {9,  {10, 1}},
                {10,  {11, 1}},
                {11,  {12, 1}},
                {12,  {13, 1}},
                {13,  {14, 1}},
                {14,  {15, 1}},
                {15,  {16, 1}},
                {16,  {17, 1}},
                {17,  {18, 1}},
                {18,  {19, 1}},
                {19,  {20, 1}},
                {20,  {21, 1}},
                {21,  {22, 1}},
                {22,  {23, 1}},
                {23,  {24, 1}},
                {24,  {25, 1}},
                {25,  {9, 2}},
                {27,  {6, 3}},
                {28,  {10, 2}},
                {31,  {11, 2}},
                {32,  {7, 3}},
                {34,  {12, 2}},
                {37,  {13, 2}},
                {38,  {6, 4}},
                {40,  {14, 2}},
                {42,  {9, 3}},
                {43,  {15, 2}},
                {45,  {7, 4}},
                {46,  {16, 2}},
                {47,  {10, 3}},
                {49,  {17, 2}},
                {52,  {18, 2}},
                {55,  {19, 2}},
                {57,  {12, 3}},
                {58,  {20, 2}},
                {59,  {9, 4}},
                {60,  {6, 6}},
                {61,  {21, 2}},
                {62,  {13, 3}},
                {64,  {22, 2}},
                {66,  {10, 4}},
                {67,  {23, 2}},
                {70,  {24, 2}},
                {71,  {7, 6}},
                {72,  {15, 3}},
                {73,  {25, 2}},
                {76,  {9, 5}},
                {77,  {16, 3}},
                {80,  {12, 4}},
                {82,  {17, 3}},
                {84,  {7, 7}},
                {85,  {10, 5}},
                {87,  {18, 3}},
                {92,  {19, 3}},
                {93,  {9, 6}},
                {94,  {14, 4}},
                {97,  {20, 3}},
                {101,  {15, 4}},
                {102,  {21, 3}},
                {103,  {12, 5}},
                {104,  {10, 6}},
                {107,  {22, 3}},
                {108,  {16, 4}},
                {110,  {9, 7}},
                {112,  {23, 3}},
                {115,  {17, 4}},
                {117,  {24, 3}},
                {121,  {14, 5}},
                {122,  {25, 3}},
                {123,  {10, 7}},
                {126,  {12, 6}},
                {127,  {9, 8}},
                {129,  {19, 4}},
                {130,  {15, 5}},
                {136,  {20, 4}},
                {137,  {13, 6}},
                {139,  {16, 5}},
                {142,  {10, 8}},
                {143,  {21, 4}},
                {144,  {9, 9}},
                {148,  {17, 5}},
                {149,  {12, 7}},
                {150,  {22, 4}},
                {157,  {23, 4}},
                {159,  {15, 6}},
                {161,  {10, 9}},
                {162,  {13, 7}},
                {164,  {24, 4}},
                {166,  {19, 5}},
                {170,  {16, 6}},
                {171,  {25, 4}},
                {172,  {12, 8}},
                {175,  {20, 5}},
                {178,  {11, 9}},
                {180,  {10, 10}},
                {181,  {17, 6}},
                {184,  {21, 5}},
                {187,  {13, 8}},
                {188,  {15, 7}},
                {192,  {18, 6}},
                {193,  {22, 5}},
                {195,  {12, 9}},
                {199,  {11, 10}},
                {201,  {16, 7}},
                {202,  {23, 5}},
                {203,  {19, 6}},
                {211,  {24, 5}},
                {212,  {13, 9}},
                {214,  {20, 6}},
                {217,  {15, 8}},
                {218,  {12, 10}},
                {220,  {25, 5}},
                {225,  {21, 6}},
                {227,  {18, 7}},
                {229,  {14, 9}},
                {232,  {16, 8}},
                {236,  {22, 6}},
                {237,  {13, 10}},
                {240,  {19, 7}},
                {241,  {12, 11}},
                {246,  {15, 9}},
                {247,  {23, 6}},
                {253,  {20, 7}},
                {256,  {14, 10}},
                {258,  {24, 6}},
                {262,  {18, 8}},
                {263,  {16, 9}},
                {264,  {12, 12}},
                {266,  {21, 7}},
                {269,  {25, 6}},
                {275,  {15, 10}},
                {277,  {19, 8}},
                {279,  {22, 7}},
                {280,  {17, 9}},
                {283,  {14, 11}},
                {287,  {13, 12}},
                {292,  {23, 7}},
                {294,  {16, 10}},
                {297,  {18, 9}},
                {304,  {15, 11}},
                {305,  {24, 7}},
                {307,  {21, 8}},
                {310,  {14, 12}},
                {312,  {13, 13}},
                {313,  {17, 10}},
                {314,  {19, 9}},
                {318,  {25, 7}},
                {322,  {22, 8}},
                {325,  {16, 11}},
                {331,  {20, 9}},
                {332,  {18, 10}},
                {333,  {15, 12}},
                {337,  {23, 8}},
                {346,  {17, 11}},
                {348,  {21, 9}},
                {351,  {19, 10}},
                {352,  {24, 8}},
                {356,  {16, 12}},
                {362,  {15, 13}},
                {364,  {14, 14}},
                {365,  {22, 9}},
                {367,  {25, 8}},
                {370,  {20, 10}},
                {379,  {17, 12}},
                {382,  {23, 9}},
                {387,  {16, 13}},
                {388,  {19, 11}},
                {389,  {21, 10}},
                {391,  {15, 14}},
                {399,  {24, 9}},
                {402,  {18, 12}},
                {408,  {22, 10}},
                {409,  {20, 11}},
                {412,  {17, 13}},
                {416,  {25, 9}},
                {418,  {16, 14}},
                {420,  {15, 15}},
                {425,  {19, 12}},
                {427,  {23, 10}},
                {430,  {21, 11}},
                {437,  {18, 13}},
                {445,  {17, 14}},
                {446,  {24, 10}},
                {448,  {20, 12}},
                {449,  {16, 15}},
                {451,  {22, 11}},
                {462,  {19, 13}},
                {465,  {25, 10}},
                {471,  {21, 12}},
                {472,  {23, 11}},
                {478,  {17, 15}},
                {480,  {16, 16}},
                {487,  {20, 13}},
                {493,  {24, 11}},
                {494,  {22, 12}},
                {499,  {19, 14}},
                {507,  {18, 15}},
                {511,  {17, 16}},
                {512,  {21, 13}},
                {514,  {25, 11}},
                {517,  {23, 12}},
                {526,  {20, 14}},
                {536,  {19, 15}},
                {537,  {22, 13}},
                {540,  {24, 12}},
                {542,  {18, 16}},
                {544,  {17, 17}},
                {553,  {21, 14}},
                {562,  {23, 13}},
                {563,  {25, 12}},
                {565,  {20, 15}},
                {573,  {19, 16}},
                {577,  {18, 17}},
                {580,  {22, 14}},
                {587,  {24, 13}},
                {594,  {21, 15}},
                {604,  {20, 16}},
                {607,  {23, 14}},
                {610,  {19, 17}},
                {612,  {25, 13}},
                {623,  {22, 15}},
                {634,  {24, 14}},
                {635,  {21, 16}},
                {643,  {20, 17}},
                {647,  {19, 18}},
                {652,  {23, 15}},
                {661,  {25, 14}},
                {666,  {22, 16}},
                {676,  {21, 17}},
                {681,  {24, 15}},
                {682,  {20, 18}},
                {684,  {19, 19}},
                {697,  {23, 16}},
                {709,  {22, 17}},
                {710,  {25, 15}},
                {717,  {21, 18}},
                {721,  {20, 19}},
                {728,  {24, 16}},
                {742,  {23, 17}},
                {752,  {22, 18}},
                {758,  {21, 19}},
                {759,  {25, 16}},
                {760,  {20, 20}},
                {775,  {24, 17}},
                {787,  {23, 18}},
                {795,  {22, 19}},
                {799,  {21, 20}},
                {808,  {25, 17}},
                {822,  {24, 18}},
                {832,  {23, 19}},
                {838,  {22, 20}},
                {840,  {21, 21}},
                {857,  {25, 18}},
                {869,  {24, 19}},
                {877,  {23, 20}},
                {881,  {22, 21}},
                {906,  {25, 19}},
                {916,  {24, 20}},
                {922,  {23, 21}},
                {924,  {22, 22}},
                {955,  {25, 20}},
                {963,  {24, 21}},
                {967,  {23, 22}},
                {1004,  {25, 21}},
                {1010,  {24, 22}},
                {1012,  {23, 23}},
                {1053,  {25, 22}},
                {1057,  {24, 23}},
                {1102,  {25, 23}},
                {1104,  {24, 24}},
                {1151,  {25, 24}},
                {1200,  {25, 25}}
        };
int msk[30][30];

int main()
{
    ios::sync_with_stdio(false);

//    for (int i = 1; i < 272; ++ i)
//    {
//        if (tbl[i].first > 1034) break;
//        auto dd = tbl[i].first - tbl[i - 1].first;
//        auto &ans = tbl[i].second;
//        auto mm = (ans.first + ans.second - 2) * 2;
//        mm -= (ans.first % 2 && ans.second % 2) * 2 + 2;
//        cout << (dd <= mm ) << endl;
//    }

    map<int, pair<int, int>> table;
    for (auto &ii : tbl) table[ii.first] = ii.second;
    for (int i = 0; i < 30; ++ i)
        for (int j = 0; j < 30; ++ j)
            msk[i][j] = (i + j) % 2;

    int t = nextInt();
    while (t --)
    {
        int s = nextInt();
        if (s > 1200) puts("-1");
        clear();
        auto &ii = *table.lower_bound(s);
        if (ii.first == s)
        {
            printf("%d %d\n", ii.second.first, ii.second.second);
            for (int i = 1; i <= ii.second.first; ++ i)
            {
                for (int j = 1; j <= ii.second.second; ++ j)
                    putchar(msk[i][j] ? 'X' : '.');
                putchar('\n');
            }
        }
        else
        {
            auto dd = ii.first - s;
            for (int i = 1; i <= ii.second.first; ++ i)
                for (int j = 1; j <= ii.second.second; ++ j)
                    g[i][j] = msk[i][j];
            for (int j = 1; dd && j <= ii.second.second; j += 2)
                if (!g[1][j]) g[1][j] = true, -- dd;
            for (int i = 3; dd && i <= ii.second.first; i += 2)
                if (!g[i][1]) g[i][1] = true, -- dd;
            int j = msk[ii.second.first][1] ? 2 : 1,
                i = msk[1][ii.second.second] ? 2 : 1;
            while (dd && j <= ii.second.second)
            {
                if (g[ii.second.first][j])
                {
                    j += 2;
                    continue;
                }
                if (count(ii.second.first, j) < 4)
                    g[ii.second.first][j] = true, -- dd;
                j += 2;
            }
            while (dd && i <= ii.second.first)
            {
                if (g[i][ii.second.second])
                {
                    i += 2;
                    continue;
                }
                if (count(i, ii.second.second) < 4)
                    g[i][ii.second.second] = true, -- dd;
                i += 2;
            }
            if (dd) {puts("-1"); continue;}
            printf("%d %d\n", ii.second.first, ii.second.second);
            for (int x = 1; x <= ii.second.first; ++ x)
            {
                for (int y = 1; y <= ii.second.second; ++ y)
                    putchar(g[x][y] ? 'X' : '.');
                putchar('\n');
            }
        }
    }

    return 0;
}