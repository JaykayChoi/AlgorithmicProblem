#include <iostream>
#include <vector>

using namespace std;

//https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=4&page=show_problem&problem=235

class TrainSwapping_299
{
public:
	int insertionSort(vector<int>& numbers)
	{
		int ret = 0;
		for (int i = 0; i < numbers.size(); i++)
		{
			int val = numbers[i], j = i - 1;
			while (j >= 0 && numbers[j] > val)
			{
				numbers[j + 1] = numbers[j];
				--j;
				ret++;
			}
			numbers[j + 1] = val;
		}
		return ret;
	}

	int sub_main()
	{
		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; cc++)
		{
			int L;
			cin >> L;
			vector<int> trains;
			for (int i = 0; i < L; i++)
			{
				int num;
				cin >> num;
				trains.push_back(num);
			}
			cout << "Optimal train swapping takes " << insertionSort(trains) <<" swaps." << endl;
		}
		return 0;
	}
private:

};