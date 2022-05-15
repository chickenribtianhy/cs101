#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Pigeons
{
public:
    Pigeons(long long h, long long f) : hunger(h), food(f) {}
    long long hunger, food;
};

bool sortByFood(const Pigeons &a, const Pigeons &b)
{
    return a.food < b.food;
}

int main()
{
    int n, c;
    long long f;
    cin >> n >> c >> f;
    vector<long long> hungerValue;
    vector<Pigeons> pigeons;
    hungerValue.reserve(c);
    pigeons.reserve(c);
    for (int i = 0; i < c; i++)
    {
        long long a, b;
        cin >> a >> b;
        pigeons.emplace_back(a, b);
        hungerValue.push_back(a);
    }
    sort(hungerValue.begin(), hungerValue.end());
    sort(pigeons.begin(), pigeons.end(), sortByFood);
    vector<long long>::iterator it = unique(hungerValue.begin(), hungerValue.end());
    hungerValue.resize(distance(hungerValue.begin(), it));
    long long ans = -1;
    int left = 0, right = hungerValue.size() - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        long long totalFood = 0;
        int high = 0, low = 0;
        for (int i = 0; i < pigeons.size(); i++)
        {
            if (pigeons[i].hunger < hungerValue[mid])
            {
                if (low < n / 2)
                {
                    low++;
                    totalFood += pigeons[i].food;
                }
            }
            else
            {
                high++;
                totalFood += pigeons[i].food;
            }
            int total = high + low;
            if (total == n || totalFood > f)
            {
                break;
            }
        }
        if (high + low == n && totalFood <= f)
        {
            ans = max(ans, hungerValue[mid]);
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    cout << ans << endl;
}