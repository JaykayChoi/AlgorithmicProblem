#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <string>
#include <set>
using namespace std;

int main()
{
	int cases;
	cin >> cases;
	for (int c = 0; c < cases; c++)
	{
		string str, strNum;
		cin >> str;
		strNum = str;
		int largest = strNum[strNum.size() - 1] - '0';
		multiset<int> numbers;
		numbers.clear();
		numbers.insert(largest);
		for (int i = strNum.size() - 2; i >= 0; i--)
		{
			if (strNum[i] - '0' < largest)
			{
				int replaceNumber;
				for (auto& num : numbers)
				{
					if (num > strNum[i] - '0')
					{
						replaceNumber = num;
						break;
					}
				}
				multiset<int>::iterator it = numbers.find(replaceNumber);
				numbers.erase(it);
				numbers.insert(strNum[i] - '0');
				strNum[i] = replaceNumber + '0';
				int j = i + 1;
				for (auto& num : numbers)
				{
					strNum[j] = num + '0';
					j++;
				}
				break;
			}
			else if (largest < strNum[i] - '0')
			{
				largest = strNum[i] - '0';
			}
			numbers.insert(strNum[i] - '0');
		}
		if (str == strNum)
			cout << "BIGGEST" << endl;
		else
			cout << strNum << endl;
	}

	return 0;
}