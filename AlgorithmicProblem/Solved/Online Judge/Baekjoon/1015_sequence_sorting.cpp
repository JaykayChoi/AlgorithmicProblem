#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

//https://www.acmicpc.net/problem/1015
int main()
{
	int n;
	vector<int> numbers;
	cin >> n;
	multimap<int, bool> sortedNumbers;
	for (int i = 0; i < n; i++)
	{
		int num;
		cin >> num;
		numbers.push_back(num);
		sortedNumbers.insert(make_pair(num, false));
	}

	bool isFirst = true;
	for (vector<int>::iterator it = numbers.begin(); it != numbers.end(); it++)
	{
		int order = 0;
		for (multimap<int, bool>::iterator it2 = sortedNumbers.begin(); it2 != sortedNumbers.end(); it2++)
		{
			if (*it == it2->first && it2->second == false)
			{
				it2->second = true;
				break;
			}
			order++;
		}
		if (isFirst == false)
			cout << " ";
		else
			isFirst = false;
		cout << order;
	}
	cout << endl;

	return 0;
}
