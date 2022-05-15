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

int bfs(int i)
{
    // arr[i]->print();
    if (i > n)
        return 0;

    int j = 0;
    int ans = arr[i]->support;
    int count_1 = 0;
    int count_2 = 0;

    while (arr[i]->linked_to[j] != '\0')
    {
        if (arr[i]->linked_to[j] - '0' == arr[i]->father)
        {
            ++j;
            continue;
        }
        int x = bfs(arr[i]->linked_to[j] - '0');
        // cout << "x = " << x << endl;
        //x = 0,1,2
        if (x == 1)
            ++count_1;
        if (x == 2)
            ++count_2;
        if (x == -1)
        {
            return -1;
        }
        ++j;
    }

    if (count_1 > 0 && count_2 > 0)
    {
        if (ans == 0)
        {
            if (!cut)
            {
                res = 0;
                return -1;
            }
            cut = false;
            if (count_1 == 1)
            {
                ++res;
            }
            if (count_2 == 1)
            {
                ++res;
            }
            if (count_1 > 1 && count_2 > 1)
            {
                res = 0;
            }
        }
        if (ans == 1)
        {
            if (!cut)
            {
                res = 0;
                return 0;
            }
            cut = false;
            if (count_2 == 1)
            {
                ++res;
            }
            else
            {
                res = 0;
            }
        }
        if (ans == 2)
        {
            if (!cut)
            {
                res = 0;
                return 0;
            }
            cut = false;
            if (count_1 == 1)
            {
                ++res;
            }
            else
            {
                res = 0;
            }
        }
    }
    else if (count_1 > 0)
    {
        if (ans == 1 || ans == 0)
        {
            ans = 1;
        }
        else
        {
            if (count_1 == 1)
            {
                if (!cut)
                {
                    res = 0;
                    return -1;
                }
                cut = false;
                ++res;
            }
        }
    }
    else if (count_2 > 0)
    {
        if (ans == 2 || ans == 0)
        {
            ans = 2;
        }
        else
        {
            if (count_2 == 1)
            {
                if (!cut)
                {
                    res = 0;
                    return -1;
                }
                cut = false;
                ++res;
            }
        }
    } /*
    cout << "res = " << res << " i = " << i << endl;
    cout << ans << endl; */
    // cout << "i=" << i << ", 1: " << count_1 << " , 2: " << count_2 << " ans: " << ans << ", res: " << res << " cut: " << cut << endl;

    return ans;
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin >> n;
    arr = new Node *[n + 1];
    int c_1 = 0;
    int c_2 = 0;
    for (int i = 1; i <= n; ++i)
    {
        int s;
        cin >> s;
        arr[i] = new Node(i, s);
    }
    int zero = 0;
    for (int i = 1; i < n; ++i)
    {
        int x, y;
        cin >> x >> y;
        arr[x]->add_edge(y);
        arr[y]->add_edge(x);
        if (arr[x]->support * arr[y]->support == 2)
            ++zero;
    }
    if (zero >= 2)
    {
        cout << 0 << endl;
        return 0;
    }
    book = new bool[n + 1];
    for (int i = 0; i <= n; ++i)
        book[i] = 0;
    int i = 1;
    while (c_1 * c_2 == 0 && i < n)
    {
        if (arr[i]->support == 1)
            c_1 = 1;
        if (arr[i]->support == 2)
            c_2 = 1;
        ++i;
    }

    if (c_1 * c_2 == 0)
    {
        cout << n - 1 << endl;
        return 0;
    }
    // for (int i = 1; i <= n; ++i)
    // {
    //     int j = 0;
    //     while (arr[i]->linked_to[j] != '\0')
    //     {
    //         if (arr[i]->support * arr[arr[i]->linked_to[j] - '0']->support == 2)
    //             zero++;
    //         ++j;
    //     }
    // }
    // cout << "z:" << zero << endl;

    // make arr[1] be root

    book[1] = 1;
    bfs_father(1);
    // for (int i = 1; i <= n; ++i)
    //     arr[i]->print();

    // for (int i = 0; i <= n; ++i)
    //     book[i] = 0;
    cut = true;
    res = 0;
    int g = bfs(1);
    // cout << "g = " << g << endl;

    cout << res << endl;

    return 0;
}