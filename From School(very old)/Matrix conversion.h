#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

const int n = 4;

double a[10][10];

void add(int s1, int s2, double k, string type)
{
	if (type == "st")
		for (int j = 0; j < n; j++)
			a[s1][j] += a[s2][j] * k;
	else
		for (int i = 0; i < n; i++)
			a[i][s1] += a[i][s2] * k;
}

void swap(int s1, int s2, string type)
{
	if (type == "st")
		for (int j = 0; j < n; j++)
			swap(a[s1][j], a[s2][j]);
	else
		for (int i = 0; i < n; i++)
			swap(a[i][s1], a[i][s2]);
}

void div(int s1, double k, string type)
{
	if (type == "st")
		for (int j = 0; j < n; j++)
			a[s1][j] /= k;
	else
		for (int i = 0; i < n; i++)
			a[i][s1] /= k;
}

void mult(int s1, double k, string type)
{
	if (type == "st")
		for (int j = 0; j < n; j++)
			a[s1][j] *= k;
	else
		for (int i = 0; i < n; i++)
			a[i][s1] *= k;
}

void write()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << a[i][j] << ' ';
		cout << endl;
	}

	cout << endl;
}


int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> a[i][j];

	string s, type;

	cout << fixed << setprecision(0);

	while (cin >> s)
	{
		cin >> type; 

		if (s == "swap")
		{
			int s1, s2;
			cin >> s1 >> s2;
			s1--; s2--;
			swap(s1, s2, type);
		}

		if (s == "add")
		{
			int s1, s2; double k;
			cin >> s1 >> s2 >> k;
			s1--; s2--;
			add(s1, s2, k, type);
		}

		if (s == "div")
		{
			int s1; double k;
			cin >> s1 >> k;
			s1--;
			div(s1, k, type);
		}

		if (s == "mult")
		{
			int s1; double k;
			cin >> s1 >> k;
			s1--;
			mult(s1, k, type);
		}

		write();
	}

    return 0;
}

/*Example in:
1 0 0 0
0 1 0 0
0 0 1 0
0 0 0 1
add st 2 4 1
add st 1 4 -2
add st 2 3 3
add st 1 3 -3
add st 1 2 6*/

