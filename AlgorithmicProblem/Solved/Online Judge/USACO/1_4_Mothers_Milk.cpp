/*
ID: jkchoik1
PROG: milk3
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

//http://jaykaychoi.tistory.com/56

int capacity[3];
int cache[21][21][21];

void pourMilk(int milks[3], int from, int to)
{
	int pauredMilk = milks[from];
	if (pauredMilk > (capacity[to] - milks[to]))
		pauredMilk = capacity[to] - milks[to];
	milks[from] -= pauredMilk;
	milks[to] += pauredMilk;
}

void solve(int milks[3])
{
	if (cache[milks[0]][milks[1]][milks[2]] == 0)
	{
		cache[milks[0]][milks[1]][milks[2]] = 1;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (j == i)
					continue;
				int temp[3] = { milks[0], milks[1], milks[2] };
				pourMilk(temp, i, j);
				solve(temp);
			}
		}
	}
}
int main()
{
	ifstream fin("milk3.in");
	ofstream fout("milk3.out");

	fin >> capacity[0] >> capacity[1] >> capacity[2];

	int temp[3] = { 0, 0, capacity[2] };
	solve(temp);

	bool isFirst = true;
	for (int c = 0; c <= capacity[2]; c++)
	{
		for (int b = 0; b <= capacity[1]; b++)
		{
			if (cache[0][b][c] == 1)
			{
				if (isFirst == false)
					fout << " ";
				fout << c;
				isFirst = false;
				break;
			}
		}
	}
	fout << endl;

	fin.close();
	fout.close();
	return 0;
}