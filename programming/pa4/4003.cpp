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
    int find_cost()
    {
        cost = 0;
        for (int i = 1; i < n; ++i)
            cost = cost + adj_matrix[sequence[i]][sequence[i + 1]];
        cost += adj_matrix[1][n];
        return cost;
    }
    void generate()
    {
        bool book[501] = {0};
        for (int i = 1; i <= n; ++i)
        {
            int x = rand() % n + 1;
            while (book[x] == 1)
            {
                x = rand() % n + 1;
            }
            book[x] = 1;
            sequence[i] = x;
        }
    }

    void disturb(int round)
    {
        // round = max(round, n / 2);
        // bool book[501] = {0};
        for (int i = 0; i < round; ++i)
        {
            int x = rand() % n + 1;
            // while (book[x] == 1)
            // {
            // cout << "faq\n";
            // x = rand() % n + 1;
            // }
            // book[x] = 1;
            int y = rand() % n + 1;
            while (y == x) //|| book[y] == 1)
            {
                // cout << "faq_y\n";
                // cout << "x = " << x << ", y = " << y << endl;
                y = rand() % n + 1;
            }
            // book[y] = 1;
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

Trial annealing()
{
#define T0 1e8
    double e = 0.99;
#define ITER 150
    double temperature = T0;

    Trial trial;
    srand((int)time(nullptr));
    clock_t start, now;
    start = clock();
    trial.generate();
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
            int dist_rate = rand() % 3 + 1;
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

    Trial ans = annealing();
    // ans.print();
    // for (int i = 0; i < 2; ++i)
    // {
    //     Trial trial_1 = annealing();
    //     trial_1.print();
    //     // cout << "cost : "<<trial_1.cost << endl;
    //     if (trial_1.cost < ans.cost)
    //     {
    //         ans = trial_1;
    //     }
    // }
    ans.print();
    // ans.print_ans();

    for (int i = 1; i <= n; ++i)
    {
        delete[] adj_matrix[i];
    }
    delete[] adj_matrix;
    return 0;
}