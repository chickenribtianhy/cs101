#include <iostream>
using namespace std;

class Node
{
public:
    Node(int i, int s)
    {
        support = s;
        index = i;
        linked_to = "";
        father = 0;
    }
    void add_edge(int y)
    {
        char c = y + '0';
        linked_to += c;
    }
    void print()
    {
        cout << "node " << index << " father " << father << " support " << support << "\t linked with " << linked_to << endl;
    }

    // int *linked_to;
    string linked_to;
    int support;
    int index;
    int father;
};

Node **arr;
bool *book;
int n;
bool cut;
int res;

void bfs_father(int i)
{
    if (i > n)
        return;
    int j = 0;
    while (arr[i]->linked_to[j] != '\0')
    {
        // arr[i]->heir(arr[i]->linked_to[j]-'0'); //son
        if (book[arr[i]->linked_to[j] - '0'] == 0)
        {
            arr[arr[i]->linked_to[j] - '0']->father = i;
            book[arr[i]->linked_to[j] - '0'] = 1;
            bfs_father(arr[i]->linked_to[j] - '0');
        }
        ++j;
    }
}



int cnt[3] = {0};

int main()
{
    std::ios::sync_with_stdio(false);
    cin >> n;
    arr = new Node *[n + 1];

    for (int i = 1; i <= n; ++i)
    {
        int s;
        cin >> s;
        ++cnt[s];
        arr[i] = new Node(i, s);
    }
    for (int i = 1; i < n; ++i)
    {
        int x, y;
        cin >> x >> y;
        arr[x]->add_edge(y);
        arr[y]->add_edge(x);
    }
    book = new bool[n + 1];
    for (int i = 0; i <= n; ++i)
        book[i] = 0;

    book[1] = 1;
    bfs_father(1);

    bfs(1);

    return 0;
}