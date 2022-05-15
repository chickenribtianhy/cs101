#include <iostream>
using namespace std;

class Point
{
public:
    Point() : m_x(0), m_y(0) {}
    Point(int x, int y) : m_x(x), m_y(y) {}

    float get_distance_square(Point &p)
    {
        return (m_x - p.m_x) * (m_x - p.m_x) + (m_y - p.m_y) * (m_y - p.m_y);
    }
    void print()
    {
        cout << m_x << " " << m_y << endl;
    }

    int m_x;
    int m_y;
    int dist1;
    int dist2;
};

void quick_sort(Point *arr[], int start, int end)
{
    if (start > end)
        return;
    Point *pivot = arr[start];
    int left = start;
    int right = end;
    while (left < right)
    {
        while (arr[right]->dist1 <= pivot->dist1 && left < right)
            --right;
        while (arr[left]->dist1 >= pivot->dist1 && left < right)
            ++left;
        if (left < right)
            swap(arr[left], arr[right]);
    }
    swap(arr[start], arr[left]);
    quick_sort(arr, start, left - 1);
    quick_sort(arr, left + 1, end);
}

int main()
{
    int x, y;
    cin >> x >> y;
    Point tower_1(x, y);
    cin >> x >> y;
    Point tower_2(x, y);
    int radius_square_1, radius_square_2;
    radius_square_1 = radius_square_2 = 0;

    int n;
    cin >> n;

    Point *arr1[80001];
    // Point *arr2[80000];

    for (int i = 0; i < n; ++i)
    {
        cin >> x >> y;
        arr1[i] = new Point(x, y);
        arr1[i]->dist1 = arr1[i]->get_distance_square(tower_1);
        arr1[i]->dist2 = arr1[i]->get_distance_square(tower_2);
    }

    // for (int i = 0; i < n; ++i)
    //     cout << arr1[i]->dist1 << " " << arr1[i]->dist2 << endl;

    // cout << endl
    //      << endl;
    arr1[n] = new Point;
    arr1[n]->dist1 = 0;
    quick_sort(arr1, 0, n - 1);
    radius_square_1 = arr1[0]->dist1;

    // for (int i = 0; i < n; ++i)
    //     cout << arr1[i]->dist1 << " " << arr1[i]->dist2 << endl;

    // cout << endl
    //      << endl;
    int cost = radius_square_1;
    for (int i = 0; i < n; ++i)
    {
        radius_square_1 = arr1[i + 1]->dist1;
        // arr2[i] = arr1[i];
        radius_square_2 = max(radius_square_2, arr1[i]->dist2);

        cost = min(cost, radius_square_1 + radius_square_2);
        // cout << radius_square_1 << " " << radius_square_2 << " " << cost << endl;
    }
    for (int i = 0; i <= n; ++i)
    {
        delete arr1[i];
    }
    cout << cost << endl;

    return 0;
}
