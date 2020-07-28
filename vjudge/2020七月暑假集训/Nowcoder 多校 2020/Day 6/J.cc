/**
 *
 */
#include <vector>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>

#define LOWBIT(x) (x & -x)

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 1, ch = getchar();
    while (!isdigit(ch)) if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

template <class T>
class tree_array
{
    vector<T> arr;
    size_t siz = 0;
    static inline int lowBit(int x) {return x & -x;}

public:
    tree_array() = default;
    tree_array(int _s): siz(_s) {arr.resize(siz + 1);};
    void add(int i, const T &v){while (i <= siz) {arr[i] += v; i += lowBit(i);}}
    T ask(int i) {return arr[i + 1];}
    T query(int i) {T x = 0; while (i) { x += arr[i]; i -= lowBit(i);} return x;}
    T query(int l, int r) {return query(r) - query(l - 1);}
    T operator [](int ind) {return arr[ind + 1];}
    T operator ()(int ind) {return query(ind);}
    T operator ()(int l, int r) {return query(r) - query(l - 1);}
    void clear() {arr.clear(); arr.resize(siz + 1);}
    void resize(int _s) {siz = _s; arr.resize(siz + 1);}
};

const int N = 1e5 + 5;
int p[N], tr[N], ans[N], tmp[N];
tree_array<int> arr;

void josephus(int n, int k)
{
    int now = 1, cur = 1, upto = n;
    auto nextDog = [&](int s)
    {
        int ret = 0, tmp = 0;
        for (int i = 17; i >= 0; -- i)
            if (!(ret > upto || LOWBIT(ret) + tmp >= s))
                ret += (1 << i), tmp += LOWBIT(ret);
        return ++ ret;
    };
    while (n --)
    {
        now = (now + k - 2) % n + 1;
        auto pos = nextDog(now);
        arr.add(pos, -1);
        tr[cur ++] = pos;
    }
}

void makeReplace(int n, int *a, const int *b = nullptr)
{
    if (!b) b = a;
    for (int i = 1; i <= n; ++ i) tmp[i] = b[a[i]];
    memcpy(a, tmp, sizeof(int) * (n + 1));
}

void fastProcess(int n, uint x)
{
    for (int i = 1; i <= n; ++ i) ans[i] = i;
    while (x)
    {
        if (x & 1u) makeReplace(n, ans, tr);
        makeReplace(n, tr), x >>= 1u;
    }
    for (int i = 1; i <= n; ++ i) tr[ans[i]] = i;
    for (int i = 1; i <= n; ++ i) tmp[tr[i]] = p[i];
    memcpy(p, tmp, sizeof(int) * (n + 1));
}

int main()
{
    int n = nextInt(), m = nextInt();
    for (int i = 1; i <= n; ++ i) p[i] = i;
    arr.resize(n);
    while (m --)
    {
        int k = nextInt(), x = nextInt();
        josephus(n, k);
        fastProcess(n, x);
    }
    for (int i = 1; i <= n; ++ i) printf("%d ", p[i]);
    puts("");
    return 0;
}