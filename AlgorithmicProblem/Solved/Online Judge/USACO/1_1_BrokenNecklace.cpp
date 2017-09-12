/*
ID: jkchoik1
PROG: beads
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

//http://train.usaco.org/usacoprob2?a=lKDHbQbnm8c&S=beads

class BrokenNecklace
{
public:
	int N;
	string beads;

	char getBead(int pos)
	{
		while (pos < 0)
			pos += N;
		pos %= N;

		return beads[pos];
	}

	int solve(int pos, int dir)
	{
		int ret;
		int position;
		char preBead = 'w';

		if (dir == 1)
			position = pos;
		else
			position = pos - 1;

		for (ret = 0; ret < N; ret++)
		{
			if (preBead == 'w' && getBead(position) != 'w')
				preBead = getBead(position);

			if (preBead != 'w' && getBead(position) != 'w' && getBead(position) != preBead)
				break;
			position += dir;
		}
		return ret;
	}


	int sub_main()
	{
		ofstream fout("beads.out");
		ifstream fin("beads.in");

		fin >> N;
		fin >> beads;

		int ret = 0;

		for (int i = 0; i < N; i++)
			ret = max(solve(i, -1) + solve(i, 1), ret);

		if (ret > N)
			ret = N;

		fout << ret << endl;

		return 0;
	}
};
