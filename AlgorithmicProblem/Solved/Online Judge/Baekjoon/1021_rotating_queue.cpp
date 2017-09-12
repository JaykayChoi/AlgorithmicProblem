#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <queue>
#include <list>
using namespace std;

//https://www.acmicpc.net/problem/1021

list<int> numbers;

void pushLeft()
{
	int temp = numbers.front();
	numbers.pop_front();
	numbers.push_back(temp);
}

void pushRight()
{
	int temp = numbers.back();
	numbers.pop_back();
	numbers.push_front(temp);
}

bool isLeftbetterThenRight(int target)
{
	int count = 0;
	for (list<int>::iterator it = numbers.begin(); it != numbers.end(); it++)
	{
		count++;
		if (*it == target)
			break;
	}
	if (count <= numbers.size() / 2 + 1)
		return true;
	else
		return false;
}

int main()
{
	int n, m;
	queue<int> needPopNumbers;

	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int num;
		cin >> num;
		needPopNumbers.push(num);
	}

	for (int i = 1; i <= n; i++)
		numbers.push_back(i);

	int ret = 0;
	while (needPopNumbers.empty() == false)
	{
		if (needPopNumbers.front() == numbers.front())
		{
			needPopNumbers.pop();
			numbers.pop_front();
		}
		else
		{
			if (isLeftbetterThenRight(needPopNumbers.front()))
				pushLeft();
			else
				pushRight();
			ret++;
		}
	}

	cout << ret << endl;

	return 0;
}
