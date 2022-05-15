#include <iostream>
using namespace std;

bool scan_f(int &x) //faster input
{
    char c;
    c = getchar();
    if (c == EOF)
        return false;
    while (c < '0' || c > '9')
        c = getchar();
    x = c - '0';
    while (c = getchar(), c >= '0' && c <= '9')
    {
        x *= 10;
        x += (c - '0');
    }
    return true;
}

int gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    int c = a % b;
    while (c != 0)
    {
        a = b;
        b = c;
        c = a % b;
    }
    return b;
}
int divideAndConquer(int arr[], int head, int tail)
{
    if (tail - head == 1)
    {
        if (arr[head] == 1)
            return 0;
        else
            return 1;
    }

    int mid = (head + tail) / 2;
    int res1 = divideAndConquer(arr, head, mid);
    int res2 = divideAndConquer(arr, mid, tail);
    cout << "merging...\n";
    for (int i = head; i < tail; ++i)
        cout << arr[i] << " ";
    cout << endl;

    int x = mid - 1;
    int y = mid;
    int t = gcd(arr[x], arr[y]); //4
    if (t == 1)
        return max(res1, res2);

    int *f = new int[tail - head];

    f[mid - head] = arr[mid];
    int right = tail; //arr[]
    for (int k = mid + 1; k < tail; ++k)
    {
        f[k - head] = gcd(arr[k], f[k - head - 1]);
        // if (f[k - head] == 1)
        // {
        //     right = k;
        //     break;
        // }
    }

    f[mid - head - 1] = arr[mid - 1];
    int left = head;
    for (int k = mid - 2; k >= head; --k) //arr[]
    {
        f[k - head] = gcd(arr[k], f[k - head + 1]);
        // if (f[k - head] == 1)
        // {
        //     left = k + 1;
        //     break;
        // }
    }

    for (int i = 0; i < tail - head; ++i)
        cout << f[i] << " ";
    cout << endl;

    int res3 = 0;

    // int i = mid - 1;
    // int j = right - 1;
    int i = mid - 1;
    int j = tail - 1;
    while (i >= left)
    {
        while (j >= mid)
        {
            int tmp = gcd(f[j - head], f[i - head]);
            if (tmp == 1)
            {
                j--;
            }
            else
                break;
        }
        if (gcd(f[i - head], f[j - head]) == 1)
        {
            --i;
            continue;
        }
        res3 = max(j - i + 1, res3);
        cout << "in loop: " << res3 << " i = " << i << " , j = " << j << endl;
        --i;
    }

    cout << res3 << endl;
    res1 = max(res1, res2);
    res3 = max(res1, res3);
    delete[] f;
    return res3;
}

int main()
{
    int t;
    scan_f(t);
    for (int k = 0; k < t; ++k)
    {
        int n;
        scan_f(n);
        if (n == 1)
        {
            int y;
            scan_f(y);
            std::cout << 1 << endl;
            return 0;
        }
        int *arr = new int[n - 1];
        int x;
        cin >> x;
        for (int i = 0; i < n - 1; ++i)
        {
            int y;
            scan_f(y);
            arr[i] = x - y;
            if (arr[i] < 0)
            {
                arr[i] = -arr[i];
            }
            x = y;
        }
        --n;
        for (int i = 0; i < n; ++i)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
        std::cout << divideAndConquer(arr, 0, n) + 1 << endl;

        delete[] arr;
    }
    return 0;
}