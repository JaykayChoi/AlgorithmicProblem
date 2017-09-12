#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class LinearTimeAlgorithm_Calc_MovingAverage_4_2
{
public:
	void Solve()
	{
		vector<double> v;
		v.push_back(10);
		v.push_back(11);
		v.push_back(12);
		v.push_back(13);
		v.push_back(14);
		v.push_back(15);

		vector<double> answer;

		answer = movingAverage2(v, 3);

		for_each(answer.begin(), answer.end(), [](double d)
		{
			cout << d << endl;
		});
	}

private:
#pragma region answer
	vector<double> movingAverage1(const vector<double>& A, int M)
	{
		vector<double> ret;
		int N = A.size();
		for (int i = M - 1; i < N; ++i)
		{
			double partialSum = 0;
			for (int j = 0; j < M; ++j)
			{
				partialSum += A[i - j];
			}
			ret.push_back(partialSum / M);
		}
		return ret;
	}

	vector<double> movingAverage2(const vector<double>& A, int M)
	{
		vector<double> ret;
		int N = A.size();
		double partialSum = 0;
		for (int i = 0; i < M - 1; ++i)
			partialSum += A[i];

		for (int i = M - 1; i < N; ++i)
		{
			partialSum += A[i];
			ret.push_back(partialSum / M);
			partialSum -= A[i - M + 1];
		}
		return ret;
	}
#pragma endregion
};