/**
 *
 * RE:  数组要开大一点，何佳林都是直接开了 150%
 *      似乎就算有对象池回收也不行
 * WA:  严重怀疑这个题目是个假题，删掉了题目的限制就过了
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <vector>
#include <stack>
#include <functional>

#define SPLAY_APPEND_MODE
#define LOG(x...) fprintf(stderr, x)
#define WATCH(var) LOG(""#var" = %lld ", (longs)var)
#define END_LINE LOG("\n"), fflush(stderr)

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

namespace SimpleSplayTree
{
    template <class T>
    struct node
    {
        T key, est, sum;
        int anc, chd[2], cnt;
        int size;
        bool rev;

        void init(T K, int father = 0)
        {
            size = cnt = 1, chd[0] = chd[1] = 0;
            key = est = sum = K, anc = father;
            rev = false;
        }
    };

    template <class T>
    class tree
    {
        int root, cnt, mem;
        stack<int> pool;

        using node_t = ::SimpleSplayTree::node<T>;
        using method_t = function<void(node_t&)>;
        vector<node_t> node;

        int &lc(int id) {return node[id].chd[0];}
        int &rc(int id) {return node[id].chd[1];}
        int dir(int id) {return node[node[id].anc].chd[1] == id;}

        int alloc(T key, int father = 0)
        {
            int id = pool.empty() ? ++ cnt : pool.top();
            if (!pool.empty()) pool.pop();
            node[id].init(key, father);
            return id;
        }

        void free(int id) {if (id) pool.push(id);}

        void update(int id)
        {
            auto ls = lc(id), rs = rc(id);
            node[id].size = node[ls].size + node[rs].size + node[id].cnt;
            node[id].est = node[id].key;
            if (ls) node[id].est = min(node[id].est, node[ls].est);
            if (rs) node[id].est = min(node[id].est, node[rs].est);
            node[id].sum = node[id].key * node[id].cnt;
            if (ls) node[id].sum += node[ls].sum;
            if (rs) node[id].sum += node[rs].sum;                 
        }

        void rotate(int id)
        {
            int fa = node[id].anc, gfa = node[fa].anc, d = dir(id);
            if (gfa) node[gfa].chd[dir(fa)] = id;
            node[fa].anc = id, node[id].anc = gfa;
            node[node[id].chd[!d]].anc = fa;
            node[fa].chd[d] = node[id].chd[!d];
            node[id].chd[!d] = fa;
            update(fa), update(id);
        }

        void splay(int id, int goal = 0)
        {
            for (int fa; (fa = node[id].anc) != goal; rotate(id))
                if (node[fa].anc != goal) rotate(dir(id) == dir(fa) ? fa : id);
            if (!goal) root = id;
        }

#ifdef SPLAY_BST_MODE
        int find(T key)
        {
            int id = root;
            if (!id) return 0;
            while (key != node[id].key && node[id].chd[key > node[id].key])
                id = node[id].chd[key > node[id].key];
            return splay(id), id;
        }

        int getNext(T key, bool dir)
        {
            int id = find(key);
            if (dir ? node[id].key > key : node[id].key < key)
                return id;
            id = node[id].chd[dir];
            while (node[id].chd[!dir]) id = node[id].chd[!dir];
            return id;
        }
#endif

        int lazyTag(int id)
        {
#ifdef SPLAY_APPEND_MODE
            if (id && node[id].rev)
            {
                swap(lc(id), rc(id));
                node[id].rev = false;
                auto ls = lc(id), rs = rc(id);
                if (ls) node[ls].rev = !node[ls].rev;
                if (rs) node[rs].rev = !node[rs].rev;
            }
#endif
            return id;
        }

        int atRank(int rank)
        {
            if (rank <= 0 || rank > node[root].size) return -1;
            int id = root, ls = lc(id), rs = rc(id);
            while (lazyTag(id), ls = lc(id), rs = rc(id), id)
                if (rank <= node[ls].size) id = ls;
                else if (rank <= node[ls].size + node[id].cnt) break;
                else rank -= node[ls].size + node[id].cnt, id = rs;
            return id;
        }

        void toStream(ostream& os, int id)
        {
            int ls = lc(id), rs = rc(id);
            if (ls) os << "{", toStream(os, ls), os << "}";
            os << " (#" <<id << ": " << node[id].key << ") ";
            if (rs) os << "{", toStream(os, rs), os << "}";
        }

        void traversal(int id, const method_t &process)
        {
            lazyTag(id);
            const auto ls = lc(id), rs = rc(id);
            if (ls) traversal(ls, process);
            process(node[id]);
            if (rs) traversal(rs, process);
        }

#if 1
        // 在左子树中找到第一个小于 key 的值
        // 利用了节点维护的最小值 (est)
        int askLeft(T key)
        {
            int id = lc(root), ls, rs;
            while (ls = lc(id), rs = rc(id), id)
                if (rs && key > node[rs].est) id = rs;
                else if (key > node[id].key) return id;
                else if (ls && key > node[ls].est) id = ls;
                else return 0;
            return 0;
        }
#endif

    public:
        explicit tree(int size) : mem(size)
        {
            root = cnt = 0;
            node.resize(size + 1);
        }

        T access(int id) {return node[id].key;}

        void clear()
        {
            root = cnt = 0;
            while (!pool.empty()) pool.pop();
        }

        T at(int rank)
        {
            if (node[root].size < rank) return -1;
            auto id = atRank(rank);
            return splay(id), node[id].key;
        }

        int getSize() {return root ? node[root].size : 0;}

        void toArray(vector<T> &arr)
        {
            arr.clear();
            traversal(root, [&](node_t &ii){arr.push_back(ii.key);});
        }

        /**
         * BST 模式：
         * 
         * 树始终维持了 BST 的性质，可以使用二分法在树上查找；
         * erase 方法已经换成不要求哨兵节点的版本了；
         * 对于每一个节点，使用 cnt 域维护该值的出现次数；
         */
