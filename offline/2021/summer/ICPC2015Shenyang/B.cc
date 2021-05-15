#include <bits/stdc++.h>

using namespace std;
using llong = long long;

#define bigint int
bigint read() {
    bigint ret = 0;
    int f = 0, ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-') f = !f;
    for (; isdigit(ch); ch = getchar())
        ret = ret * 10 + ch - 48;
    return f ? -ret : ret;
}

void write(bigint x) {
    static char str[100];
    if (x < 0) putchar('-'), x = -x;
    int cnt = 0;
    while (x > 9) {
        str[cnt ++] = char(x % 10 + 48);
        x /= 10;
    }
    str[cnt ++] = char(x + 48);
    while (cnt --) putchar(str[cnt]);
}
#undef bigint

const int N = 2050, M = 505;
int next[M][N];
char str[M][N];

void build_kmp(const char *s, int *kmp, int n) {
    int i = 0, j = kmp[0] = -1;
    while (i < n)
        if (-1 == j || s[i] == s[j])
            kmp[++ i] = ++ j;
        else j = kmp[j];
}

bool match_kmp(const char *s, const char *t,
              const int *kmp, int tl, int pl) {
    int i = 0, j = 0, cnt = 0;
    while (i < tl)
        if (-1 == j || s[i] == t[j]) {
            ++ i, ++ j;
            if (j != pl) continue;
            else return true;
        } else j = kmp[j];
    return false;
}

bool match_sub(int i, int j) {
    return match_kmp(str[i], str[j], ::next[j], strlen(str[i]), strlen(str[j]));
}

signed main() {
    for (int T = read(), tc = 1; tc <= T; ++ tc) {
        printf("Case #%d: ", tc);
        int n = read();
        for (int i = 0; i < n; ++ i) {
            scanf("%s", str[i]);
            build_kmp(str[i], ::next[i], strlen(str[i]));
        }
        int l = n - 2, r = n - 1;
        for(; r > 0; --r, --l) {
            //printf("matching : \n%s\n%s\n", str[l], str[r]);
            if(!match_sub(r, l))
                break;
        }
        if(!r) {
            puts("-1");
            continue;
        }
        if(r == n) {
            printf("%d\n", r);
            continue;
        }
        while(l >= 0) {
            while(r < n && !match_sub(r, l)) ++ r;
            if(r == n) break;
            -- l;
        }
        printf("%d\n", r);
    }
    return 0;
}