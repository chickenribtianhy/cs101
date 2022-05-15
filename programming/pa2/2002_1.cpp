#include <iostream>
using namespace std;

int gcd(int a, int b)
{
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
    // cin >> t;
    // for (int s = 0; s < t; ++s)
    // {

    int n;
    cin >> n;
    int *arr = new int[n];
    int x;
    cin >> x;
    for (int i = 0; i < n - 1; ++i)
    {
        int y;
        cin >> y;
        if (x - y < 0)
            arr[i] = y - x;
        else if (x - y == 0)
            arr[i] = x;
        else
            arr[i] = x - y;
        x = y;
    }
    --n;

    // for (int i = 0; i < n; ++i)
    //     cout << arr[i] << " ";
    // cout << endl;

    int p = 0;
    int q = 0;

    int res = 0;
    int left = p;
    int g = arr[p];

    while (p < n)
    {
        // g = arr[p];
        q = p + 1;
        while (q < n)
        {
            g = gcd(g, arr[q]);
            if (g == 1)
            {
                res = max(res, q - left);
                break; // the current q is the first value illegal
            }
            ++q;
        }
        if (q >= n)
        {
            res = max(res, q - left);
            break;
        }
        // cout << "p = " << p << ", left = " << left << ", q = " << q << endl;
        int i = q;
        g = arr[q];
        int tmp_g = g;
        while (i > p)
        {
            tmp_g = gcd(g, arr[i]);
            if (tmp_g == 1)
            {
                res = max(res, q - i);
                break; // the current i is the last value illegal, the next p should start as i+1, or actually q+1 with g
            }          // g is still the gcd from arr[i+1] to arr[q]
            g = tmp_g;
            --i;
        }
        // cout << "i = " << i << ", g = " << g << endl;
        left = i + 1;
        p = q;
    }
    cout << 1 + res << endl;
    // }
    return 0;
}