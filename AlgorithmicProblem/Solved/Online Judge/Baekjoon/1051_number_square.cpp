#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <string>
using namespace std;

int height, width;
int map[51][51];

int getMaxLength()
{
	int ret = 0;
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			int num = map[h][w];
			int maxLength = height - h - 1;
			if (width - w - 1 < maxLength)
				maxLength = width - w - 1;
			if (maxLength < ret)
				continue;
			for (int length = ret; length <= maxLength; length++)
			{
				if (map[h][w + length] == num && map[h + length][w + length] == num && map[h + length][w] == num)
					ret = length;
			}
		}
	}
	return ret;
}

int main()
{
	cin >> height >> width;

	for (int h = 0; h < height; h++)
	{
		string str;
		cin >> str;
		for (int w = 0; w < width; w++)
			map[h][w] = str[w] - '0';
	}
	int ret = getMaxLength() + 1;
	cout << ret * ret << endl;

	return 0;
}

