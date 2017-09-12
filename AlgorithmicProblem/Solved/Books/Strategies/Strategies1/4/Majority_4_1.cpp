#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//주어진 배열 A에서 가장 많이 등장하는 숫자를 반환

class Majority_4_1
{
public:
	void Solve()
	{

	}

private:
#pragma region answer
	//주어진 배열 A에서 가장 많이 등장하는 숫자를 반환. 둘 이상일 경우 아무 것이나 반환.
	int majority1(const vector<int>& A)
	{
		int N = A.size();
		int majority = -1, majorityCount = 0;
		for (int i = 0; i < N; i++)
		{
			//A에 등장하는 A{i]의 숫자를 센다.
			int V = A[i], count = 0;
			for (int j = 0; j < N; j++)
			{
				if (A[j] == V)
					count++;
			}

			//지금까지 본 최대 빈도보다 많이 출현했다면 답을 갱신.
			if (count > majorityCount)
			{
				majorityCount = count;
				majority = V;
			}
		}
		return majority;
	}

	//A의 각 원소가 0부터 100 사이의 값일 경우 가장 많이 등장하는 숫자를 반환.
	int majority2(const vector<int>& A)
	{
		int N = A.size();
		vector<int> count(101,0);	// 101 ints with value 0
		for (int i = 0; i < N; i++)
		{
			count[A[i]]++;
		}

		int majority = 0;
		for (int i = 1; i <= 100; i++)
		{
			if (count[i] > count[majority])
				majority = i;
		}
		return majority;
	}
#pragma endregion


};