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

int main()
{
    int t;
    scan_f(t);
    for (int s = 0; s < t; ++s)
    {

        int n;
        scan_f(n);
        int *arr = new int[n - 1];
        int x;
        scan_f(x);
        for (int i = 0; i < n - 1; ++i)
        {
            int y;
            scan_f(y);
            if (x - y < 0)
                arr[i] = y - x;
            // else if (x - y == 0)
            //     arr[i] = x;
            else
                arr[i] = x - y;
            x = y;
        }
        --n;

        bool is_all_one = true;
        for (int i = 0; i < n; ++i)
        {
            if (arr[i] != 1)
            {
                is_all_one = false;
                break;
            }
        }
        if (is_all_one)
        {
            cout << 1 << endl;
            continue;
        }

        // for (int i = 0; i < n; ++i)
        //     cout << arr[i] << " ";
        // cout << endl;

        int p = 0;
        int q = 0;

        int res = 0;

        while (p < n)
        {
            int g = arr[p];
            int x;
            q = p + 1;
            // bool is_legal = false;
            while (q < n)
            {
                g = gcd(g, arr[q]);
                if (g == 1)
                {
                    // if (is_legal)
                    res = max(res, q - p);
                    break; // the current q is the first value illegal
                }
                // is_legal = true;
                ++q;
            }
            // cout << "p = " << p << ", q = " << q << endl;
            if (q >= n)
            {
                // if (is_legal)
                res = max(res, q - p);
                break;
            }
            int i = q;
            g = arr[q];
            while (i > p)
            {
                g = gcd(g, arr[i]);
                if (g == 1)
                {
                    res = max(res, q - i);
                    break; // the current i is the last value illegal, the next p should start as i
                }
                --i;
            }
            // cout << "i = " << i << endl;
            p = i + 1;
            // cout << "then p: " << p << endl;
        }
        cout << 1 + res << endl;
        delete[] arr;
    }
    return 0;
}