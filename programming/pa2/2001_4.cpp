#include <iostream>
using namespace std;

struct Pair
{
	Pair()
	{
		one = 0;
		two = 0;
	}
	Pair(int o, int t)
	{
		one = o;
		two = t;
	}
	int one;
	int two;
};

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

class Node
{
public:
	Node() {}
	Node(int s)
	{
		support = s;
		father = 0;
	}
	void append(int index)
	{
		adj_list.push(new LinkedNode(index));
	}
	void print()
	{
		cout << "Node: support " << support << " father " << father << " adj_list: ";
		LinkedNode *i = adj_list.head;
		while (i != nullptr)
		{
			cout << i->info << " ";
			i = i->next;
		}
		cout << endl;
	}
	List adj_list;
	int support;
	int father;
};

Node **arr;
int n;
bool cut_yet = 0;
bool *book;
int total[3] = {0};

void find_father(int i)
{
	if (i > n)
		return;
	LinkedNode *j = arr[i]->adj_list.head;
	while (j != nullptr)
	{
		if (book[j->info])
		{
			j = j->next;
			continue;
		}
		arr[j->info]->father = i;
		book[j->info] = 1;
		find_father(j->info);
		j = j->next;
	}
}

int ans;
bool success = 1;

Pair dfs(int i)
{
	if (i > n || !success)
		return Pair();
	Pair pair;
	LinkedNode *j = arr[i]->adj_list.head;
	while (j != nullptr)
	{
		if (j->info == arr[i]->father)
		{
			j = j->next;
			continue;
		}
		Pair sub = dfs(j->info);
		// subtree
		if (sub.one * sub.two == 0)
		{
			if (sub.one == total[1] && sub.two == 0 || total[1] == 0)
				++ans;
			else if (sub.two == total[2] && sub.one == 0 || total[2] == 0)
				++ans;
			pair.one += sub.one;
			pair.two += sub.two;
		}
		// else
		// {
		// 	// we have to cut in this situation
		// 	cut_yet = true;
		// 	if()
		// }
		// myself
		// pair.one += sub.one;
		// pair.two += sub.two;
		j = j->next;
	}
	if (arr[i]->support == 1)
		++pair.one;
	else if (arr[i]->support == 2)
		++pair.two;
	// arr[i]->print();
	// cout << "pair: " << pair.one << ", " << pair.two << endl;
	return pair;
}

int main()
{
	std::ios::sync_with_stdio(false);
	cin >> n;
	arr = new Node *[n + 1];
	for (int i = 1; i <= n; ++i)
	{
		int s;
		cin >> s;
		++total[s];
		arr[i] = new Node(s);
	}
	for (int i = 1; i < n; ++i)
	{
		int x, y;
		cin >> x >> y;
		arr[y]->append(x);
		arr[x]->append(y);
	}

	// make arr[1] be the root
	book = new bool[n + 1];
	for (int i = 0; i <= n; ++i)
		book[i] = 0;
	book[1] = 1;
	find_father(1);
	// for (int i = 1; i <= n; ++i)
	// 	arr[i]->print();

	ans = 0;
	dfs(1);
	// cout << total[1] << " " << total[2] << endl;
	cout << ans << endl;
	return 0;
}