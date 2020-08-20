/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <vector>
#include <deque>

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

namespace Splay
{
    template <class T>
    struct node
    {
        T key, est, sum;
        int anc, chd[2];
        int size;

        void init(T K, int father = 0)
        {
            size = 1, chd[0] = chd[1] = 0;
            key = est = sum = K, anc = father;
        }
    };

    template <class T>
    class tree
    {
        int root, cnt, mem;
        deque<int> pool;

        using node_t = ::Splay::node<T>;
        vector<node_t> node;

        int &$lc(int id) {return node[id].chd[0];}
        int &$rc(int id) {return node[id].chd[1];}
        int $dir(int id) {return node[node[id].anc].chd[1] == id;}

        int alloc(T key, int father = 0)
        {
            int id = pool.empty() ? ++ cnt : pool.front();
            if (!pool.empty()) pool.pop_front();
            node[id].init(key, father);
            return id;
        }

        void pushUp(int id)
        {
            auto ls = $lc(id), rs = $rc(id);
            node[id].size = node[ls].size + node[rs].size + 1;
            node[id].est = node[id].key;
            if (ls) node[id].est = min(node[id].est, node[ls].est);
            if (rs) node[id].est = min(node[id].est, node[rs].est);
            node[id].sum = node[id].key;
            if (ls) node[id].sum += node[ls].sum;
            if (rs) node[id].sum += node[rs].sum;                 // 注意溢出，可能需要判断
        }

        void rotate(int id)
        {
            int fa = node[id].anc, gfa = node[fa].anc, d = $dir(id);
            if (gfa) node[gfa].chd[$dir(fa)] = id;
            node[fa].anc = id, node[id].anc = gfa;
            node[node[id].chd[!d]].anc = fa;
            node[fa].chd[d] = node[id].chd[!d];
            node[id].chd[!d] = fa;
            pushUp(fa), pushUp(id);
        }

        void splay(int id, int goal = 0)
        {
            for (int fa; (fa = node[id].anc) != goal; rotate(id))
                if (node[fa].anc != goal) rotate($dir(id) == $dir(fa) ? fa : id);
            if (!goal) root = id;
        }

        int getByKey(T key)
        {
            int id = node[root].chd[0], ls = $lc(id), rs = $rc(id);
            while (id)
                if ((rs = $rc(id)) && key > node[rs].est) id = rs;
                else if (key > node[id].key) return id;
                else if ((ls = $lc(id)) && key > node[ls].est) id = ls;
                else return 0;
            return 0;
        }

        int getByRank(int rank)
        {
            if (rank <= 0 || rank > node[root].size) return -1;
            int id = root, ls = $lc(id), rs = $rc(id);
            while (ls = $lc(id), rs = $rc(id), id)
                if (rank <= node[ls].size) id = ls;
                else if (rank <= node[ls].size + 1) break;
                else rank -= node[ls].size + 1, id = rs;
            return id;
        }

        void toStream(ostream &os, int id)
        {
            int ls = $lc(id), rs = $rc(id);
            if (ls) os << "{", toStream(os, ls), os << "}";
            os << " (" << node[id].key << ", " << node[id].est << ") ";
            if (rs) os << "{", toStream(os, rs), os << "}";
        }

    public:
        explicit tree(int size) : mem(size)
        {
            root = cnt = 0;
            node.resize(size);
        }

        void clear()
        {
            root = cnt = 0;
            while (!pool.empty())
                pool.pop_front();
        }

        void insert(T key)
        {
            if (!root)
            {
                root = alloc(key);
                return;
            }
            int id = root, ls, rs;
            while (ls = $lc(id), rs = $rc(id), id)
                if (!rs) return splay(rs = alloc(key, id));
                else id = rs;
        }

        void remove(int id)
        {
            int &ls = $lc(id), &rs = $rc(id);       // assert(id != 0)
            splay(id);
            if (node[id].size == 1)
                return root = 0, pool.push_front(id);
            if (!ls || !rs)
                return root = ls | rs, node[root].anc = 0,
                pool.push_front(id);
            id = node[root].chd[0], ls = $lc(id), rs = $rc(id);
            while (rs) id = rs, ls = $lc(id), rs = $rc(id);
            splay(id), pool.push_front(rs);
            node[node[rs].chd[1]].anc = id, rs = node[rs].child[1];
            pushUp(id);
        }

        T operator [](int rank)
        {
            int id = getByRank(rank);
            splay(id);
            return node[id].key;
        }

        int getPrecursor(int id)
        {
            splay(id), id = $lc(id);
            while ($rc(id)) id = $rc(id);
            return id;
        }

        int getSucceed(int id)
        {
            splay(id), id = $rc(id);
            while ($lc(id)) id = $lc(id);
            return id;
        }

        friend ostream &operator <<(ostream &os, const tree &me)
        {
            me.toStream(os, me.root);
            return os << flush;
        }
    };

}

const int N = 2e5 + 5;
const longs inf = 0x3f3f3f3f3f3f3f3f;

int main()
{
    ios::sync_with_stdio(false);

    Splay::tree<longs> tree(N);
    int t = nextInt();
    while (t --)
    {
        int n = nextInt(), q = nextInt();
        tree.clear();
        while (n --) tree.insert(nextInt());
        tree.insert(inf);
        while (q --)
        {
            longs op = nextInt(), ans;
            if (op == 1)
            {

            }
        }
    }


    return 0;
}