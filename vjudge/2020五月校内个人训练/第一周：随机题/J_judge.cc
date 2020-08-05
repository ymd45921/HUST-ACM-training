/**
 *
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>

using namespace std;
using longs = long long;

constexpr int inf = 0x3f3f3f3f;
constexpr double eps = 1e-8;

template <int n> int *EulerSieve()
{
    static int prime[n + 5];
    bool vis[n + 5] {false};
    int &cnt = prime[0] = 0;
    for (int i = 2; i <= n; ++ i)
    {
        if (!vis[i]) prime[++ cnt] = i;
        for (int j = 1; j <= cnt && (longs)i * prime[j] <= n; ++ j)
        {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
        }
    }
    return prime;
}

longs gcd(longs a, longs b)
{
    if (a < b) swap(a, b);
    return b ? gcd(b, a % b) : a;
}

bool check(longs ans, longs out)
{
    if (abs(ans - out) <= 7) return true;
    else return ans * 2 <= out || out * 2 <= ans;
}

longs bruteAnswer(longs num)
{
    static bool initialized = false;
    static int *prime, cnt;
    if (!initialized)
    {
        prime = EulerSieve<31623>();
        cnt = prime[0];
        initialized = true;
    }
    int count[3500]{0}, maxx = 0;
    for (int i = 1; i <= cnt; ++ i)
    {
        if (prime[i] > num) break;
        else maxx = i;
        while (num % prime[i] == 0)
            ++ count[i], num /= prime[i];
    }
    longs answer = 1;
    for (int i = 1; i <= maxx; ++ i)
        answer *= (1 + count[i]);
    return answer;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<longs> tests, ans;
    int cnt;

    auto input_test = [&]
    {
        cerr << "set number of games: " << endl;
        cin >> cnt; longs xx;
        cerr << "you want to hold " << cnt << " game(s)." << endl;
        for (int i = 1; i <= cnt; ++ i)
        {
            cin >> xx;
            if (xx > 0 && xx <= 1e9)
            {
                tests.push_back(xx);
                ans.push_back(bruteAnswer(xx));
                cerr << "test " << i << ": " << xx << endl;
            }
            else
            {
                cerr << "violate range. try again." << endl;
                -- i;
            }
        }
    };

    auto load_test = [&]
    {
        ifstream fin (argv[1]);
        fin >> cnt; longs xx;
        cerr << "you want to hold " << cnt << " game(s)." << endl;
        for (int i = 1; i <= cnt; ++ i)
        {
            fin >> xx;
            tests.push_back(xx);
            ans.push_back(bruteAnswer(xx));
            cerr << '[' << i << "] : " << xx << endl;
        }
        cout << cnt << endl;
    };

    if (argc == 1) input_test();
    else if (argc == 2) load_test();

    for (auto &ii : tests)
    {
        cerr << "test start, give query..." << endl;
        int queries = 0; longs query;
        char mod; bool result = false;
        while (queries <= 22)
        {
            cin >> mod >> query;
            if (mod == '!')
            {
                result = check(ii, query);
                if (result) cerr << "Correct, next test..." << endl;
                else cerr << "Failed, answer = " << ii << ", but output = "
                    << query << ". next test..." << endl;
                break;
            }
            else if (mod == '?')
            {
                if (queries == 22)
                {
                    cerr << "Queries has reached upper limit, you failed." << endl;
                    break;
                }
                ++ queries;
                if (queries >= 1e18 || queries <= 0)
                    cerr << "Invalid query " << query << "violate the range 1e18" << endl;
                else cout << gcd(ii, query) << endl;
            }
            else cerr << "invalid query symbol." << endl;
        }
        cerr << "Test ended... state = " << (result ? "[PASSED]" : "[REJECTED]") << endl;
    }

    return 0;
}