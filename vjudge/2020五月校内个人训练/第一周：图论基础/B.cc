/**
 *
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define ok(n) "Sorted sequence determined after " << n << " relations: "
#define cf(n) "Inconsistency found after " << n << " relations."
#define failed "Sorted sequence cannot be determined."

using namespace std;
typedef long long longs;
enum state {wait, conflict, pass};

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;

int n, m; string s;
bool out[30][30];
int in[30];

void init()
{
    memset(in, 0, sizeof in);
    memset(out, 0, sizeof out);
}

int *topSort()
{
    static int seq[30], ind[30];
    seq[0] = 0;
    for (int i = 0; i < n; ++ i)
        ind[i] = in[i];
    int find = -1, find2 = -1;
    int residue = n;
    while (residue)
    {
        find = -1, find2 = -1;
        for (int i = 0; i < n; ++ i)
            if (!ind[i])
                (find != -1 ? find2 : find) = i;
        if (find == -1)
        {
            seq[0] = -1;
            break;
        }
        else if (find2 != -1)
        {
            seq[0] = -2;
            break;
        }
        else
        {
            for (int i = 0; i < 26; ++ i)
                if (out[find][i]) -- ind[i];
            ind[find] = -1;
            seq[++ seq[0]] = find;
            -- residue;
        }
    }
    return seq;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    while (cin >> n >> m && n && m)
    {
        init(); state ss = wait;
        int cnt = 0, value = 0;
        int *seq;

        while (m --)
        {
            cin >> s;
            if (ss != wait) continue;
            int from = s[0] - 'A', to = s[2] - 'A';
            out[from][to] = true;
            ++ in[to]; ++ cnt;
            if (out[to][from])
            {
                ss = conflict;
                value = cnt;
            }
            else
            {
                int *xx = topSort();
                if (xx[0] == -1)
                {
                    ss = conflict;
                    value = cnt;
                }
                else if (xx[0] == n)
                {
                    ss = pass;
                    value = cnt;
                    seq = xx;
                }
            }
        }

        switch (ss)
        {
            case conflict:
                cout << cf(value) << endl;
                break;
            case wait:
                cout << failed << endl;
                break;
            case pass:
                cout << ok(value);
                for (int i = 1; i <= seq[0]; ++ i)
                    cout << char(seq[i] + 'A');
                cout << endl;
                break;
            default: break;
        }
    }

    return 0;
}