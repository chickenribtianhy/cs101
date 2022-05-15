#include <bits/stdc++.h>
using namespace std;

struct SplayNode
{
    int key;
    SplayNode(int v) { key = v; }
};

#define MAXN 1000001
int _parent[MAXN];
int _children[MAXN][2];
int _size[MAXN];
int _value[MAXN];
class Splay
{
private:
    int _cnt;
    int _root;

public:
    Splay()
    {
        _cnt = 0;
        _root = 0;
        _size[0] = 0;
    }
    void print()
    {
        for (int i = 1; i <= 6; ++i)
        {
            cout << "i = " << i << " , value: " << _value[i] << " , parent: " << _parent[i] << endl
                 << " , children: " << _children[i][0] << " and " << _children[i][1] << endl
                 << " , size:" << _size[i] << endl;
        }
    }

    int size()
    {
        return _size[_root];
    }
    // return 0 if x is a left child, 1 is x is a right child
    bool is_right_child(int x)
    {
        return _children[_parent[x]][1] == x;
    }
    void relink(int son, int father, bool rc)
    {
        // cout << "linking: father = " << father << " , rc = " << rc << " , son = " << son << endl;
        _parent[son] = father;
        _children[father][rc] = son;
    }
    void update(int x)
    {
        // update size
        _size[x] = _size[_children[x][0]] + _size[_children[x][1]] + 1;
    }

    void rotate(int x)
    {
        int fx = _parent[x];
        int ffx = _parent[fx];
        bool rc = is_right_child(x);
        bool frc = is_right_child(fx);
        //==========
        relink(x, ffx, frc);
        // right child to father's left child
        relink(_children[x][!rc], fx, rc);
        relink(fx, x, !rc);
        update(fx);
        update(x);
        // cout << "rotating... fx: " << fx << " , x: " << x << " , ffx: " << ffx << endl;
    }
    void splay(int x)
    {
        if (_parent[x] == 0)
        {
            //x is root, _root == x
            return;
        }
        int i = 1;
        while (_parent[x] != 0)
        {
            int fx = _parent[x];
            bool rc = is_right_child(x);
            if (rc == is_right_child(fx) && _parent[fx] != 0)
            {
                // cout << i << " from splay , fx: " << fx << " , x: " << x << " ffx: " << _parent[i] << endl;
                rotate(fx);
            }
            // if (i == 1 || i == 2)
            //     // cout << i << " from splay , fx: " << fx << " , x: " << x << " ffx: " << _parent[i] << endl;
            rotate(x);
            i++;
        }
        _root = x;
    }
    void splay_to_rootchild(int x)
    {
        if (_parent[x] == _root)
        {
            return;
        }
        int i = 1;
        while (_parent[x] != _root)
        {
            int fx = _parent[x];
            bool rc = is_right_child(x);
            if (rc == is_right_child(fx) && _parent[fx] != _root)
            {
                // cout << i << " from splay , fx: " << fx << " , x: " << x << " ffx: " << _parent[i] << endl;
                rotate(fx);
            }
            // if (i == 1 || i == 2)
            //     // cout << i << " from splay , fx: " << fx << " , x: " << x << " ffx: " << _parent[i] << endl;
            rotate(x);
            i++;
        }
    }
    void insert(int value)
    {
        if (_root == 0)
        {
            // new
            _root = 1;
            _cnt = 1;
            _value[1] = value;
            _parent[1] = _children[1][0] = _children[1][1] = 0;
            _size[1] = 1;
            return;
        }
        // lookup
        ++_cnt;
        _value[_cnt] = value;
        _children[_cnt][0] = _children[_cnt][1] = 0;

        int c = _root;
        bool rc;
        // _children[c][0] != 0 || _children[c][1] != 0
        while (1)
        {
            ++_size[c];
            // cout << "_value[c]: " << _value[c] << " , value: " << value << endl;
            if (_value[c] > value)
            {
                // left-sub tree
                if (_children[c][0] == 0)
                {
                    // cout << "lc\n";
                    rc = false;
                    break;
                }
                c = _children[c][0];
                continue;
            }
            else if (_value[c] <= value) //equal
            {
                if (_children[c][1] == 0)
                {
                    rc = true;
                    break;
                }
                c = _children[c][1];
                continue;
            }
        }
        relink(_cnt, c, rc);
        // cout << "link_format: " << _cnt << " , " << c << " , " << rc << endl;
        _size[_cnt]++;
        splay(_cnt);
        // print();
    }
    int find_last(int x)
    {
        int c = x;
        while (_children[c][1] != 0)
        {
            c = _children[c][1];
        }
        return c;
    }

    int find_next(int x)
    {
        int c = x;
        while (_children[c][0] != 0)
        {
            c = _children[c][0];
        }
        return c;
    }

