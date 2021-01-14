#include <bits/stdc++.h>

using namespace std;

using longs = long long;
using uint = unsigned;
using lll = __int128;
using ulongs = unsigned long long;

#define maximium(a, b) ((a) = max(a, b))
#define minimium(a, b) ((a) = min(a, b))
#define sgn(x) ((x) < 0 ? -1 : ((x) > 0))

template <class T>
void print(T x)
{
    char ch[40]; int cnt = 0;
    if (x == 0) return void(putchar('0'));
    if (x < 0) putchar('-'), x = -x;
    while (x) ch[cnt ++] = x % 10 + 48, x /= 10;
    while (cnt --) putchar(ch[cnt]);
}
void print(char x) {putchar(x);}
template <class T>
void println(T x) {print(x), putchar('\n');}

class Scanner
{
    template <class T>
    T read()
    {
        T x = 0; int ch = getchar(), f = 1;
        while (!isdigit(ch)) (ch == '-' && (f = !f)), ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
        return f ? x : -x;
    }

    public:

    template <class T>
    void operator()(T &x) {x = read<T>();}

    void operator()(char &x)
    {
        x = getchar();
        while (x == ' ' || x == '\n') x = getchar();
    }

    template <class T, class ...Ts>
    void operator()(T &x, Ts &... y)
    {(*this)(x), (*this)(y...);}
} scan;

const int N = 1e5 + 5;
int a[N], tmp[N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    cout << "Give n k p to set a testcase: " << flush;
    int n, k, p;
    cin >> n >> k >> p;
    for (int i = 1; i <= n; ++ i) a[i] = k;
    const auto process = [&n, &p]
    {
        const int desc = n - 1, insc = 1;
        memset(tmp, 0, sizeof(int) * (n + 1));
        for (int i = 0; i < n; ++ i)
        {
            double my = a[i + 1], half = my / 2.;
            int left = floor(half),
                right = ceil(half);
            if (i + 1 == p) left = 0, right = my;    
            tmp[(i + desc) % n + 1] += left;
            tmp[(i + insc) % n + 1] += right;
        }
        memcpy(a, tmp, sizeof(int) * (n + 1));
    };
    char op; int pos, cnt = 0;
    while (true)
    {
        cin >> op >> pos;
        if (cnt >= 1000) cerr << "WARN: interaction limit exceeded" << endl;
        if (op == '?') cout << a[pos] << endl;
        else if (op == p) cout << "OK." << endl, exit(EXIT_SUCCESS);
        else cout << "Reject. Answer is " << p << "." << endl, exit(EXIT_FAILURE);
        process();
        #if 1
            for (int i = 1; i <= n; ++ i)
                cerr << a[i] << " \n"[i == n];
        #endif
    }
    return 0;   
}

