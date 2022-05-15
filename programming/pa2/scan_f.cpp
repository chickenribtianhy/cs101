#include <iostream>
using namespace std;

bool scan_f(int &x)
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

int main()
{
    int n;
    scan_f(n);
    cout << n;

    return 0;
}