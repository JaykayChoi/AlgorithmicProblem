#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <string>
using namespace std;

string arrStr[8] = { "TTT", "TTH", "THT", "THH", "HTT", "HTH", "HHT", "HHH" };


int main()
{
	int cases;
	cin >> cases;
	for (int i = 0; i < cases; i++)
	{
		int ret[8] = { 0, };
		string str;
		cin >> str;
		for (int s = 0; s < 38; s++)
		{
			string sub = str.substr(s, 3);
			for (int j = 0; j < 8; j++)
			{
				if (sub == arrStr[j])
				{
					ret[j]++;
					break;
				}
			}
		}
		for (int k = 0; k < 8; k++)
		{
			cout << ret[k];
			if (k != 7)
				cout << " ";
		}
		cout << endl;
	}
	return 0;
}



