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

    void disturb(int round)
    {
        for (int i = 0; i < round; ++i)
        {
            int x = rand() % n + 1;
            int y = rand() % n + 1;
            while (y == x) //|| book[y] == 1)
            {
                y = rand() % n + 1;
            }
            swap(sequence[x], sequence[y]);
        }
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

Trial annealing(Trial trial)
{
#define T0 1e8
    double e = 0.99;
#define ITER 150
    double temperature = T0;

    srand((int)time(nullptr));
    clock_t start, now;
    start = clock();
    int temp_cost = trial.find_cost(); // 1-1000 times 50, 1e4
    // trial.print();
    // cout << "after disturbence..." << endl;
    // trial.disturb(3);
    // trial.print();

    Trial best;
    best = trial;
    best.find_cost();

    while (temperature > 1e-9)
    {
        // cout << "faq\n";
        int i = 1;
        while (i <= ITER)
        {
            // cout << "iter: " << i << endl;
            int dist_rate = rand() % 20 + 1;
            Trial trial_1;
            trial_1 = trial;
            trial_1.disturb(2);
            // trial.disturb(dist_rate);
            int difference = trial_1.find_cost() - temp_cost; // 1e4
            if (trial.cost < best.cost)
            {
                best = trial_1;
            }
            double prob;
            if (difference <= 0) // better
            {
                prob = 1;
            }
            else
            {
                prob = 1 / exp(difference / temperature); //more diff, less possible;
                // prob = 0;
                // cout << "faq\n";
            }
            //bernoulli trial:
#define N 1000000
            double judger = (rand() % N) / (double)(N - 1);
            // cout << "judger = " << judger << ", prob = " << prob << endl;
            if (judger <= prob)
            {
                //do
                trial = trial_1;
                temp_cost = trial.find_cost();
            }
            ++i;
        }
        temperature *= e;
        // e = e * 0.99999;
    }
    // trial.print_ans();
    // cout << endl;
    // trial.print();
    // best.print();
    return best;
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

    ans = annealing(ans);
    ans.print();
    // ans.print_ans();

    for (int i = 1; i <= n; ++i)
    {
        delete[] adj_matrix[i];
    }
    delete[] adj_matrix;
    return 0;
}