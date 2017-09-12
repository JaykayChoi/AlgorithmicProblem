#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <string>

//https://www.acmicpc.net/problem/1032

using namespace std;
const int MAX_N = 50;

int main()
{
	string characters[MAX_N][MAX_N];

	int n;
	int strLength = 0;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		string str;
		cin >> str;
		strLength = str.length();
		for (int j = 0; j < strLength; j++)
			characters[i][j] = str[j];
	}

	string ret = "";

	for (int x = 0; x < strLength; x++)
	{
		string c = characters[0][x];
		bool isSame = true;
		for (int y = 1; y < n; y++)
		{
			if (c != characters[y][x])
			{
				isSame = false;
				ret += "?";
				break;
			}
		}
		if (isSame)
			ret += c;
	}

	cout << ret << endl;

	return 0;
}