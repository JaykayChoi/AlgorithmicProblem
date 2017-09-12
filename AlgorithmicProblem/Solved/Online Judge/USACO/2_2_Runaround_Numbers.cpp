/*
ID: jkchoik1
PROG: runround
LANG: C++11
*/

//http://jaykaychoi.tistory.com/77

#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
typedef long long ll;

int touchInfo;
int digit;

bool isAllTouched()
{
	return touchInfo == (1 << digit) - 1;
}

bool touch(int index)
{
	if (touchInfo & (1 << index))
		return false;
	touchInfo |= (1 << index);
	return true;
}

int getIndex(int resource, int order)
{
	string str = to_string(resource);
	int numLetter = str.size();
	if (order > numLetter)
		order %= numLetter;
	if (order == 0)
		order = numLetter;
	return order;
}

void setDigit(int number)
{
	string str = to_string(number);
	digit = str.size();
}

int getRunaroundNumber(int start)
{
	for (int i = start; ; i++)
	{
		setDigit(i);
		string str = to_string(i);

		bool ok = true;
		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] == '0')
			{
				ok = false;
				break;
			}
			for (int j = i + 1; j < str.size(); j++)
			{
				if (str[i] == str[j])
				{
					ok = false;
					break;
				}
			}
			if (ok == false)
				break;
		}
		if (ok == false)
			continue;

		int index = 1;
		touchInfo = 0;
		while (true)
		{
			int idx = str[index - 1] - '0';
			idx = getIndex(i, idx + index);
			if (touch(idx - 1) == false)
				break;
			if (isAllTouched())
				return i;
			index = idx;
		}
	}
	return -1;
}



int main()
{
	ifstream fin("runround.in");
	ofstream fout("runround.out");

	int minNum;
	fin >> minNum;
	minNum++;

	fout << getRunaroundNumber(minNum) << endl;

	fin.close();
	fout.close();
	return 0;
}