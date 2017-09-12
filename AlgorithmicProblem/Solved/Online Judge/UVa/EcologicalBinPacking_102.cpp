#include <iostream>
#include <queue>
#include <string>
#include <cstring>
using namespace std;

//https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=38

class EcologicalBinPacking_102
{
public:
	int bin[3][3] = { 0, };
	int minValue = 2147483647;
	string minValueBinOrder = "BGC";

	void solveNaive(int* seq)
	{
		string curStr = "";
		for (int i = 0; i < 3; i++)
		{
			switch (seq[i])
			{
			case 0:
				curStr += "B";
				break;
			case 1:
				curStr += "G";
				break;
			case 2:
				curStr += "C";
				break;
			}
		}

		int sum = 0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (seq[i] == j)
				{
					continue;
				}
				sum += *(*(bin + i) + j);

				if (sum >= minValue)
					return;
			}
		}

		if (minValue > sum)
		{
			minValue = sum;
			minValueBinOrder = curStr;
		}

	}

	void makeSequence(int* arr, int n, int size)
	{
		if (n == size - 1)
		{
			int seq[3];
			for (int i = 0; i < size; i++)
				seq[i] = *(arr + i);
			solveNaive(seq);
			return;
		}

		for (int i = n; i < size; i++)
		{
			int temp = arr[n];
			arr[n] = arr[i];
			arr[i] = temp;

			makeSequence(arr, n + 1, size);
		}

		int temp = arr[n];
		for (int i = n; i < size - 1; i++)
			arr[i] = arr[i + 1];
		arr[size - 1] = temp;
	}

	int sub_main()
	{
		int a[9] = { 0, };
		while (cin >> a[0] >> a[1] >> a[2] >> a[3] >> a[4] >> a[5] >> a[6] >> a[7] >> a[8])
		{
			memset(bin, 0, sizeof(bin));
			minValue = 2147483647;
			minValueBinOrder = "BGC";

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					bin[i][j] = a[i * 3 + j];
				}
			}
			int a[3] = { 0,2,1 };
			makeSequence(a, 0, 3);

			cout << minValueBinOrder << " " << minValue << endl;
		}
		return 0;
	}
};
