#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

//https://www.acmicpc.net/problem/1013

bool finiteAutomata(vector<int>& numbers)
{
	int q = 0;
	int index = 0;
	while (true)
	{
		if (index == numbers.size())
			break;
		int num = numbers[index];

		switch (q)
		{
		case 0:
			if (num == 0)
				q = 1;
			else
				q = 3;
			break;

		case 1:
			if (num == 1)
				q = 2;
			else
				return false;
			break;

		case 2:
			if (num == 0)
				q = 1;
			else
				q = 3;
			break;

		case 3:
			if (num == 0)
				q = 4;
			else
				return false;
			break;

		case 4:
			if (num == 0)
				q = 5;
			else
				return false;
			break;

		case 5:
			if (num == 0)
				q = 5;
			else
				q = 6;
			break;

		case 6:
			if (num == 0)
				q = 8;
			else
				q = 7;
			break;

		case 7:
			if (num == 0)
				q = 9;
			else
				q = 7;
			break;

		case 8:
			if (num == 1)
				q = 2;
			else
				return false;
			break;

		case 9:
			if (num == 0)
				q = 5;
			else
				q = 2;
			break;
		default:
			break;
		}
		index++;
	}

	if (q == 2 || q == 6 || q == 7)
		return true;
	else
		return false;
}

int main()
{
	int cases;
	cin >> cases;
	for (int i = 0; i < cases; i++)
	{
		string str;
		cin >> str;

		vector<int> numbers;

		for (int i = 0; i < str.size(); i++)
			numbers.push_back(str[i] - '0');

		if (finiteAutomata(numbers))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}

	return 0;
}
