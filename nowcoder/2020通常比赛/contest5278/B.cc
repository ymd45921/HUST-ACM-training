/**
 *
 */
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iomanip>

using namespace std;
using longs = long long;
using longd = long double;
using ulongs = unsigned long long;

const int inf = 0x3f3f3f3f;
const longs INF = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-8;

struct info
{
    int date;
    string id;
    double temp;

    info() = default;
    info(int date, string id, double temp) : date(date), id(id), temp(temp) {}

    bool operator<(const info &rhs) const {
        if (date < rhs.date)
            return true;
        if (rhs.date < date)
            return false;
        if (temp < rhs.temp)
            return true;
        if (rhs.temp < temp)
            return false;
        return id > rhs.id;
    }

    bool operator>(const info &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const info &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const info &rhs) const {
        return !(*this < rhs);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m = 0;
    int x; string y; double z;
    vector<info> v;
    cin >> n;
    for (int i = 0; i < n; ++ i)
    {
        cin >> x >> y >> z;
        if (z < 38.0) continue;
        ++ m;
        v.emplace_back(x,y,z);
    }
    sort(v.begin(), v.end());
    cout << m << endl << fixed << setprecision(1);
    while (m --)
    {
        cout << v[m].date << ' '
             << v[m].id << ' '
             << v[m].temp << endl;
    }

    return 0;
}