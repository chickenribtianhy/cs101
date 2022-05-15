#include <iostream>
using namespace std;

class Queue
{
public:
    int *arr;
    int head;
    int tail;
    Queue(int n)
    {
        arr = new int[n];
        head = 0;
        tail = 0;
    }
    void push(int val)
    {
        arr[tail] = val;
        ++tail;
    }
    int pop()
    {
        if (head == tail)
        {
            return -1;
        }
        ++head;
        return arr[head - 1];
    }
    ~Queue()
    {
        delete[] arr;
    }
    bool is_empty()
    {
        return (head == tail);
    }
};
int n;
int *a;
int *b;
int *dp;
bool *book;

int bfs()
{
    Queue sequence(n);
    sequence.push(n);
    book[n] = true;
    dp[n] = 0;
    int opt = n + 1;
    int cnt = 0;
    bool runningstatus = true;
    while (!sequence.is_empty())
    {
        int x = sequence.pop();
        // cout << "x = " << x << endl;
        ++cnt;
        if (x - a[x] <= 0)
        {
            return dp[x] + 1;
            // return cnt;
        }
        //opt
        runningstatus = false;
        // cout << "opt-1 = " << opt - 1 << endl;
        // for (int i = max(x - opt + 1, a[x] - 5000); i <= a[x] && x - i > 0; ++i)
        for (int i = x - opt + 1; i <= a[x] && x - i > 0; ++i)
        {
            // cout << "trying... " << x - i << endl;
            if (x - i + b[x - i] >= n || book[x - i + b[x - i]])
            {
                continue;
            }
            // cout << "pushing... " << x - i + b[x - i] << endl;
            sequence.push(x - i + b[x - i]);
            book[x - i + b[x - i]] = true;
            dp[x - i + b[x - i]] = dp[x] + 1;
            // cout << "dp[x] = " << dp[2] << endl;
            runningstatus = true;
        }
        opt = min(opt, x - a[x]);
        // cout << "opt = " << opt << endl;
    }
    // for (int i = 1; i <= n; ++i)
    // {
    //     cout << dp[i] << " ";
    // }
    return -1;
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin >> n;
    a = new int[n + 1];
    b = new int[n + 1];
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i <= n; ++i)
        cin >> b[i];

    dp = new int[n + 1];
    book = new bool[n + 1];
    for (int i = 1; i <= n; ++i)
        book[i] = false;
    int ans = bfs();

    cout << ans << endl;
    delete[] a;
    delete[] b;
    delete[] dp;
    return 0;
}