#include <iostream>
using namespace std;
int n, m;
int *firmness;
float final_res;

class Edge
{
private:
    int x;
    int y;
    int len;
    bool is_visited;

public:
    Edge() {}
    Edge(int a, int b)
    {
        is_visited = false;
        x = a;
        y = b;
        len = firmness[a] + firmness[b];
    }
    int get_len()
    {
        return len;
    }
    void print()
    {
        cout << firmness[x] << " -- " << firmness[y] << ", len = " << len << ", is_visit = " << is_visited << endl;
    }
    int get_x()
    {
        return x;
    }
    int get_y()
    {
        return y;
    }
    void visit()
    {
        is_visited = true;
    }
    bool get_visit()
    {
        return is_visited;
    }
    void change_len(int newlen)
    {
        len = newlen;
    }
    void unsvisit()
    {
        is_visited = false;
    }
};
Edge **edges;

void quicksort(Edge **arr, int start, int end)
{
    if (start > end)
        return;
    Edge *pivot = arr[start];
    int left = start;
    int right = end;
    while (left < right)
    {
        while (left < right && arr[right]->get_len() <= pivot->get_len())
            --right;
        while (left < right && arr[left]->get_len() >= pivot->get_len())
            ++left;
        if (left < right)
            swap(arr[left], arr[right]);
    }
    swap(arr[start], arr[left]);
    quicksort(arr, start, left - 1);
    quicksort(arr, left + 1, end);
}

class DisjointSet
{
private:
    int *disjoint_set;

public:
    DisjointSet()
    {
        disjoint_set = new int[n + 1];
        for (int i = 1; i <= n; ++i)
        {
            disjoint_set[i] = i;
        }
    }
    ~DisjointSet()
    {
        delete[] disjoint_set;
    }
    int find(int x)
    {
        if (disjoint_set[x] == x)
            return x;
        int master = find(disjoint_set[x]);
        disjoint_set[x] = master;
        return master;
    }
    bool set_union(int x, int y)
    {
        int fx = find(x);
        int fy = find(y);
        if (fx == fy)
        {
            return false;
        }
        disjoint_set[fy] = fx;
        return true;
    }
};


int kruskal()
{
    DisjointSet *set_1;
    set_1 = new DisjointSet();
    int edge_included = 0;
    int i = 0;
    int max_value = 0;

    while (edge_included < n - 1 && i < m)
    {
        // if (edges[i]->get_visit())
        // {
        //     ++i;
        //     continue;
        // }
        if (edges[i]->get_len() == -1)
        {
            ++i;
            continue;
        }
        int x = edges[i]->get_x();
        int y = edges[i]->get_y();
        // edges[i]->print();
        if (set_1->set_union(x, y))
        {
            edge_included++;
            edges[i]->visit();
            max_value += edges[i]->get_len();
            //update min_edge
        }
        ++i;
    }

    //int second_max = 0;
    //traverse unvisited edges

    //final_res = max_value / 1.0;
    // final_res = second_max;
    return max_value;
}

int main()
{
    std::ios::sync_with_stdio(false);
    //preperation
    cin >> n >> m;
    firmness = new int[n + 1];
    edges = new Edge *[m];

    for (int i = 1; i <= n; ++i)
    {
        cin >> firmness[i];
    }

    for (int i = 0; i < m; ++i)
    {
        int x, y;
        cin >> x >> y;
        edges[i] = new Edge(x, y);
    }

    quicksort(edges, 0, m - 1);
    // for (int i = 0; i < m; ++i)
    // {
    //     edges[i]->print();
    // }

    //kruskal

    int res;
    res = kruskal();
    if (n == m + 1)
    {
        printf("%.1f\n", ((float)res));
        return 0;
    }
    // cout << "========================================\n";
    // cout << res << endl;
    // cout << final_res << endl;
    bool *used = new bool[m];
    for (int i = 0; i < m; ++i)
    {
        used[i] = edges[i]->get_visit();
    }

    int second_max = 0;
    for (int i = 0; i < m; ++i)
    {
        if (!used[i])
        {
            continue;
        }
        int real = edges[i]->get_len();
        edges[i]->change_len(-1);
        // for (int j = 0; j < m; ++j)
        // {
        //     edges[j]->print();
        // }
        int res_1 = kruskal();
        // cout << res_1 << endl;
        edges[i]->change_len(real);
        second_max = max(second_max, res_1);
    }
    // cout << res << " " << second_max << endl;
    final_res = (res + second_max) / 2.0;

    printf("%.1f\n", final_res);

    //finish
    delete[] firmness;
    for (int i = 0; i < m; ++i)
    {
        delete edges[i];
    }
    delete[] edges;
    return 0;
}