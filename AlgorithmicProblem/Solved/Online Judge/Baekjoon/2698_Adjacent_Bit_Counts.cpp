#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <vector>
#include <set>
#include <string>
using namespace std;

void recursive(int n, int k, vector<int>& numbers, set<string>& ret)
{
	if (numbers.size() == n)
	{
		int count = 0;
		string str = to_string(numbers[0]);
		for (int i = 1; i < n; i++)
		{
			str += to_string(numbers[i]);
			if (numbers[i - 1] == 1 && numbers[i] == 1)
				count++;
		}
		if (count == k)
			ret.insert(str);
	}

	for (int i = numbers.size(); i < n; i++)
	{
		numbers.push_back(1);
		recursive(n, k, numbers, ret);
		numbers[i] = 0;
		recursive(n, k, numbers, ret);
		numbers.pop_back();
	}
}

int main()
{
	int cases, n, k;
	cin >> cases;
	for (int c = 0; c < cases; c++)
	{
		cin >> n >> k;
		vector<int> numbers;
		set<string> ret;
		recursive(n, k, numbers, ret);
		cout << ret.size() << endl;
	}

	return 0;
}