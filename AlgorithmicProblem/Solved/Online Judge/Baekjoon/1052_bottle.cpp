#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <vector>
using namespace std;

vector<int> convertBase10ToBase2(int num, int& bitCount)
{
	vector<int> ret(100, 0);
	int temp;
	bitCount = 0;
	int i = 0;
	do
	{
		temp = num % 2;
		if (temp == 1)
			bitCount++;
		ret[i] = temp;
		num /= 2;
		i++;
	} while (num > 0);
	return ret;
}

int main()
{
	int n, k;
	cin >> n >> k;
	int bitCount = 0;
	vector<int> base2 = convertBase10ToBase2(n, bitCount);

	int ret = 0;
	int i = 0;
	while (bitCount > k)
	{
		if (base2[i] == 1)
		{
			ret += pow(2, i);
			base2[i] = 0;
			bitCount--;
			for (int j = i + 1; ; j++)
			{
				if (base2[j] == 1)
				{
					base2[j] = 0;
					bitCount--;
				}
				else
				{
					base2[j] = 1;
					bitCount++;
					break;
				}
			}
		}
		i++;
	}

	cout << ret << endl;
	return 0;
}