#ifdef SPLAY_BST_MODE
        void insert(T key)
        {
            if (!root)
            {
                root = alloc(key);
                return;
            }
            int id = root, fa = 0;
            while (id && node[id].key != key)
            {
                fa = id;
                id = node[id].chd[key > node[id].key];
            }
            if (id) return ++ node[id].cnt, splay(id);
            id = alloc(key, fa);
            if (fa) node[fa].chd[key > node[fa].key] = id;  // 无需特判 fa 是否为根
            return splay(id);
        }

        void erase(T key)
        {
            int id = find(key), ex;
            if (!id || node[id].key != key) return;
            if (node[id].cnt > 1)
                return -- node[id].cnt, update(id);
            auto ls = lc(id), rs = rc(id);
            if (!ls || !rs)
            {
                root = ls | rs;
                if (root) node[root].anc = 0;
                return free(id);
            }
            id = ls, ex = root, rs = rc(id);
            while (rs) id = rs, rs = rc(id);
            splay(id), node[id].anc = 0, rs = rc(ex);
            node[rs].anc = id, rc(id) = rs;
            return free(ex), update(root);
        }

        int getOrder(T key)
        {
            int id = find(key);
            if (!lc(id)) return 1;
            return node[lc(id)].size + 1;
        }
        
        T getPrecursor(T key)
        {
            auto id = getNext(key, 0);
            return node[id].key;
        }

        T getSucceed(T key)
        {
            auto id = getNext(key, 1);
            return node[id].key;
        }
#endif

        /**
         * APPEND 模式：
         *
         * 指不适用 BST 性质，仅将树的中序遍历作为数组序列的用法；
         * 因此，不能使用 find 方法查找特定键值的节点 id；
         * 可通过使用第 k 大的方法去按照下标来获得 id 从而随机访问；
         * 还可以通过维护关于键值的一些特定值，来进行关于键值的特定查找；
         *
         * 当在 APPEND 模式下，节点的 cnt 值毫无意义，始终为 1；
         * 并不是不可以使用 cnt 维护连续的值相同的区间，主要是意义不大；
         */
