#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//�־��� �迭 A���� ���� ���� �����ϴ� ���ڸ� ��ȯ

class Majority_4_1
{
public:
	void Solve()
	{

	}

private:
#pragma region answer
	//�־��� �迭 A���� ���� ���� �����ϴ� ���ڸ� ��ȯ. �� �̻��� ��� �ƹ� ���̳� ��ȯ.
	int majority1(const vector<int>& A)
	{
		int N = A.size();
		int majority = -1, majorityCount = 0;
		for (int i = 0; i < N; i++)
		{
			//A�� �����ϴ� A{i]�� ���ڸ� ����.
			int V = A[i], count = 0;
			for (int j = 0; j < N; j++)
			{
				if (A[j] == V)
					count++;
			}

			//���ݱ��� �� �ִ� �󵵺��� ���� �����ߴٸ� ���� ����.
			if (count > majorityCount)
			{
				majorityCount = count;
				majority = V;
			}
		}
		return majority;
	}

	//A�� �� ���Ұ� 0���� 100 ������ ���� ��� ���� ���� �����ϴ� ���ڸ� ��ȯ.
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