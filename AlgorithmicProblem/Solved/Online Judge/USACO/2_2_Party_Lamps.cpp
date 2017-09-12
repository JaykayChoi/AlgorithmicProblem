/*
ID: jkchoik1
PROG: lamps
LANG: C++11
*/
//http://jaykaychoi.tistory.com/78
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
using namespace std;
typedef long long ll;

ofstream fout("lamps.out");
int n;
vector<bool> lamps;
vector<int> on;
vector<int> off;
set<string> ret;

bool whetherMeet()
{
	for (vector<int>::iterator it = on.begin(); it != on.end(); it++)
	{
		if (lamps[*it] == false)
			return false;
	}
	for (vector<int>::iterator it = off.begin(); it != off.end(); it++)
	{
		if (lamps[*it])
			return false;
	}

	return true;
}

void changeState(int type)
{
	switch (type)
	{
	case 1:
		for (vector<bool>::iterator it = lamps.begin(); it != lamps.end(); it++)
			*it = !*it;
		break;
	case 2:
		for (int i = 0; i < n; i += 2)
			lamps[i] = !lamps[i];
		break;
	case 3:
		for (int i = 1; i < n; i += 2)
			lamps[i] = !lamps[i];
		break;
	case 4:
		for (int i = 0; i < n; i += 3)
			lamps[i] = !lamps[i];
		break;
	default:
		break;
	}
}

//It used more than the allotted runtime of 1 seconds when c is over 100
void bruteForce(int remainingNumber)
{
	if (remainingNumber == 0)
	{
		if (whetherMeet())
		{
			string str = "";
			for (int i = 0; i < n; i++)
				str += to_string((int)lamps[i]);
			ret.insert(str);
		}
		return;
	}

	for (int i = 1; i < 5; i++)
	{
		changeState(i);
		bruteForce(remainingNumber - 1);
		changeState(i);
	}
}

void greedy(int c)
{
	for (int i = 0; i < 1 << 4; i++)
	{
		int type[4] = { i & 1, i >> 1 & 1, i >> 2 & 1, i >> 3 & 1 };
		int bitCount = 0;
		for (int i = 0; i < 4; i++)
			bitCount += type[i];

		if (bitCount > c)
			continue;

		if (bitCount % 2 != c & 2)
			continue;

		fill(lamps.begin(), lamps.end(), 1);

		for (int i = 0; i < 4; i++)
		{
			if (type[i] == 1)
				changeState(i + 1);
		}

		if (whetherMeet())
		{
			string str = "";
			for (int i = 0; i < n; i++)
				str += to_string((int)lamps[i]);
			ret.insert(str);
		}
	}
}

int main()
{
	ifstream fin("lamps.in");

	int c;
	fin >> n >> c;

	int lamp;
	while (fin >> lamp)
	{
		if (lamp == -1)
			break;
		on.push_back(lamp - 1);
	}
	while (fin >> lamp)
	{
		if (lamp == -1)
			break;
		off.push_back(lamp - 1);
	}

	vector<bool> temp(n, 1);
	lamps = temp;

	greedy(c);


	if (ret.empty())
	{
		fout << "IMPOSSIBLE" << endl;
	}
	else
	{
		for (set<string>::iterator it = ret.begin(); it != ret.end(); it++)
			fout << *it << endl;
	}

	fin.close();
	fout.close();
	return 0;
}