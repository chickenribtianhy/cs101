#include <iostream>
using namespace std;

class Person
{
public:
    Person()
    {
        num = -1;
        weight = 0;
    }
    Person(int n)
    {
        num = n;
        weight = 1;
    }
    void merge()
    {
        weight += 1;
    }
    int num;
    int weight;
};

int main()
{
    int n;
    cin >> n;
    Person *arr[500000];
    int tail = -1;
    int count = 0;
    for (int i = 0; i < n; ++i)
    {
        int x;
        cin >> x;
        // cout << x << ": tail=" << tail << endl;
        bool append = true;
        if (tail >= 0)
        {
            if (arr[tail]->num == x)
            {
                count += arr[tail]->weight;
                arr[tail]->merge();
                int k = 0;
                // while (k <= tail)
                // {
                //     cout << arr[k]->num << "(" << arr[k]->weight << ") ";
                //     ++k;
                // }
                // cout << count << endl;
                continue;
            }
        }

        if (tail > 0)
        {
            if (x > arr[tail]->num && arr[tail - 1]->num > arr[tail]->num)
            {

                count += 2 * arr[tail]->weight;
                delete arr[tail];
                --tail;

                if (tail > 0)
                {
                    while ((arr[tail]->num == x || x > arr[tail]->num && arr[tail - 1]->num > arr[tail]->num) && tail > 0)
                    {
                        if (arr[tail]->num == x && tail > 0)
                        {
                            count += arr[tail]->weight;
                            arr[tail]->merge();
                            append = false;
                            break;
                        }
                        if (x > arr[tail]->num && arr[tail - 1]->num > arr[tail]->num && tail > 0)
                        {
                            count += 2 * arr[tail]->weight;
                            delete arr[tail];
                            --tail;
                            if (tail == 0)
                            {
                                break;
                            }
                        }
                    }
                }
                if (tail == 0)
                {
                    bool is_same = arr[tail]->num == x;
                    if (is_same)
                    {
                        count += arr[tail]->weight;
                        arr[tail]->merge();
                        append = false;
                    }
                }
                if (append)
                {
                    ++tail;
                    arr[tail] = new Person(x);
                }
                // int k = 0;
                // while (k <= tail)
                // {
                //     cout << arr[k]->num << "(" << arr[k]->weight << ") ";
                //     ++k;
                // }
                // cout << count << endl;
                continue;
            }
        }

        if (append)
        {
            ++tail;
            arr[tail] = new Person(x);
        }

        // int k = 0;
        // while (k <= tail)
        // {
        //     cout << arr[k]->num << "(" << arr[k]->weight << ") ";
        //     ++k;
        // }
        // cout << count << endl;
    }

    //.................concluding.........................
    if (tail == 0)
    {
        cout << count << endl;
        delete arr[0];
        return 0;
    }
    if (tail == 1)
    {
        if (arr[0]->num < arr[1]->num)
        {
            count += arr[0]->weight;
        }
        else
        {
            count += arr[1]->weight;
        }
        cout << count << endl;
        delete arr[0];
        delete arr[1];
        return 0;
    }

    if (arr[0]->num < arr[1]->num)
    {
        count += arr[0]->weight;
    }
    if (arr[tail]->num < arr[tail - 1]->num)
    {
        count += arr[tail]->weight;
    }

    for (int i = 1; i <= tail - 1; ++i)
    {
        // count += arr[i]->weight;
        if (arr[i]->num < arr[i - 1]->num)
        {
            count += arr[i]->weight;
        }
        if (arr[i]->num < arr[i + 1]->num)
        {
            count += arr[i]->weight;
        }
    }
    for (int i = 0; i <= tail; ++i)
    {
        delete arr[i];
    }
    cout << count << endl;

    return 0;
}