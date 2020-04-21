///**
// *
// */
//#include <iostream>
//#include <map>
//#include <cstring>
//#include <algorithm>
//
//using namespace std;
//using longs = long long;
//using longd = long double;
//using ulongs = unsigned long long;
//
//const int N = 20005;
//const int inf = 0x3f3f3f3f;
//const longs INF = 0x3f3f3f3f3f3f3f3f;
//const double eps = 1e-8;
//const char ja[] = "ora";
//const char da[] = "muda";
//const char sa[] = "zawaluduo";
//const int jal = strlen(ja);
//const int dal = strlen(da);
//const int sal = strlen(sa);
//const char cndd[] = "Kono Dio da";
//const char hjk[] = "Hinnjaku";
//const char wry[] = "Wryyyyy";
//
//struct item
//{
//    bool ds, js, da, ja;
//    item() {ds=js=da=ja=false;}
//};
//
////char jj[N], dd[N];
//string jj, dd;
//int jh, dh, n;
//
////namespace KMPja
////{
////    int Next[1000010];
////    int length = strlen(ja);
////    const char *s = ja;
////
////    inline void buildNextArray()
////    {
////        Next[0] = -1;
////        int i = 0, j = -1;
////        while(i < length)
////        {
////            if(-1 == j || s[i] == s[j])
////                Next[++ i] = ++ j;
////            else j = Next[j];
////        }
////    }
////
////    char* find(char* ss)
////    {
////        int ps = 0, pp = 0, len = strlen(ss);
////        while (ps < len)
////        {
////            if (!~pp || s[pp] == ss[ps]) ++ pp, ++ ps;
////            else pp = Next[pp];
////            if (pp == length) return ss + (ps - length);
////        }
////        return NULL;
////    }
////}
////
////namespace KMPda
////{
////    int Next[1000010];
////    int length = strlen(da);
////    const char *s = da;
////
////    inline void buildNextArray()
////    {
////        Next[0] = -1;
////        int i = 0, j = -1;
////        while(i < length)
////        {
////            if(-1 == j || s[i] == s[j])
////                Next[++ i] = ++ j;
////            else j = Next[j];
////        }
////    }
////
////    char* find(char* ss)
////    {
////        int ps = 0, pp = 0, len = strlen(ss);
////        while (ps < len)
////        {
////            if (!~pp || s[pp] == ss[ps]) ++ pp, ++ ps;
////            else pp = Next[pp];
////            if (pp == length) return ss + (ps - length);
////        }
////        return NULL;
////    }
////}
////
////namespace KMPsa
////{
////    int Next[1000010];
////    int length = strlen(sa);
////    const char *s = sa;
////
////    inline void buildNextArray()
////    {
////        Next[0] = -1;
////        int i = 0, j = -1;
////        while(i < length)
////        {
////            if(-1 == j || s[i] == s[j])
////                Next[++ i] = ++ j;
////            else j = Next[j];
////        }
////    }
////
////    char* find(char* ss)
////    {
////        int ps = 0, pp = 0, len = strlen(ss);
////        while (ps < len)
////        {
////            if (!~pp || s[pp] == ss[ps]) ++ pp, ++ ps;
////            else pp = Next[pp];
////            if (pp == length) return ss + (ps - length);
////        }
////        return NULL;
////    }
////}
//
//int main()
//{
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
//
////    KMPja::buildNextArray();
////    KMPsa::buildNextArray();
////    KMPda::buildNextArray();
////
////    while (1)
////    {
////        char ss[N];
////        cin >> ss;
////        auto cc = KMPja::find(ss);
////        while (cc)
////        {
////            cerr << cc-ss << ',' << cc-ss+jal-1 << endl;
////            cc += jal;
////            cc = KMPja::find(cc);
////        }
////        cerr << "end" << endl << endl;
////    }
//
//
//    int t; cin >> t;
//    map<int,item> mm;
//    while (t --)
//    {
//        int nn, hh;
//        cin >> nn >> hh;
//        jh = dh = hh;
//        cin >> jj >> dd;
//
//        int cc = 0;
//        while (cc != string::npos)
//        {
//            cc = jj.find(ja, cc);
//            if (cc != string::npos)
//            {
//                int xx = cc + jal - 1;
//                mm[xx].ja = true;
//                cc += jal;
//            }
//        }
//
//        cc = 0;
//        while (cc != string::npos)
//        {
//            cc = jj.find(sa, cc);
//            if (cc != string::npos)
//            {
//                int xx = cc + sal - 1;
//                mm[xx].js = true;
//                cc += sal;
//            }
//        }
//
//        cc = 0;
//        while (cc != string::npos)
//        {
//            cc = dd.find(da, cc);
//            if (cc != string::npos)
//            {
//                int xx = cc + dal - 1;
//                mm[xx].da = true;
//                cc += dal;
//            }
//        }
//
//        cc = 0;
//        while (cc != string::npos)
//        {
//            cc = dd.find(sa, cc);
//            if (cc != string::npos)
//            {
//                int xx = cc + sal - 1;
//                mm[xx].ds = true;
//                cc += sal;
//            }
//        }
//
//        for (auto ii : mm)
//        {
//            if (ii.second.ds)
//            {
//                jh = 0;
//                ii.second.ja = false;
//                ii.second.js = false;
//                break;
//            }
//            else if (ii.second.js)
//            {
//                dh = 0;
//                ii.second.da = false;
//                ii.second.ds = false;
//                break;
//            }
//
//            if (ii.second.ja) -- dh;
//            if (ii.second.da) -- jh;
//            if (jh <= 0 || dh <= 0) break;
//        }
//        if (jh <= 0 || dh <= 0)
//        {
//            if (jh <= 0 && dh <= 0) cout << cndd << endl;
//            cout << (jh > 0 ? wry : hjk) << endl;
//        }
//        else if (jh == dh) cout << cndd << endl;
//        else cout << (jh > dh ? wry : hjk) << endl;
//        mm.clear();
//    }
//
//
//    return 0;
//}

