#include<iostream>
#include <queue>

using namespace std;

//https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=87

class PowerCrisis_151
{
public:
	int last = 13;

	int CalcByQueue(int N)
	{
		for (int m = 1; m <= N; m++)
		{
			queue<int> survivors;
			for (int j = 1; j <= N; j++)
				survivors.push(j);

			while (survivors.size() > 1)
			{
				survivors.pop();

				for (int i = 0; i < m - 1; i++) {
					survivors.push(survivors.front());
					survivors.pop();
				}
			}

			if (survivors.front() == last)
			{
				return m;
			}
		}
		return 0;
	}
	int sub_main()
	{
		int N;
		
		while (true)
		{
			cin >> N;
			if (N == 0)
				break;

			cout << CalcByQueue(N) << endl;
		}


		return 0;
	}
private:
	
};
