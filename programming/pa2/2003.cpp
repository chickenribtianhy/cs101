#include <iostream>
using namespace std;

int *a;
int *b;
int **dp;
int *pigeons;
int n, c, f;
bool running_status;

void quick_sort(int arr[], int start, int end)
{
    if (start > end)
        return;
    int pivot = arr[start];
    int left = start;
    int right = end;
    while (left < right)
    {
        while (left < right && arr[right] <= pivot)
            --right;
        while (left < right && arr[left] >= pivot)
            ++left;
        if (left < right)
            swap(arr[left], arr[right]);
    }
    swap(arr[start], arr[left]);
    quick_sort(arr, start, left - 1);
    quick_sort(arr, left + 1, end);
}

bool dfs(int i, int j, int count)
{
    if (!running_status)
    {
        return true;
    }
    if (i <= 0)
    {
        return false;
    }
    if (dp[i][j] == dp[i - 1][j])
    {
        dfs(i - 1, j, count);
    }
    if (j - b[i] >= 0 && dp[i][j] == dp[i - 1][j - b[i]] + a[i])
    {
        pigeons[count] = a[i];
        if (count + 1 == n)
        {
            running_status = false;
            /* for (int i = 0; i < n; ++i)
            {
                cout << pigeons[i] << " ";
            }
            cout << endl; */
            quick_sort(pigeons, 0, n - 1);
            /* for (int i = 0; i < n; ++i)
            {
                cout << pigeons[i] << " ";
            }
            cout << endl; */
            cout << pigeons[n / 2] << endl;
            // exit;
        }
        dfs(i - 1, j - b[i], count + 1);
        pigeons[count] = 0;
    }
    return false;
}

int main()
{

    cin >> n >> c >> f;

    a = new int[c + 1];
    b = new int[c + 1];

    for (int i = 1; i <= c; ++i)
    {
        cin >> a[i]; // hunger degree (to maximize)
        cin >> b[i]; // cost
    }

    dp = new int *[c + 1]; // the number of items
    for (int i = 0; i <= c; ++i)
        dp[i] = new int[f + 1]; // the size of the bag

    for (int i = 0; i <= c; ++i)
        dp[i][0] = 0; // 0 income when the size of the bag is empty

    for (int j = 0; j <= f; ++j)
        dp[0][j] = 0; // 0 income when there is no item

    for (int i = 1; i <= c; ++i) // the i-th item
    {
        for (int j = 1; j <= f; ++j)
        {
            if (b[i] > j)
            {
                dp[i][j] = dp[i - 1][j];
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - b[i]] + a[i]);
            }
        }
    }

    // for (int i = 0; i <= c; ++i)
    // {
    //     for (int j = 0; j <= f; ++j)
    //     {
    //         printf("%d\t", dp[i][j]);
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    // recall the best solution:
    // well there can be many situations that satisfy, which is disgusting, but we want to find the one have n pigeons
    // so dfs can be better than a loop
    pigeons = new int[n];

    /* int i = c, j = f;
    while (i > 0 && j > 0)
    {
        cout << dp[i][j] << " " << b[i] << " " << j << endl;
        if (dp[i][j] == dp[i - 1][j])
        {
            pigeons[i] = 0;
            --i;
        }
        else
        {
            pigeons[i] = 1;
            // cout << "j = " << j << " , bi = " << b[i] << endl;
            j = j - b[i];
            --i;
            // cout << "j-bi = " << j << endl;
        }
    } */
    running_status = true;
    bool x = dfs(c, f, 0); // where 0 is we have 0 pigoens fed currently; true is the running status

    // for (int i = 0; i < n; ++i)
    // {
    //     cout << pigeons[i] << " ";
    // }
    // cout << endl;
    if (running_status)
    {
        cout << -1 << endl;
    }
    /* for (int i = 0; i <= c; ++i)
    {
        for (int j = 0; j <= f; ++j)
        {
            // cout << dp[i][j] << " ";
            printf("%d\t", x[i][j]);
        }
        cout << endl;
    } */
    // cout << dp[c][f] << endl;
    delete[] a;
    delete[] b;
    for (int i = 0; i < n + 1; ++i)
        delete[] dp[i];
    delete[] dp;
    return 0;
}