/**
 *
 */
#include <iostream>
#include <map>
#include <cstring>
#include <algorithm>

using namespace std;
using longs = long long;
using longd = long double;
using ulongs = unsigned long long;

const int N = 20005;
const int inf = 0x3f3f3f3f;
const longs INF = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-8;
const char ja[] = "ora";
const char da[] = "muda";
const char sa[] = "zawaluduo";
const int jal = strlen(ja);
const int dal = strlen(da);
const int sal = strlen(sa);
const char cndd[] = "Kono Dio da";
const char hjk[] = "Hinnjaku";
const char wry[] = "Wryyyyy";

struct item
{
    bool ds, js, da, ja;
    item() {ds=js=da=ja=false;}
};

char jj[N], dd[N];
int jh, dh, n;

namespace KMPja
{
    int Next[1000010];
    int length = strlen(ja);
    const char *s = ja;

    inline void buildNextArray()
    {
        Next[0] = -1;
        int i = 0, j = -1;
        while(i < length)
        {
            if(-1 == j || s[i] == s[j])
                Next[++ i] = ++ j;
            else j = Next[j];
        }
    }

    char* find(char* ss)
    {
        int ps = 0, pp = 0, len = strlen(ss);
        while (ps < len)
        {
            if (!~pp || s[pp] == ss[ps]) ++ pp, ++ ps;
            else pp = Next[pp];
            if (pp == length) return ss + (ps - length);
        }
        return NULL;
    }
}

namespace KMPda
{
    int Next[1000010];
    int length = strlen(da);
    const char *s = da;

    inline void buildNextArray()
    {
        Next[0] = -1;
        int i = 0, j = -1;
        while(i < length)
        {
            if(-1 == j || s[i] == s[j])
                Next[++ i] = ++ j;
            else j = Next[j];
        }
    }

