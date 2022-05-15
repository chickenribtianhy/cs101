#include <iostream>
using namespace std;

int main()
{
  int n;
    cin >> n;
    int c_1 = 0;
    int c_2 = 0;
    for (int i = 1; i <= n; ++i)
    {
        int s;
        cin >> s;
        if (s == 1)
            c_1=1;
        if (s == 2)
            c_2=1;
    }
    for (int i = 1; i < n; ++i)
    {
        int x, y;
        cin >> x >> y;
    }

    if (c_1 * c_2 == 0)
    {
        cout << n - 1 << endl;
        return 0;
    }
    cout<<0<<endl;

    return 0;
}