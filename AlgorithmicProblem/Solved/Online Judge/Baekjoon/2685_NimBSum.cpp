#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <vector>
using namespace std;

vector<int> convertToBase(int b, int num)
{
	vector<int> ret;
	while (num != 0)
	{
		int remainder = num % b;
		ret.push_back(remainder);
		num /= b;
	}
	return ret;
}

int NimSum(int b, int x, int y)
{
	if (x > y)
		return NimSum(b, y, x);
	vector<int> baseX = convertToBase(b, x);
	vector<int> baseY = convertToBase(b, y);
	vector<int> baseSum;
	for (int i = 0; i < baseX.size(); i++)
		baseSum.push_back((baseX[i] + baseY[i]) % b);

	for (int i = 0; i < baseY.size() - baseX.size(); i++)
		baseSum.push_back(baseY[baseX.size() + i]);

	int ret = 0;
	for (int i = 0; i < baseSum.size(); i++)
	{
		ret += baseSum[i] * pow(b, i);
	}
	return ret;
}

int main()
{
	int cases, b, x, y;
	cin >> cases;
	for (int c = 0; c < cases; c++)
	{
		cin >> b >> x >> y;
		cout << NimSum(b, x, y) << endl;
	}
	return 0;
}