#include <iostream>
#include <time.h>
#include <math.h>
using namespace std;

int n;
int **adj_matrix;

struct Trial
{
    int sequence[501];
    int cost;
    int cnt;
    Trial() { cnt = 0; }
    int find_cost()
    {
        cost = 0;
        for (int i = 1; i < n; ++i)
            cost = cost + adj_matrix[sequence[i]][sequence[i + 1]];
        cost += adj_matrix[n][1];
        return cost;
    }
    void append(int x)
    {
        cnt++;
        sequence[cnt] = x;
    }

    void print_ans()
    {
        for (int i = 1; i <= n; ++i)
            cout << sequence[i] << " ";
    }

    void print()
    {
        cout << "sequence is: ";
        for (int i = 1; i <= n; ++i)
        {
            cout << sequence[i] << " ";
        }
        cout << endl;
        cout << "distance is: " << find_cost() << endl;
    }
};

Trial greedy(int start)
{
    int num = 1;
    Trial trial;
    trial.append(start);
    int x = start;
    bool book[501] = {0};
    book[start] = 1;
    while (num <= n)
    {
        int min_index = 0;
        int min_val = 1001;
        for (int i = 1; i <= n; ++i)
        {
            if (book[i] == 0 && adj_matrix[x][i] <= min_val)
            {
                min_index = i;
                min_val = adj_matrix[x][i];
            }
        }
        num++;
        trial.append(min_index);
        book[min_index] = 1;
        x = min_index;
    }
    // trial.print();
    return trial;
}

int main()
{
    cin >> n;
    adj_matrix = new int *[n + 1];
    for (int i = 1; i <= n; ++i)
    {
        adj_matrix[i] = new int[n + 1];
        for (int j = 1; j <= n; ++j)
        {
            cin >> adj_matrix[i][j];
        }
    }
    Trial ans = greedy(1);

    for (int i = 2; i <= n; ++i)
    {
        Trial trial_1 = greedy(i);
        if (trial_1.find_cost() < ans.find_cost())
        {
            ans = trial_1;
        }
    }
    // ans.print();
    ans.print_ans();
    for (int i = 1; i <= n; ++i)
    {
        delete[] adj_matrix[i];
    }
    delete[] adj_matrix;
    return 0;
}