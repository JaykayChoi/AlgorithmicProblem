/*
ID: jkchoik1
PROG: ariprog
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cstring>
using namespace std;

//http://jaykaychoi.tistory.com/53

int n, m;
bool bisquares[250 * 250 * 2 + 1];

void setBisquares()
{
	for (int p = 0; p <= m; p++)
	{
		for (int q = 0; q <= m; q++)
			bisquares[p * p + q * q] = true;
	}
}

multimap<int, int> solve()
{
	multimap<int, int> ret;
	for (int a = 0; ; a++)
	{
		if (a + (n - 1) > 2 * pow(m, 2))
			break;

		for (int b = 1; ; b++)
		{
			if (a + (n - 1) * b  > 2 * pow(m, 2))
				break;

			bool ok = true;
			for (int seq = 0; seq < n; seq++)
			{
				int num = a + seq * b;
				if (bisquares[num] == false)
				{
					ok = false;
					break;
				}
			}
			if (ok)
				ret.insert(make_pair(b, a));
		}
	}
	return ret;
}

int main()
{
	ifstream fin("ariprog.in");
	ofstream fout("ariprog.out");

	fin >> n >> m;

	setBisquares();
	multimap<int, int> ret = solve();

	if (ret.empty())
		fout << "NONE" << endl;
	else
	{
		for (multimap<int, int>::iterator it = ret.begin(); it != ret.end(); it++)
			fout << it->second << " " << it->first << endl;
	}

	fin.close();
	fout.close();
	return 0;
}