    char* find(char* ss)
    {
        int ps = 0, pp = 0, len = strlen(ss);
        while (ps < len)
        {
            if (!~pp || s[pp] == ss[ps]) ++ pp, ++ ps;
            else pp = Next[pp];
            if (pp == length) return ss + (ps - length);
        }
        return NULL;
    }
}

namespace KMPsa
{
    int Next[1000010];
    int length = strlen(sa);
    const char *s = sa;

    inline void buildNextArray()
    {
        Next[0] = -1;
        int i = 0, j = -1;
        while(i < length)
        {
            if(-1 == j || s[i] == s[j])
                Next[++ i] = ++ j;
            else j = Next[j];
        }
    }

    char* find(char* ss)
    {
        int ps = 0, pp = 0, len = strlen(ss);
        while (ps < len)
        {
            if (!~pp || s[pp] == ss[ps]) ++ pp, ++ ps;
            else pp = Next[pp];
            if (pp == length) return ss + (ps - length);
        }
        return NULL;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    KMPja::buildNextArray();
    KMPsa::buildNextArray();
    KMPda::buildNextArray();

//    while (1)
//    {
//        char ss[N];
//        cin >> ss;
//        auto cc = KMPja::find(ss);
//        while (cc)
//        {
//            cerr << cc-ss << ',' << cc-ss+jal-1 << endl;
//            cc += jal;
//            cc = KMPja::find(cc);
//        }
//        cerr << "end" << endl << endl;
//    }


    int t; cin >> t;
    map<int,item> mm;
    while (t --)
    {
        int nn, hh;
        cin >> nn >> hh;
        jh = dh = hh;
        cin >> jj >> dd;
        n = strlen(jj);

        int iii = 0;
        while(iii < n)
        {
            if((iii + 3 <= n) && strncmp(jj + iii, ja, 3) == 0)
            {
                mm[iii + 2].ja = true;
                iii += 3;
                continue;
            }
            else if((iii + 9 <= n) && strncmp(jj + iii, sa, 9) == 0)
            {
                mm[iii + 8].js = true;
                iii += 9;
                continue;
            }
            ++ iii;
        }
        iii = 0;
        while(iii < n)
        {

            if((iii + 4 <= n) && strncmp(dd + iii, da, 4) == 0)
            {
                mm[iii + 3].da = true;
                iii += 4;
                continue;
            }
            else if((iii + 9 <= n) && strncmp(dd + iii, sa, 9) == 0)
            {
                mm[iii + 8].ds = true;
                iii += 9;
                continue;
            }
            ++ iii;
        }

        int winner = 0;
        for (auto ii : mm)
        {
            if (ii.second.ds)
            {
                jh = 0;
                winner = 1;
                break;
            }
            else if (ii.second.js)
            {
                dh = 0;
                winner = 2;
                break;
            }

            if (ii.second.ja) -- dh;
            if (ii.second.da) -- jh;
            if (jh <= 0 || dh <= 0)
            {
                if (jh <= 0) winner = 1;
                else winner = 2;
                if (jh <= 0 && dh <= 0) winner = 3;
                break;
            }
        }
        if (!winner)
        {
            if ((jh <= 0 && dh <= 0) || jh == dh) winner = 3;
            else if (jh < dh) winner = 1;
            else winner = 2;
        }

        switch (winner)
        {
            case 1: cout << hjk << endl; break;
            case 2: cout << wry << endl; break;
            case 3: cout << cndd << endl; break;
        }
//        if (jh <= 0 || dh <= 0)
//        {
//            if (jh <= 0 && dh <= 0) cout << cndd << endl;
//            cout << (jh > 0 ? wry : hjk) << endl;
//        }
//        else if (jh == dh) cout << cndd << endl;
//        else cout << (jh > dh ? wry : hjk) << endl;
        mm.clear();
    }


    return 0;
}