#include <iostream>
#include <time.h>
using namespace std;

int main()
{
    srand((int)time(nullptr));
    int n;
#define N 1000
    cin >> n;
    int matrix[501][501] = {0};
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (i == j)
            {
                matrix[i][j] = 0;
                continue;
            }
            else if (i > j)
            {
                int x = rand() % N + 1;
                // int y = cls_random::
                matrix[i][j] = x;
                matrix[j][i] = x;
            }
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}