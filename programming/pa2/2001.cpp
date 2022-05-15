#include <iostream>
using namespace std;

class Node
{
public:
    Node()
    {
        count_edges = 0;
    }
    Node(int num, int x)
    {
        number = num;
        support = x;
        son_num = 0;
        count_edges = 0;
    }
    void Print()
    {
        cout << number << " support " << support << ", with: ";
        for (int i = 0; i < son_num; ++i)
        {
            // cout << adj[i]->number << " ";
        }
        cout << endl;
    }

    void append(Node *y)
    {
        // adj[son_num] = y;
        ++son_num;
    }

    int number;
    int support;
    int son_num;
    // Node *adj[];
    int count_edges;
};

class Edge
{
public:
    Edge()
    {
        a = -1;
        b = -1;
    }
    Edge(int x, int y)
    {
        a = x;
        b = y;
    }
    int a;
    int b;
    void print()
    {
        cout << a << " linked with " << b << endl;
    }
};
Edge **edges;
Node **arr_nodes;

/* void quick_sort_edges(Edge *arr[], int start, int end)
{
    cout << "faq2\n";
    if (start > end)
        return;
    Edge *pivot = arr[start];
    int left = start;
    int right = end;
    while (left < right)
    {
        while (left < right && arr[right]->a >= pivot->a)
            --right;
        while (left < right && arr[left]->a <= pivot->a)
            ++left;
        if (left < right)
            swap(arr[left], arr[right]);
    }
    swap(arr[start], arr[left]);
    quick_sort_edges(arr, start, left - 1);
    quick_sort_edges(arr, left + 1, end);
} */

void quick_sort_Nodes(Node *arr[], int start, int end)
{
    cout << "faq2\n";
    if (start > end)
        return;
    Node *pivot = arr[start];
    int left = start;
    int right = end;
    while (left < right)
    {
        while (left < right && arr[right]->count_edges >= pivot->count_edges)
            --right;
        while (left < right && arr[left]->count_edges <= pivot->count_edges)
            ++left;
        if (left < right)
            swap(arr[left], arr[right]);
    }
    swap(arr[start], arr[left]);
    quick_sort_Nodes(arr, start, left - 1);
    quick_sort_Nodes(arr, left + 1, end);
}

int main()
{
    //============preparation==============
    std::ios::sync_with_stdio(false);
    int n;
    cin >> n;
    edges = new Edge *[n];
    arr_nodes = new Node *[n + 1];

    for (int i = 1; i <= n; ++i)
    {
        int x;
        cin >> x;
        arr_nodes[i] = new Node(i, x);
    }
    for (int i = 0; i < n - 1; ++i)
    {
        int x, y;
        cin >> x >> y;
        if (x > y)
            swap(x, y);
        edges[i] = new Edge(x, y);
        ++arr_nodes[x]->count_edges;
        ++arr_nodes[y]->count_edges;
    }
    for (int i = 1; i <= n; ++i)
    {
        cout << "edge number: " << arr_nodes[i]->count_edges << endl;
    }
    //=============sorting==============
    // quick_sort_Nodes(arr_nodes, 0, n - 1);
    // for (int i = 0; i < n - 1; ++i)
    // {
    //     arr_nodes[i]->Print();
    // }

    //=======father=========
    int *father = new int[n + 1];
    for (int i = 0; i <= n; ++i)
        father[i] = 0;
    for (int i = 0; i <= n - 2; ++i)
    { //edges[i]
        int x = edges[i]->a;
        int y = edges[i]->b;
        if (father[y] == 0)
        {
            father[y] = x;
        }
        else if (father[x]==0){
            father[x]=y;
        }else{
            int tmp=y;
            while(father[tmp]!=0){
                
            }
        }
    }
    //=============ending===========
    for (int i = 1; i <= n; ++i)
        delete arr_nodes[i];
    delete[] arr_nodes;
    for (int i = 0; i < n - 1; ++i)
        delete edges[i];
    delete[] edges;
    return 0;
}