/**
 *
 * 不想要哈希的话也可以后缀数组
 *
 * 真的debug给整吐了
 * 下次哈希还是乖乖的s+1报平安吧（
 * 就算这过了的代码还有越界访问的锅，就很草）
 * 
 * 算是深度debug了==
 */
#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <cstring>

using namespace std;
typedef long long longs;
typedef unsigned long long ulongs;

const int N = 2e6+5;
const int inf = 0x7fffffff;
const longs INF = 0x7fffffffffffffff;
const double eps = 1e-8;

int n, k; char s[N];
int ff[N];

namespace StringHash
{
    const int __base = 6151;
    const int __offset = 97;
    ulongs pow[N], var[N];

    int __idx(const char ch)
    {
        return ch - 'a' + 1;
    }

    void init(const char* s)
    {
        pow[0] = 1; var[0] = __idx(s[0]) + __offset;
        int n = strlen(s);
        for (int i = 1; i < n; ++ i)
        {
            pow[i] = pow[i - 1] * __base;
            var[i] = var[i - 1] * __base + __idx(s[i]) + __offset;
        }
    }

    ulongs getHashCode(int l, int r)
    {
        if (l == r || !r) return 0ull;
        auto __elim = l ? var[l - 1] : 0ull;
        return var[r - 1] - __elim * pow[r - l];
    }
}

namespace newStringHash
{
    const int __base = 127;
    const int __offset = 0;
    ulongs var[N], pow[N];

    int __idx(char ch)
    {
        return ch - 'a';
    }

    void init(const char *s)
    {
        const int n = strlen(s);
        var[n] = 0; pow[0] = 1;
        for (int i = n - 1; ~i; -- i)
            var[i] = var[i + 1] * __base + __idx(s[i]) + __offset;
        for (int i = 1; i <= n; ++ i)
            pow[i] = pow[i - 1] * __base;
    }

    ulongs getHashCode(int l, int r)
    {
        return var[l] - pow[r - l] * var[r];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto check = [&](int mid) -> bool
    {
        if (mid == 0) return true;                  // 仍然需要：因为getHashCode("") = 0，不可确定，一定false
        using StringHash::getHashCode;              // 若字符串[l, r]，则空字符串创造了接点
        static unordered_map<ulongs, int> map;
        ff[0] = 0; int ret = 0, lim = n - mid;      // 因为手动偏移了坐标i到[1,n]，所以理论上ff[-1] = 0; map默认值-1
        for (int i = 0; i <= lim; ++ i)
        {
            if (i - mid >= 0) map[getHashCode(i - mid, i)] = i - mid + 1;       // 0 是默认值，会有意想不到的值存进来，
            ulongs xx = map[getHashCode(i, i + mid)] - 1; ff[i] = ff[xx] + 1;   // 所以有意义的值要主动回避
            ret = max(ret, ff[i]);                                              // 虽然A了，但xx可能为-1，导致越界访问。
        }
        map.clear();
        return ret >= k;
    };

    auto recheck = [&](int mid) -> bool
    {
        if (mid == 0) return true;
        using StringHash::getHashCode;
        static unordered_map<ulongs, int> map;
        int ret = 0, lim = n - mid;
        for (int i = 0; i <= lim; ++ i)
        {
            if (i - mid >= 0) map[getHashCode(i - mid, i)] = i - mid;
            ulongs hashcode = getHashCode(i, i + mid);
            ff[i] = map.count(hashcode) ? ff[map[hashcode]] + 1 : 1;
            ret = max(ret, ff[i]);
        }
        map.clear();
        return ret >= k;
    };

    cin >> n >> k >> s;
    StringHash::init(s);

    int ll = 0, rr = n, ans = 0;
    recheck(0);
    while (ll <= rr)
    {
        int mm = ll + rr >> 1;
        if (recheck(mm)) ans = mm, ll = ++ mm;
        else rr = -- mm;
    }
    cout << ans << endl;

    return 0;
}