#include <iostream>
#include <vector>
#include <tuple>

using namespace std;
using longs = long long;

struct hand
{
    vector<int> w, b, s, z;

    static bool check3(const vector<int> &list, int res,
                       bool allowShunZi)
    {
        if (!res) return true;
        vector<int> tmp = list;
        bool found = false;
        for (int i = 1; !found && i < 10; ++ i)
            if (tmp[i] >= 3)
                tmp[i] -= 3,
                found |= check3(tmp, res - 3, allowShunZi),
                tmp[i] += 3;
        if (allowShunZi)
            for (int i = 3; !found && i < 10; ++ i)
                if (tmp[i - 2] && tmp[i - 1] && tmp[i])
                    tmp[i - 2] --, tmp[i - 1] --, tmp[i] --,
                    found |= check3(tmp, res - 3, allowShunZi),
                    tmp[i - 2] ++, tmp[i - 1] ++, tmp[i] ++;
        return found;
    }

    static bool check2(const vector<int> &list, int res,
                       bool allowShunZi)
    {
        vector<int> tmp = list;
        bool found = false;
        for (int i = 1; !found && i < 10; ++ i)
            if (tmp[i] >= 2)
                tmp[i] -= 2,
                found |= check3(tmp, res - 2, allowShunZi),
                tmp[i] += 2;
        return found;
    }

    static bool checkDuiZi(const vector<int> &list)
    { return (count(list) % 3); }

    static int count(const vector<int> &list)
    {
        int ret = 0;
        for (auto ii : list) ret += ii;
        return ret;
    }

    static void append(string &s, char type, int num, int times)
    {
        while (times --)
            s.push_back(char(num + '0')),
            s.push_back(type);
    }

    [[nodiscard]] bool isRiichi() const
    {
        char hasDuiZi = '\0';
        int cntDuiZi = 0;
        if (checkDuiZi(w)) hasDuiZi = 'w', ++ cntDuiZi;
        if (checkDuiZi(b)) hasDuiZi = 'b', ++ cntDuiZi;
        if (checkDuiZi(s)) hasDuiZi = 's', ++ cntDuiZi;
        if (checkDuiZi(z)) hasDuiZi = 'z', ++ cntDuiZi;
        if (cntDuiZi != 1) return false;
        bool check = true;
        check &= (hasDuiZi == 'w' ? check2 : check3)(w, count(w), true);
        check &= (hasDuiZi == 'b' ? check2 : check3)(b, count(b), true);
        check &= (hasDuiZi == 's' ? check2 : check3)(s, count(s), true);
        check &= (hasDuiZi == 'z' ? check2 : check3)(z, count(z), false);
        return check;
    }

    void clear()
    {
        w.clear(), w.resize(10, 0);
        b.clear(), b.resize(10, 0);
        s.clear(), s.resize(10, 0);
        z.clear(), z.resize(10, 0);
    }

    void insert(char type, int num)
    {
        switch (type)
        {
            case 'w': ++ w[num]; break;
            case 'b': ++ b[num]; break;
            case 's': ++ s[num]; break;
            case 'z': ++ z[num]; break;
            default: break;
        }
    }

    hand() = default;

    explicit hand(const string &rhs)
    {
        const int n = rhs.length(); clear();
        for (int i = 0; i < n; i += 2)
            insert(rhs[i + 1], rhs[i] - '0');
    }

    hand &operator=(const string &rhs)
    {
        const int n = rhs.length(); clear();
        for (int i = 0; i < n; i += 2)
            insert(rhs[i + 1], rhs[i] - '0');
        return *this;
    }

    explicit operator string() const
    {
        string builder;
        for (int i = 1; i < 10; ++ i)
            if (w[i]) append(builder, 'w', i, w[i]);
        for (int i = 1; i < 10; ++ i)
            if (b[i]) append(builder, 'b', i, b[i]);
        for (int i = 1; i < 10; ++ i)
            if (s[i]) append(builder, 's', i, s[i]);
        for (int i = 1; i < 8; ++ i)
            if (z[i]) append(builder, 'z', i, z[i]);
        return builder;
    }

    [[nodiscard]] int count() const
    {return count(w) + count(s) + count(b) + count(z);}

    [[nodiscard]] string toString() const
    {return (string)(*this);}
};

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int T; string s;
    cin >> T;
    hand now, ans;
    vector<tuple<char, int, string>> out;
    const auto draw =
    [&](hand tmp)
    {
        for (int i = 1; i < 10; ++ i)
        {
            ++ tmp.w[i];
            if (tmp.isRiichi()) ans.insert('w', i);
            -- tmp.w[i];
            ++ tmp.s[i];
            if (tmp.isRiichi()) ans.insert('s', i);
            -- tmp.s[i];
            ++ tmp.b[i];
            if (tmp.isRiichi()) ans.insert('b', i);
            -- tmp.b[i];
            if (i > 7) continue;
            ++ tmp.z[i];
            if (tmp.isRiichi()) ans.insert('z', i);
            -- tmp.z[i];
        }
    };
    while (T --)
    {
        cin >> s;
        now = s, ans.clear(), out.clear();
        if (now.isRiichi())
        {
            cout << "Tsumo!" << endl;
            continue;
        }
        else
        {
            for (int i = 1; i < 10; ++ i)
                if (now.w[i])
                {
                    ans.clear();
                    -- now.w[i], draw(now), ++ now.w[i];
                    auto ret = ans.count();
                    if (ret) out.emplace_back('w', i, ans.toString());
                }
            for (int i = 1; i < 10; ++ i)
                if (now.b[i])
                {
                    ans.clear();
                    -- now.b[i], draw(now), ++ now.b[i];
                    auto ret = ans.count();
                    if (ret) out.emplace_back('b', i, ans.toString());
                }
            for (int i = 1; i < 10; ++ i)
                if (now.s[i])
                {
                    ans.clear();
                    -- now.s[i], draw(now), ++ now.s[i];
                    auto ret = ans.count();
                    if (ret) out.emplace_back('s', i, ans.toString());
                }
            for (int i = 1; i < 8; ++ i)
                if (now.z[i])
                {
                    ans.clear();
                    -- now.z[i], draw(now), ++ now.z[i];
                    auto ret = ans.count();
                    if (ret) out.emplace_back('z', i, ans.toString());
                }
        }
        cout << out.size() << endl;
        for (auto &[ty, id, alt] : out)
            cout << id << ty << ' ' << alt << endl;
    }
    return 0;
}