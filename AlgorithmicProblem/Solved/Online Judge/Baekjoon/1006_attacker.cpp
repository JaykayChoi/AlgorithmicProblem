#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cstring>
using namespace std;

//https://www.acmicpc.net/problem/1006

int numArea, numTroopsPerUnit;
int enemies[10001][2];
int cache[10001][2];


#pragma region brute force / It used more than the allotted runtime
vector<int> enemies_ForBruteForce;

//direction: 1 left, 2 right, 3 opposite side
int getImmediateArea(int curPos, int direction)
{
	switch (direction)
	{
	case 1:
		if (curPos == 0)
			return numArea - 1;
		else if (curPos == numArea)
			return numArea * 2 - 1;
		else
			return curPos - 1;
	case 2:
		if (curPos == numArea - 1)
			return 0;
		else if (curPos == numArea * 2 - 1)
			return numArea;
		else
			return curPos + 1;
	case 3:
		if (curPos < numArea)
			return curPos + numArea;
		else
			return curPos - numArea;
	default:
		break;
	}
	return -1;
}

int bruteForce(set<int>& put)
{
	if (put.size() == numArea * 2)
		return 0;

	int ret = 0;
	for (int i = 0; i < numArea * 2; i++)
	{
		set<int>::iterator it = put.find(i);
		if (it != put.end())
			continue;

		for (int direction = 0; direction <= 3; direction++)
		{
			if (direction == 0)
			{
				put.insert(i);
				bruteForce(put);
				put.erase(i);
			}
			else
			{
				int immediateArea = getImmediateArea(i, direction);
				it = put.find(immediateArea);
				if (it != put.end())
					continue;

				if (enemies_ForBruteForce[i] + enemies_ForBruteForce[immediateArea] <= numTroopsPerUnit)
				{
					put.insert(i);
					put.insert(immediateArea);
					int candidate = bruteForce(put) + 1;
					ret = max(ret, candidate);
					put.erase(i);
					put.erase(immediateArea);
				}
			}
		}
	}
	return ret;
}
#pragma endregion


bool canAttackTwoAreas(int column1, int row1, int column2, int row2)
{
	if (column1 >= numArea || column2 >= numArea)
		return false;
	return enemies[column1][row1] + enemies[column2][row2] <= numTroopsPerUnit;
}

int dp(int column, int row)
{
	if (column >= numArea)
		return 0;

	int& ret = cache[column][row];
	if (ret != -1)
		return ret;

	ret = -1;

	if (column == numArea - 1)
	{
		if (row == 0 && canAttackTwoAreas(numArea - 1, 0, numArea - 1, 1))
			return 1;

		return 0;
	}

	if (row == 0)
	{
		if (canAttackTwoAreas(column, 0, column, 1))
			ret = max(ret, dp(column + 1, 0) + 1);

		if (canAttackTwoAreas(column, 0, column + 1, 0))
		{
			if (canAttackTwoAreas(column, 1, column + 1, 1))
				ret = max(ret, dp(column + 2, 0) + 2);
			ret = max(ret, dp(column + 1, 1) + 1);
		}

		ret = max(ret, dp(column, 1));
	}
	else
	{
		if (canAttackTwoAreas(column, 1, column + 1, 1))
		{
			if (canAttackTwoAreas(column + 1, 0, column + 2, 0))
				ret = max(ret, dp(column + 2, 1) + 2);

			ret = max(ret, dp(column + 2, 0) + 1);
		}

		ret = max(ret, dp(column + 1, 0));
	}

	return ret;
}


int main()
{
	int cases;
	cin >> cases;

	for (int i = 0; i < cases; i++)
	{
		cin >> numArea >> numTroopsPerUnit;

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < numArea; j++)
			{
				int num;
				cin >> num;
				enemies[j][i] = num;
			}
		}

		memset(cache, -1, sizeof(cache));

		int twoAreas = dp(0, 0);

		if (numArea > 1)
		{
			int temp[2][2];

			for (int i = 0; i < 2; i++)
			{
				temp[0][i] = enemies[numArea - 1][i];
				temp[1][i] = enemies[0][i];
			}

			if (canAttackTwoAreas(numArea - 1, 0, 0, 0) && canAttackTwoAreas(numArea - 1, 1, 0, 1))
			{
				enemies[numArea - 1][0] = numTroopsPerUnit + 1;
				enemies[numArea - 1][1] = numTroopsPerUnit + 1;

				memset(cache, -1, sizeof(cache));
				twoAreas = max(twoAreas, dp(1, 0) + 2);

				enemies[numArea - 1][0] = temp[0][0];
				enemies[numArea - 1][1] = temp[0][1];
			}

			if (canAttackTwoAreas(numArea - 1, 0, 0, 0))
			{
				enemies[numArea - 1][0] = numTroopsPerUnit + 1;

				memset(cache, -1, sizeof(cache));
				twoAreas = max(twoAreas, dp(0, 1) + 1);

				enemies[numArea - 1][0] = temp[0][0];
			}

			if (canAttackTwoAreas(numArea - 1, 1, 0, 1))
			{
				enemies[numArea - 1][1] = numTroopsPerUnit + 1;
				enemies[0][1] = numTroopsPerUnit + 1;

				memset(cache, -1, sizeof(cache));
				twoAreas = max(twoAreas, dp(0, 0) + 1);
			}
		}
		cout << numArea * 2 - twoAreas << endl;

	}

	return 0;
}
