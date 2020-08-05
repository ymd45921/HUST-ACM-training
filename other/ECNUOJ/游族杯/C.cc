/**
 *
 */
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using longs = long long;
using ulongs = unsigned long long;

constexpr int inf = 0x3f3f3f3f;
constexpr double eps = 1e-8;

struct leukocyte
{
    int id;
    ulongs x, y, z;

    leukocyte() = default;

    bool operator<(const leukocyte &rhs) const
    {
        return (x <= rhs.x && y <= rhs.y && z <= rhs.z) &&
                (x < rhs.x || y < rhs.y || z < rhs.z);
    }

    bool operator>(const leukocyte &rhs) const
    {
        return (x >= rhs.x && y >= rhs.y && z >= rhs.z) &&
               (x > rhs.x || y > rhs.y || z > rhs.z);
    }

    bool operator==(const leukocyte &rhs) const
    { return !(*this < rhs) && !(*this > rhs); }
};

namespace generator
{
    unsigned long long k1, k2;

    unsigned long long CoronavirusBeats()
    {
        unsigned long long k3 = k1, k4 = k2;
        k1 = k4;
        k3 ^= k3 << 23;
        k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
        return k2 + k4;
    }

    void gen(leukocyte *array, int n)
    {
        for (int i = 0; i < n; ++ i)
        {
            array[i].x = CoronavirusBeats();
            array[i].y = CoronavirusBeats();
            array[i].z = CoronavirusBeats();
            array[i].id = i;
        }
    }
}

const int N = 1e5 + 5;
leukocyte leu[N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n >> generator::k1 >> generator::k2;
    generator::gen(leu, n);
    

    return 0;
}