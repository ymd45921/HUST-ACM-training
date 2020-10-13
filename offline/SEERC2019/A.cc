/**
 *
 * 算是有趣的题目，要想要做出这个题：
 * - 需要看出斑马数列需要维护的次数
 * - 需要想到使用线段树维护更新答案
 * 综合起来就非常的麻烦了；下面是抄的代码
 * 
 * TODO: 理解抄的代码的做法
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;
using longd = long double;

#define eprintf(x...) fprintf(stderr, x...)
#define var(x) ""#x" = " << x 
#define lll __int128
#define ls (now << 1)
#define rs (ls ^ 1)
#define NOW tree[now]
#define LS tree[ls]
#define RS tree[rs]
#define whole 1, 1, (2 * n)

template <class T>
void println(const T x)
{puts(to_string(x).c_str());}
void println(const char *s){puts(s);}
void println(const char ch)
{putchar(ch), putchar('\n');}

static class Scanner 
{
    template<class T>
    inline T read()
    {
        T x = 0; int f = 0, ch = getchar();
        while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
        return f ? -x : x;
    }

public:

    template <class T>
    void operator()(T &x){x = read<T>();}

    template <class T, class... Ts>
    void operator()(T &x, Ts &... y)
    {(*this)(x), (*this)(y...);}

    void operator()(char *x){scanf("%s", x);}
    void operator()(char &x){x = getchar();}

    int nextInt() {return read<int>();}
    longs nextLongs() {return read<longs>();}  
    lll nextInt128() {return read<lll>();}
    char nextChar() {return getchar();}    
} scanner;

const int N = 2e5 + 5;
int a[N * 2], k = 0;
vector<int> pos[N];

namespace segTree
{
    struct node
    {int l, r, val;}
    tree[N * 2 * 4];

    node merge(node ll, node rr, int l, int r, int mid)
    {
        node ret;
        bool flag = (longs)(a[mid] - k) * (a[mid + 1] - k) < 0;
        if (flag && ll.l == mid - l + 1) ret.l = ll.l + rr.l;
        else ret.l = ll.l;
        if (flag && rr.r == r - mid) ret.r = ll.r + rr.r;
        else ret.r = rr.r;
        if (flag) ret.val = ll.val - ll.r / 2 + rr.val - rr.l / 2 + (ll.r + rr.l) / 2;
        else ret.val = ll.val + rr.val;
        return ret;
    }

    void build(int now, int l, int r)
    {
        if (l == r)
        {
            if (a[l] == k) NOW = {0, 0, 0};
            else NOW = {1, 1, 0};
        }
        else 
        {
            auto mid = (l + r) >> 1;
            build(ls, l, mid);
            build(rs, mid + 1, r);
            NOW = merge(LS, RS, l, r, mid);
        }
    }

    void update(int now, int l, int r, int p)
    {
        if (l > p || r < p) return;
        else if (l == r)
        {
            if (a[l] == k) NOW = {0, 0, 0};
            else NOW = {1, 1, 0};
        }
        else
        {
            int mid = (l + r) >> 1;
            update(ls, l, mid, p);
            update(rs, mid + 1, r, p);
            NOW = merge(LS, RS, l, r, mid);
        }
    }

    node query(int now, int l, int r, int al, int ar)
    {
        if (l >= al && r <= ar) return NOW;
        int mid = l + r >> 1;
        if (mid >= ar) return query(ls, l, mid, al, ar);
        if (al > mid) return query(rs, mid + 1, r, al, ar);
        return merge
        (
            query(ls, l, mid, al, ar),
            query(rs, mid + 1, r, al, ar),
            max(l, al), min(r, ar), mid
        );
    }
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n, m;
    scanner(n, m);
    for (int i = 1; i <= n; ++ i)
    {
        a[i] = scanner.nextInt();
        pos[a[i]].push_back(i);
        a[i + n] = a[i];
    }
    segTree::build(whole);
    for (k = 1; k <= m; ++ k)
    {
        for (auto p : pos[k])
            segTree::update(whole, p),
            segTree::update(whole, p + n);
        for (auto p : pos[k - 1])
            segTree::update(whole, p),
            segTree::update(whole, p + n);
        if (pos[k].empty())
        {
            printf("-1 ");    
            continue;
        }
        int l = pos[k][0], r = pos[k][0] + n;
        auto ans = segTree::query(whole, l, r).val;
        ans += n - pos[k].size();
        printf("%d ", ans);
    }

    return 0;
}

