#include<cassert>
#include<vector>
#include<iostream>
#include<cstring>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <string>
#include "Utils.h"
#include <ctime>
using namespace std;


//����
//
//� �������� 0�� �̻��� ���ڸ� ���� ����� �� ������ �κ� �����̶�� �θ��ϴ�.���� ��� '4 7 6'�� '4 3 7 6 9'�� �κ� �����Դϴ�.�ߺ��� ���ڰ� ���� ���� �������� ���ĵǾ� �ִ� �κ� �������� ������ ���� �κ� �����̶�� �θ�����.���� ��� '3 6 9'�� ���� ������ ���� �κ� �����Դϴ�.
//
//�� ���� ���� ���� A �� B ���� ���� ���� �κ� ������ ���� �� �̵��� ũ�� ������� ��ģ ���� ��ģ ���� �κ� �����̶�� �θ���� �սô�.�� �� ���� �� ������ ��ģ LIS(JLIS, Joined Longest Increasing Subsequence)�̶�� �θ��ô�.���� ��� '1 3 4 7 9' �� '1 9 4' �� '3 4 7' �� JLIS�Դϴ�. '1 9' �� '3 4 7' �� ���� '1 3 4 7 9'�� ���� �� �ֱ� ����������.
//
//A �� B �� �־��� ��, JLIS�� ���̸� ����ϴ� ���α׷��� �ۼ��ϼ���.
//
//�Է�
//
//�Է��� ù �ٿ��� �׽�Ʈ ���̽��� �� c(1 <= c <= 50) �� �־����ϴ�.�� �׽�Ʈ ���̽��� ù �ٿ��� A �� B �� ���� n �� m �� �־����ϴ�(1 <= n, m <= 100).���� �ٿ��� n ���� ������ A �� ���ҵ���, �� ���� �ٿ��� m ���� ������ B �� ���ҵ��� �־����ϴ�.��� ���ҵ��� 32��Ʈ ��ȣ �ִ� ������ ������ �� �ֽ��ϴ�.
//
//���
//
//�� �׽�Ʈ ���̽����� �� �ٿ�, JLIS �� ���̸� ����մϴ�.
//
//���� �Է�
//
//3
//3 3
//1 2 4
//3 4 7
//3 3
//1 2 3
//4 5 6
//5 3
//10 20 30 1 2
//10 20 30
//���� ���
//
//5
//6
//5

class JLIS_8_5
{
public:
	void Solve()
	{
		Input();
	}
private:
	//int n;
	vector<int> numbers;
	void Input()
	{
		memset(lisCache, -1, sizeof(lisCache));
		memset(lengthOfEachStart, 1, sizeof(lengthOfEachStart));
		string filePath = "JLIS_8_5_Input.txt";
		vector<string> vInputLines = Utils::GetLine_InputFile(filePath);

		int numProblems = stoi(vInputLines[0]);

		for (int i = 0; i < numProblems; i++)
		{
			string delimiter = " ";
			vector<int> nm = Utils::SplitStringToInt(vInputLines[i * 3 + 1], delimiter);
			n = nm[0];
			numbers = Utils::SplitStringToInt(vInputLines[i * 3 + 2], delimiter);

			int lisResult = LIS(0);

			vector<int> result = GetLISNumbers(lisResult);

			for each (int var in result)
			{
				cout << var << " ";
			}

			cout << endl;
		}
	}

	int lisCache[100];
	int lengthOfEachStart[100];
	int LIS(int start)
	{
		int& ret = lisCache[start];

		if (ret != -1)
			return ret;

		ret = 1;

		for (int next = start + 1; next < n; next++)
		{
			if (numbers[start] < numbers[next])
				ret = max(ret, 1 + LIS(next));
		}

		if (lengthOfEachStart[start] < ret)
			lengthOfEachStart[start] = ret;

		return ret;
	}

	vector<int> GetLISNumbers(int lisResult)
	{
		int max = 0;
		int selectedStart = 0;
		for (int i = 0; i < n; i++)
		{
			if (lengthOfEachStart[i] > max)
			{
				max = lengthOfEachStart[i];
				selectedStart = i;
			}
		}

		vector<int> ret;

		for (int i = selectedStart; i < selectedStart + lisResult; i++)
		{
			ret.push_back(numbers[i]);
		}

		return ret;
	}




	////
	// �Է��� 32��Ʈ ��ȣ �ִ� ������ ��� ���� ���� �� �����Ƿ� �������� �ּҰ��� 64��Ʈ���� �Ѵ�
	const long long NEGINF = numeric_limits<long long>::min();

	int n, m, A[100], B[100];
	int cache[101][101];

	// min(A[indexA], B[indexB]), max(A[indexA], B[indexB]) �� �����ϴ�
	// ��ģ ���� �κ� ������ �ִ� ���̸� ��ȯ�Ѵ�
	// �� A[indexA] != B[indexB] ��� �����Ѵ�.
	int jlis(int indexA, int indexB) {
		// �޸������̼�
		int& ret = cache[indexA + 1][indexB + 1];
		if (ret != -1) return ret;
		// A[indexA], B[indexB] �� �̹� �����ϹǷ� 2���� �׻� �ִ�.
		ret = 2;
		long long a = (indexA == -1 ? NEGINF : A[indexA]);
		long long b = (indexB == -1 ? NEGINF : B[indexB]);
		long long maxElement = max(a, b);
		// ���� ���Ҹ� ã�´�
		for (int nextA = indexA + 1; nextA < n; ++nextA)
			if (maxElement < A[nextA])
				ret = max(ret, jlis(nextA, indexB) + 1);
		for (int nextB = indexB + 1; nextB < m; ++nextB)
			if (maxElement < B[nextB])
				ret = max(ret, jlis(indexA, nextB) + 1);
		return ret;
	}
};