#ifdef SPLAY_APPEND_MODE
        void append(T key)
        {
            if (!root)
            {
                root = alloc(key);
                return;
            }
            int id = root, rs;
            while (rs = rc(id), id)
                if (!rs) return splay(rc(id) = alloc(key, id));
                else id = rs;
        }

        void remove(int id)
        {
            splay(id);                      // assert(id != 0)
            int ls = lc(id), rs = rc(id);   // 不要滥用引用！ ls/rs 在 id 后更新
            if (node[id].cnt > 1)
                return -- node[id].cnt, update(id);
            if (node[id].size == 1)
                return root = 0, free(id);
            if (!ls || !rs)
                return root = ls | rs, node[root].anc = 0, free(id);
            id = node[root].chd[0], ls = lc(id), rs = rc(id);
            while (rs) id = rs, ls = lc(id), rs = rc(id);
            splay(id), free(rs);            // free 没有立即清空，所以可以先 free
            ls = lc(id), rs = rc(id);       // 树的结构发生变化，应立即更新 ls， rs
            node[rc(rs)].anc = id, rc(id) = node[rs].chd[1];
            update(id);
        }

        int getLast(int id)
        {
            splay(id), id = lc(id);
            while (rc(id)) id = rc(id);
            return id;
        }

        int getNext(int id)
        {
            splay(id), id = rc(id);
            while (lc(id)) id = lc(id);
            return id;
        }

        // 使用的时候应当保证插入虚节点作为哨兵（仅末尾
        void reverse(int l, int r)
        {
            if (l > r) return;
            int id = atRank(r + 1);
            splay(id), splay(atRank(l - 1), id);
            int son = rc(lc(root));
            node[son].rev = !node[son].rev;
        }
#endif

        T operator [](int rank)
        {
            int id = atRank(rank);
            splay(id);
            return node[id].key;
        }

        friend ostream &operator <<(ostream &os, tree &me)
        {
            me.toStream(os, me.root);
            return os << flush;
        }

#if 1
        // 执行题目要求的向左推砖块（平移区间）
        T pushLeft(int x, T y)
        {
            int r = atRank(x), r1 = getNext(r);
            splay(r1);
            int l = askLeft(y);
            if (!l) return 0;
            else splay(l, r1);
            int id = rc(lc(root));
            longs size = node[id].size, sum = node[id].sum;
            int l1 = getNext(l);
            node[l].key += node[l1].key - y + 1;
            remove(l1);
            int ins = getLast(r1);
            rc(ins) = alloc(y - 1, ins);
            update(ins), splay(ins);
            return sum - size * (y - 1);
        }
#endif
    };

}

const int inf = 0x3f3f3f3f;
const longs INF = 0x3f3f3f3f3f3f3f3f;
const int N = 3e5 + 50;

int main()
{
    ios::sync_with_stdio(false);

    int t = nextInt();
    SimpleSplayTree::tree<longs> tbl(N);
    vector<longs> vec;
    auto toLog = [&]()
    {
        tbl.toArray(vec);
        for (auto ii : vec) LOG("%lld ", ii);
        END_LINE;
    };
    while (t --)
    {
        int n = nextInt(), q = nextInt();
        tbl.clear();
        while (n --) tbl.append(nextInt());
        tbl.append(0);
        while (q --)
        {
            int op = nextInt();
            if (op == 1)
            {
                int x = nextInt(), y = nextInt();
                if (tbl[x] < y) puts("0");          // tbl[x + 1] >= y ??
                else printf("%lld\n", tbl.pushLeft(x, y));
            }
            else printf("%lld\n", tbl[nextInt()]);
        }
        tbl.toArray(vec);
        n = (int) vec.size() - 1;
        printf("%lld", vec[0]);
        for (int i = 1; i < n; ++ i)
            printf(" %lld", vec[i]);
        puts("");
    }

    return 0;
}