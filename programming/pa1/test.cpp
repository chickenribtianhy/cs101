#include <bits/stdc++.h>
using namespace std;

int a[80000];
int b[80000];
int dist[90000][2];
int max1;
int res = 999999999;
int cmp;

int MAX(int arr[])
{
	int flag;
	max1 = 0;
	for (int i = 0; i < sizeof(arr); i++)
	{
		if (arr[i] >= max1)
		{
			max1 = arr[i];
			flag = i;
		}
	}
	return flag;
}

int main()
{
	memset(b, 0, sizeof(b));
	int m1, n1, m2, n2;
	cin >> m1 >> n1 >> m2 >> n2;
	int N;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		int x1, y1;
		cin >> x1 >> y1;
		dist[i][0] = (x1 - m1) * (x1 - m1) + (y1 - n1) * (y1 - n1);
		dist[i][1] = (x1 - m2) * (x1 - m2) + (y1 - n2) * (y1 - n2);
		a[i] = dist[i][0];
	}
	for (int i = 0; i < N; i++)
	{
		int flag1 = MAX(a);
		int flag2 = MAX(b);
		int cmp = a[flag1] + b[flag2];
		res = min(cmp, res);
		//cout<<res<<endl;
		a[flag1] = -1;
		b[i] = dist[flag1][1];
	}
	cout << res << endl;
	return 0;
}