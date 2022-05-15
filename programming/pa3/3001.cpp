#include <iostream>
using namespace std;

class DisjointSet
{
private:
    int *arr;
    int *gain;
    int n;

public:
    DisjointSet(int n);
    int find(int x);
    void set_union(int x, int y);
    int solve();
    void print()
    {
        cout << "arr: ";
        for (int i = 1; i <= n; ++i)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
        cout << "gain: ";
        for (int i = 1; i <= n; ++i)
        {
            cout << gain[i] << " ";
        }
        cout << endl;
    }
};

DisjointSet::DisjointSet(int nn)
{
    n = nn;
    arr = new int[n + 1];
    for (int i = 0; i <= n; ++i)
    {
        arr[i] = i;
    }
    gain = new int[n + 1];
    for (int i = 0; i <= n; ++i)
    {
        gain[i] = -1;
    }
}

int DisjointSet::find(int x)
{
    if (arr[x] == x)
    {
        return x;
    }
    int master = find(arr[x]);
    arr[x] = master;
    return master;
}

void DisjointSet::set_union(int x, int y)
{
    int fx = find(x);
    int fy = find(y);
    if (fx == fy)
    {
        ++gain[fx];
        return;
    }
    arr[fy] = fx;
    gain[fx] = gain[fx] + gain[fy] + 1;
}
int DisjointSet::solve()
{
    int res = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (arr[i] == i)
        {
            // cout << "father " << i << ", arr: " << arr[i] << endl;
            if (gain[i] > 0)
            {
                res += gain[i];
            }
        }
    }
    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    DisjointSet set_1(n);
    for (int i = 0; i < m; ++i)
    {
        int x, y;
        cin >> x >> y;
        set_1.set_union(x, y);
        // set_1.print();
        // cout << "i: " << i << " m: " << m << endl;
    }
    // int ans = ;
    // cout << endl;
    // set_1.print();
    cout << set_1.solve() << endl;

    return 0;
}