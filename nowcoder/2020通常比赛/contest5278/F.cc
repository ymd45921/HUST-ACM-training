/**
 *
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

string dateString(int y, int m, int d)
{
    string s;
    if (m == 5) s = "Mother\'s Day: May ";
    else s = "Father\'s Day: June ";
    s.append(to_string(d));
    if (d / 10 == 1) s.append("th, ");
    else if (d % 10 == 1) s.append("st, ");
    else if (d % 10 == 2) s.append("nd, ");
    else if (d % 10 == 3) s.append("rd, ");
    else s.append("th, ");
    s.append(to_string(y));
    return s;
}

namespace Zeller
{
    struct date {int year, month, day; };
    enum weekday {sun = 0, mon, tue, wed, thu, fri, sat};
    typedef int id;

    const int __shift = 0;

    id getZellerId(int y, int m, int d)
    {
        y += 400 * __shift; if (m < 3) -- y, m += 12;
        return 365 *  y + y / 4 - y / 100 + y / 400 + (153 * (m - 3) + 2) / 5 + d - 307;
    }

    date getZellerDate(id zellerId)
    {
        int x = zellerId + 1789995, n, i, j, y, m, d;
        n = 4 * x / 146097; x -= (146097 * n + 3) / 4;
        i = (4000 * (x + 1)) / 1461001; x -= 1461 * i / 4 - 31;
        j = 80 * x / 2447; d = x - 2447 * j / 80; x = j / 11;
        m = j + 2 - 12 * x; y = 100 * (n - 49) + i + x;
        return {y,m,d};
    }
    
    weekday getWeekday(id zellerId)
    {
        return static_cast<weekday>((zellerId + 1) % 7);
    }
    
    weekday getWeekday(int y, int m, int d)
    {
        return getWeekday(getZellerId(y, m, d));
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    using Zeller::getZellerId;
    using Zeller::getWeekday;
    using Zeller::getZellerDate;
    
    auto getMotherDayId = [](int y)
    {
        Zeller::id xx = getZellerId(y, 5, 1);
        int yy = getWeekday(xx);
        if (!yy) xx += 7;
        else
        {
            int dd = 7 - yy;
            xx += dd + 7;
        }
        return xx;
    };         
    
    auto getFatherDayId = [](int y)
    {
        Zeller::id xx = getZellerId(y, 6, 1);
        int yy = getWeekday(xx);
        if (!yy) xx += 14;
        else
        {
            int dd = 7 - yy;
            xx += dd + 14;
        }
        return xx;
    };

    int t; cin >> t;
    int y, m, d;
    while (t --)
    {
        cin >> y >> m >> d;
        if (m < 5)
        {
            auto id = getMotherDayId(y);
            auto dd = getZellerDate(id);
            cout << dateString(dd.year, dd.month, dd.day) << endl;
        }
        else if (m > 6)
        {
            auto id = getMotherDayId(y + 1);
            auto dd = getZellerDate(id);
            cout << dateString(dd.year, dd.month, dd.day) << endl;
        }
        else
        {
            auto ll = getMotherDayId(y);
            auto rr = getFatherDayId(y);
            auto mm = getZellerId(y,m,d);
            Zeller::date dd;
            if (mm < ll) dd = getZellerDate(ll);
            else if (mm < rr) dd = getZellerDate(rr);
            else 
            {
                auto id = getMotherDayId(y + 1);
                dd = getZellerDate(id);
            }
            cout << dateString(dd.year, dd.month, dd.day) << endl;
        }
    }

    return 0;
}