#include <iostream>
#include <time.h>
#include <math.h>
using namespace std;

int n;
int **adj_matrix;

struct Trial
{
    int sequence[501] = {0};
    int cost;
    int counter;
    Trial()
    {
        counter = 0;
        cost = 0;
    }
    int find_cost()
    {
        cost = 0;
        for (int i = 1; i < n; ++i)
            cost = cost + adj_matrix[sequence[i]][sequence[i + 1]];
        cost += adj_matrix[1][n];
        return cost;
    }
    int start()
    {
        sequence[1] = rand() % n + 1;
        counter = 1;
        return sequence[1];
    }
    void move(int j)
    {
        // cout << "counter = " << counter << endl;
        ++counter;
        // cout<<"faq in class\n";
        sequence[counter] = j;
        // print();
    }

    void print_ans()
    {
        for (int i = 1; i <= n; ++i)
            cout << sequence[i] << " ";
        cout << endl;
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

#define rho 0.7  // volatility coefficient
#define alpha 1  // weight on ph eromone
#define beta 10  // weight on visibility
#define Q 1500.0 // constant of pheromone
#define M 15     // number of ants
double pow_of_beta(double x)
{
    double res = 1;
    for (int i = 0; i < beta; ++i)
        res *= x;
    return res;
}

Trial ACO()
{
    Trial ans;
    ans.cost = 1e6;
    srand((int)time(nullptr));
    double phero[501][501]; // pheromone
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            phero[i][j] = 1;
    double vis[501][501]; // visibility
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            if (i == j)
            {
                vis[i][j] = 0;
            }
            vis[i][j] = pow_of_beta(1.0 / adj_matrix[i][j]);
        }

#define T 50                    // loops
    for (int t = 0; t < T; ++t) // iterations
    {
        // int L[M] = {0};
        double delta[501][501] = {0};
        for (int k = 0; k < M; ++k) // motion of each ant
        {
            bool book[n + 1] = {0};
            Trial ant_trial;
            book[ant_trial.start()] = true;
            for (int i = 1; i < n; ++i) // n-1 movements
            {
                double indicator = (double)((rand() % 1000) / 1000.0); // [0,1)
                double prob_sum = 0;
                double prob[501] = {0};
                for (int j = 1; j <= n; ++j) // for every possible stop
                {
                    // now at sequence[i]
                    if (book[j] == false && adj_matrix[ant_trial.sequence[i]][j] != 0)
                    {
                        prob[j] = (phero[ant_trial.sequence[i]][j] * vis[ant_trial.sequence[i]][j]);
                        prob_sum += prob[j];
                    }
                    else
                    {
                        prob[j] = 0;
                    }
                }
                // cout << "prob_sum = " << prob_sum << endl;
                // cout << "indicator = " << indicator << endl;
                double counting_prob = 0;
                for (int j = 1; j <= n; ++j)
                {
                    prob[j] /= prob_sum;
                    // cout << "prob[j] = " << prob[j] << endl;
                    counting_prob += prob[j];
                    if (book[j] == 1 || adj_matrix[ant_trial.sequence[i]][j] == 0)
                        prob[j] = 0;
                    if (counting_prob > indicator && book[j] == false) // then go to j
                    {
                        ant_trial.move(j);
                        book[j] = true;
                        break;
                    }
                }
            }
            // cout << "booking...\n";
            // for (int i = 1; i <= n; ++i)
            // {
            //     cout << book[i] << " ";
            // }
            // cout << endl;
            int L = ant_trial.find_cost();
            if (L < ans.cost)
            {
                ans = ant_trial;
            }
            double inc = Q / L;
            for (int i = 1; i < n; ++i) // delta of pheromone
            {
                int x = ant_trial.sequence[i];
                int y = ant_trial.sequence[i + 1];
                delta[x][y] += inc;
            }
        }
        // after the moving of all ants, update the pheromone matrix
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                phero[i][j] = rho * phero[i][j] + delta[i][j];
            }
        }
    }
    return ans;
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
    Trial ans;
    ans = ACO();
    ans.print_ans();
    ans.print();

    for (int i = 1; i <= n; ++i)
    {
        delete[] adj_matrix[i];
    }
    delete[] adj_matrix;
    return 0;
}