    void remove(int v)
    {
        if (_root == 0) //empty tree
        {
            return;
        }
        int c = _root;
        while (1)
        {
            if (_value[c] == v)
            {
                splay(c);
                break;
            }

            if (_value[c] > v)
            {
                c = _children[c][0];
            }
            else
            {
                c = _children[c][1];
            }
        }
        splay(c);
        if (_children[c][0] == 0)
        {
            _root = _children[c][1];
            _parent[_root] = 0;
            // _cnt--;
            return;
        }
        else if (_children[c][1] == 0)
        {
            _root = _children[c][0];
            _parent[_root] = 0;
            // _cnt--;
            return;
        }
        else
        {
            int last = find_last(_children[c][0]);
            int next = find_next(_children[c][1]);
            splay(last); // now last is root, next is right child of root
            splay_to_rootchild(next);
            // cout << "-----------------------\n";
            // cout << "splay(20): " << endl;
            // print();
            // cout << "--------------------\n";
            // cout << "last: " << last << " , next " << next << endl;
            // c is left child of next, and is a leaf
            // _cnt--;
            _size[last]--;
            _size[next]--;
            _children[next][0] = 0;
            return;
        }
    }

    int kth(int k)
    {
        if (_root == 0)
        {
            return 0;
        }
        int c = _root;

        // k++;// to synchronize with size
        while (1)
        {
            if (_size[_children[c][0]] == k)
            {
                return _value[c];
            }
            if (_size[_children[c][0]] > k)
            {
                c = _children[c][0];
                continue;
            }
            else
            {
                k = k - _size[_children[c][0]] - 1;
                c = _children[c][1];
                continue;
            }
        }
    }
    // return true if x is a leaf node
    bool is_leaf(int x)
    {
        return (_children[x][0] == 0 && _children[x][1] == 0);
    }

    int rank(int v)
    {
        if (_root == 0) //empty tree
        {
            return 0;
        }
        int c = _root;
        while (1)
        {
            if (_value[c] == v)
            {
                splay(c);
                return _size[_children[c][0]];
            }
            // if (is_leaf(c))
            // {
            if (_children[c][0] == 0 && _value[c] > v)
            {
                splay(c);
                return _size[_children[c][0]];
            }
            else if (_children[c][1] == 0 && _value[c] < v)
            {
                splay(c);
                return _size[_children[c][0]] + 1;
            }
            // }
            if (_value[c] > v)
            {
                c = _children[c][0];
            }
            else
            {
                c = _children[c][1];
            }
        }
    }
};

/* PLEASE DO NOT CHANGE BELOW*/
int A, B, C, lfsr;
double P[4][4];
int lfsr_generator()
{
    auto ret = lfsr;
    return (lfsr ^= lfsr << 13, lfsr ^= lfsr >> 17, lfsr ^= lfsr << 5, ret);
}
tuple<int, int> command()
{
    auto imm = lfsr_generator();
    static int state = 0;
    auto p = double(lfsr_generator() & 0x7fffffff) / INT32_MAX;
    for (int i = 0; i < 4; i++)
        if ((p -= P[state % 4][i]) < 0)
        {
            state += 4 - state % 4 + i;
            break;
        }
    return tuple<int, int>(state % 4, (imm * A + state * B + C) & 0x7fffffff);
}
/* PLEASE DO NOT CHANGE ABOVE*/
int main()
{
    int m;
    Splay tree;
    cin >> m >> lfsr >> A >> B >> C;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            cin >> P[i][j];
    int tans = 0;
    for (int i = 1; i <= m; i++)
    {
        int op, imm;
        tie(op, imm) = command();
        // cout << "op: " << op << ", imm: " << imm << endl;
        if (op == 0)
            tree.insert(imm);
        if (op == 1)
            tree.remove(tree.kth(imm % tree.size()));
        if (op == 2)
            tans ^= tree.rank(imm);
        if (op == 3)
            tans ^= tree.kth(imm % tree.size());
        // cout << "iter " << i << " == == == == == == == == == == == == == == == == == == =\n ";
        // tree.print();
    }

    // tree.insert(10);
    // tree.insert(50);
    // tree.insert(20);
    // tree.insert(60);
    // tree.insert(40);
    // tree.insert(30);
    // tree.insert(1602717496);
    // tree.print();
    // cout << "===============================\n";
    // // cout << "rank(1602717496) = " << tree.rank(41) << endl;
    // cout << "size(): " << tree.size() << endl;
    // cout << "kth(): " << tree.kth(4) << endl;
    // tree.print();
    // cout << "=========================================\n";
    // cout << "find_max():" << tree.find_next(5) << endl;
    // tree.remove(20);
    // cout << "after remove(): " << endl;
    // tree.splay(4);
    // tree.splay(5);
    // tree.print();

    cout << tans << "\n";
}
