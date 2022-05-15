#include <iostream>
using namespace std;

int n, c, f;
int ans;
bool is_found = false;

class Pigeon
{
public:
    Pigeon()
    {
        hunger = 0;
        food = 0;
        num = 0;
    }
    Pigeon(int a, int b, int p)
    {
        hunger = a;
        food = b;
        num = p;
    }
    void print()
    {
        std::cout << "pigeon: hunger = " << hunger << ", food = " << food << endl;
    }

    bool operator<(Pigeon &rhs)
    {
        return food < rhs.food;
    }
    int hunger;
    int food;
    int num;
};
Pigeon **pigeons;
int *hunger_arr;

void quick_sort(int arr[], int start, int end)
{
    if (start > end)
        return;
    int pivot = arr[start];
    int left = start;
    int right = end;
    while (left < right)
    {
        while (left < right && arr[right] >= pivot)
            --right;
        while (left < right && arr[left] <= pivot)
            ++left;
        if (left < right)
            swap(arr[left], arr[right]);
    }
    swap(arr[start], arr[left]);
    quick_sort(arr, start, left - 1);
    quick_sort(arr, left + 1, end);
}

void quick_sort_pigoens(Pigeon *arr[], int start, int end)
{
    if (start > end)
        return;
    Pigeon *pivot = arr[start];
    int left = start;
    int right = end;
    while (left < right)
    {
        while (left < right && arr[right]->food >= pivot->food)
            --right;
        while (left < right && arr[left]->food <= pivot->food)
            ++left;
        if (left < right)
            swap(arr[left], arr[right]);
    }
    swap(arr[start], arr[left]);
    quick_sort_pigoens(arr, start, left - 1);
    quick_sort_pigoens(arr, left + 1, end);
}

void binary_search(int start, int end)
{
    if (start > end)
        return;
    int mid = (start + end) / 2;
    int pivot = hunger_arr[mid]; // potential ans
    int food_needed = 0;
    int smaller = 0; //the number underconsideration with smaller hunger than hunger_arr[mid]
    int greater = 0; //that is greater ot equal
    bool is_break_for_max_n = 0;
    bool is_break_for_exceeded_f = 0;
    for (int i = 0; i < c; ++i)
    {
        if (pigeons[i]->hunger >= pivot)
        {
            ++greater;
            food_needed += pigeons[i]->food;
        }
        else
        {
            // make limit on smaller, and let greater in, if feasible, search greater, otherwise smaller
            if (smaller >= (n - 1) / 2)
                continue;
            ++smaller;
            food_needed += pigeons[i]->food;
        }

        if (greater + smaller == n)
        {
            is_break_for_max_n = 1;
            break;
        }
        if (food_needed > f)
        {
            is_break_for_exceeded_f = 1;
            break;
        }
    }
    // if(!is_break_for_exceeded_f)
    if (is_break_for_max_n && food_needed <= f)
    {
        ans = max(ans, pivot);
        is_found = 1;
        binary_search(mid + 1, end);
    }
    else if (food_needed > f)
    {
        binary_search(start, mid - 1);
    }
    else if (greater + smaller < n)
    {
        // cout << "hello" << end;
        binary_search(start, mid - 1);
    }
}

int main()
{
    //===========preparation==============
    std::ios::sync_with_stdio(false);
    cin >> n >> c >> f;
    ans = -1;
    pigeons = new Pigeon *[c];
    hunger_arr = new int[c];
    for (int i = 0; i < c; ++i)
    {
        int a, b;
        cin >> a >> b;
        pigeons[i] = new Pigeon(a, b, i);
        hunger_arr[i] = a;
    }
    // for (int i = 0; i < c; ++i)
    //     pigeons[i]->print();

    //==============sorting================
    quick_sort(hunger_arr, 0, c - 1);
    // for (int i = 0; i < c; ++i)
    //     cout << hunger_arr[i] << endl;
    quick_sort_pigoens(pigeons, 0, c - 1);
    // for (int i = 0; i < c; ++i)
    //     pigeons[i]->print();
    //============binary_search===========
    // int count = 0;
    // for (int i = 1; i < c; ++i)
    // {
    //     if (hunger_arr[i] == hunger_arr[i - 1])
    //         ++count;
    //     cout << hunger_arr[i] << " ";
    // }

    binary_search(0, c - 1);
    if (is_found)
        cout << ans << endl;
    else
        cout << -1 << endl;
    //===============end==============
    for (int i = 0; i < c; ++i)
        delete pigeons[i];

    delete[] pigeons;
    delete[] hunger_arr;
    return 0;
}