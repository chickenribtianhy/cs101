#include <iostream>
using namespace std;

class LinkedNode
{
public:
	LinkedNode(int i)
	{
		info = i;
		next = nullptr;
	}
	LinkedNode *next;
	int info;
};

class List
{
public:
	List()
	{
		head = nullptr;
		tail = nullptr;
	}
	List(LinkedNode *r)
	{
		head = r;
		tail = r;
	}
	void push(LinkedNode *obj)
	{
		if (tail == nullptr)
		{
			head = obj;
			tail = obj;
			return;
		}
		tail->next = obj;
		tail = obj;
	}
	LinkedNode *head;
	LinkedNode *tail;
};

class BinaryHeap
{
private:
	int *arr;
	int size;

public:
	BinaryHeap(int n)
	{
		arr = new int[n + 1];
		size = 0;
	}
	void print()
	{
		cout << "heap: ";
		for (int i = 1; i <= size; ++i)
		{
			cout << arr[i] << " ";
		}
		cout << endl;
	}

	void procolate(int x)
	{
		if (x == 1)
			return;
		int c = x / 2;
		while (c > 0)
		{
			if (arr[x] >= arr[c])
				return;
			swap(arr[x], arr[c]);
			x = c;
			c = x / 2;
		}
	}

	void procolate_down(int x)
	{
		int c = 2 * x;
		if (c > size)
			return;

		while (c <= size)
		{
			if (c + 1 > size)
			{
				if (arr[x] > arr[c])
					swap(arr[x], arr[c]);
				return;
			}
			bool c0 = (arr[c] > arr[c + 1]);
			if (arr[x] > arr[c + c0])
			{
				swap(arr[x], arr[c + c0]);
				x = c + c0;
				c = 2 * x;
			}
			else
			{
				return;
			}
		}
	}

	void push(int v)
	{
		++size;
		arr[size] = v;
		procolate(size);
	}
	int pop()
	{
		int res = arr[1];
		arr[1] = arr[size];
		--size;
		procolate_down(1);
		return res;
	}
};
int n, m;

class Node
{
public:
	int value;
	List adj_list;

	Node()
	{
	}
	void link(int x)
	{
		LinkedNode *ptr = new LinkedNode(x);
		if (adj_list.head == nullptr)
		{
			adj_list.head = ptr;
			adj_list.tail = ptr;
		}
		else
		{
			adj_list.tail->next = ptr;
			adj_list.tail = ptr;
		}
	}
	void print()
	{
		cout << "linked with: ";
		LinkedNode *p = adj_list.head;
		cout << p->info << " ";
		while (p != adj_list.tail)
		{
			p = p->next;
			cout << p->info << " ";
		}
		cout << endl;
	}
};

int main()
{
	cin >> n >> m;
	int *answer = new int[n + 1];
	int cnt = 1;
	Node *nodes = new Node[n + 1];

	for (int i = 0; i < m; ++i)
	{
		int x, y;
		cin >> x >> y;
		nodes[x].link(y);
		nodes[y].link(x);
	}

	BinaryHeap heap(n);
	heap.push(1);
	bool *book = new bool[n + 1];
	for (int i = 0; i <= n; ++i)
		book[i] = false;

	book[1] = true;
	while (cnt <= n)
	{
		int x = heap.pop();
		answer[cnt] = x;
		++cnt;
		LinkedNode *ptr = nodes[x].adj_list.head;
		while (ptr != nullptr)
		{
			if (!book[ptr->info])
			{
				heap.push(ptr->info);
				book[ptr->info] = true;
			}
			ptr = ptr->next;
		}
		// heap.print();
	}

	for (int i = 1; i <= n; ++i)
	{
		cout << answer[i] << " ";
	}
	cout << endl;

	return 0;
}