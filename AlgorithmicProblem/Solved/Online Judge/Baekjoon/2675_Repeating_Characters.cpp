#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <string>
using namespace std;


int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int repeat;
		cin >> repeat;
		string str;
		cin >> str;
		for (int j = 0; j < str.length(); j++)
		{
			for (int k = 0; k < repeat; k++)
			{
				cout << str[j];
			}
		}
		cout << endl;
	}
	return 0;
}