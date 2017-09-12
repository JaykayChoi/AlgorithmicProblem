/*
ID: jkchoik1
PROG: combo
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

//http://jaykaychoi.tistory.com/admin/entry/post/?id=41

int n;
set<string> dialSettings;

int getPosition(int pos)
{
	while (pos < 0)
		pos += n;

	if (pos > n)
		pos %= n;

	if (pos == 0)
		pos = n;

	return pos;
}
//배열을 포인터 형식의 파라미터로 
void setDial(int *combination)
{
	for (int i = -2; i < 3; i++)
	{
		for (int j = -2; j < 3; j++)
		{
			for (int k = -2; k < 3; k++)
			{
				string str = to_string(getPosition(combination[0] + i)) + to_string(getPosition(combination[1] + j)) + to_string(getPosition(combination[2] + k));
				dialSettings.insert(str);
			}
		}
	}
}
int submain()
{
	ofstream fout("combo.out");
	ifstream fin("combo.in");

	fin >> n;

	int farmarCombination[3];
	int masterCombination[3];

	for (int i = 0; i < 3; i++)
	{
		int num;
		fin >> num;
		farmarCombination[i] = num;
	}
	for (int i = 0; i < 3; i++)
	{
		int num;
		fin >> num;
		masterCombination[i] = num;
	}

	setDial(farmarCombination);
	setDial(masterCombination);

	fout << dialSettings.size() << endl;

	return 0;
}