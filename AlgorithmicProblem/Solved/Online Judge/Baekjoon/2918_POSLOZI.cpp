#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//https://www.acmicpc.net/problem/2918

struct Swap
{
	int a, b;
	Swap(int _a, int _b) : a(_a), b(_b) {};
};

int n, m;

vector<int> sortedSequence;
vector<Swap> swaps;
int minValue = 987654321;
vector<int> order;

bool isSorted(vector<int> a)
{
	for (int i = 0; i < n; i++)
	{
		if (sortedSequence[i] != a[i])
			return false;
	}
	return true;
}

void swap(vector<int>& seq, Swap method)
{
	int temp = seq[method.a];
	seq[method.a] = seq[method.b];
	seq[method.b] = temp;
}


vector<int> solve(vector<int>& seq, vector<int>& performed)
{
	if (isSorted(seq))
		return performed;

	for (int i = 0; i < m; i++)
	{
		swap(seq, swaps[i]);
		performed.push_back(i);
		vector<int> a = solve(seq, performed);
		if (a.size() < minValue)
		{
			minValue = a.size();
			order = a;
		}
		swap(seq, swaps[i]);
	}
}

int main()
{
	vector<int> sequence;
	cin >> n >> m;

	for (int i = 0; i < n; i++)
	{
		int num;
		cin >> num;
		sequence.push_back(num);
		sortedSequence.push_back(num);
	}
	sort(sortedSequence.begin(), sortedSequence.end());

	for (int i = 0; i < m; i++)
	{
		int num1, num2;
		cin >> num1 >> num2;
		Swap s(num1 - 1, num2 - 1);
		swaps.push_back(s);
	}
	vector<int> performed;
	solve(sequence, performed);

	cout << minValue << endl;
	for (vector<int>::iterator it = performed.begin(); it != performed.end(); it++)
		cout << *it << endl;

	system("pause");
	return 0;
}