#include <limits>       // std::numeric_limits
#include <vector>
#include <algorithm> 
#include <ctime>
#include <iostream>

using namespace std;

//����
//
//N���� ������ ��� �ִ� �迭 A�� �־����� ��, ���⼭ ������ ���� �κ����� ���ϴ� ���α׷��� �ۼ��϶�.
//
//���⼭ ���� ���̶�� ���� �迭 A = { a1, a2, ..., aN } ���� �ƹ� ���� ������ ���� �ʰų�(�� ��� ���� 0), �迭�� ������ i��° �� ���� j��° �� ����(ai, ai + 1, ..., aj) (1 <= i <= j <= N)�� ���� ���� ���Ѵ�.
//
//�Է�
//
//�Է��� ù��° �ٿ��� �׽�Ʈ ���̽��� ���� T�� �Էµȴ�.
//�׸��� �� ������ ���� ���ٿ� �ϳ��� T���� �׽�Ʈ ���̽��� �Էµȴ�.
//�׽�Ʈ ���̽��� ù��° �ٿ��� ���� N(1 <= N <= 105)�� �Էµȴ�.
//�׸��� �� �����ٿ��� N���� �迭�� ��� ���ڰ� ������� �Էµȴ�.������ ������ - 100�̻� 100������ ������.
//
//���
//
//���ٿ� �ϳ��� �׽�Ʈ ���̽��� ������� �� �׽�Ʈ���̽��� ���� ���� ū ���� �κ����� ����Ѵ�.
//
//���� �Է�
//
//2
//4
//1 2 3 4
//3
//- 1 0 1
//
//���� ���
//
//10
//1

//https://en.wikipedia.org/wiki/Maximum_subarray_problem

class CalcMaxSumOfArray_4_6
{
public:
	void Solve()
	{
		vector<int> v;
		v.push_back(-7);
		v.push_back(4);
		v.push_back(-3);
		v.push_back(6);
		v.push_back(3);
		v.push_back(-8);
		v.push_back(3);
		v.push_back(4);

		clock_t start = clock();

		int answer = inefficientMaxSum(v);
		
		clock_t end = clock();
		double time = double(end - start) / CLOCKS_PER_SEC;

		cout << "Time (s): " << time << endl;
		cout << "Answer1 : " << answer << endl;

		answer = betterMaxSum(v);

		cout << "Answer2 : " << answer << endl;

		answer = fastMaxSum(v, 0, 7);
		cout << "Answer3 : " << answer << endl;

		answer = fastestMaxSum(v);
		cout << "Answer4 : " << answer << endl;

	}
private:
	const int MIN = numeric_limits<int>::min();

	//O(N^3)
	int inefficientMaxSum(const vector<int>& A)
	{
		int N = A.size(), ret = MIN;
		for (int i = 0; i < N; i++)
		{
			for (int j = i; j < N; j++)
			{
				int sum = 0;
				for (int k = i; k <= j; k++)
					sum += A[k];
				ret = max(ret, sum);
			}
		}
		return ret;
		
	}

	//O(N^2)
	int betterMaxSum(const vector<int>& A)
	{
		int N = A.size(), ret = MIN;

		for (int i = 0; i < N; i++)
		{
			int sum = 0;
			for (int j = i; j < N; j++)
			{
				sum += A[j];
				ret = max(ret, sum);
			}
		}
		return ret;
	}

	//A[lo..hi]�� ���ӵ� �κ� ������ �ִ� ���� ���Ѵ�. O(nlgn)
	int fastMaxSum(const vector<int>& A, int lo, int hi)
	{
		//������ ���̰� 1�� ���.
		if (lo == hi)
			return A[lo];

		//�迭�� A[lo..mid], A[mid+1..hi]�� �� �������� ������.
		int mid = (lo + hi) / 2;

		//�� �κп� ��� �����ִ� �ִ� �� ������ ã�´� �� ������ A[i..mid]�� A[mid+1..j] ���¸� ���� ������ ������ �̷������.
		//A[i..mid]���¸� ���� �ִ� ������ ã�´�.
		int left = MIN, right = MIN, sum = 0;
		for (int i = mid; i >= lo; i--)
		{
			sum += A[i];
			left = max(left, sum);
		}
		
		//A[mid+1..j] ���¸� ���� �ִ� ������ ã�´�.
		sum = 0;
		for (int j = mid + 1; j <= hi; j++)
		{
			sum += A[j];
			right = max(right, sum);
		}

		//�ִ� ������ �� ���� �� �ϳ����� ���� �ִ� ����� ���� ��� ȣ��� ã�´�.
		int single = max(fastMaxSum(A, lo, mid), fastMaxSum(A, mid+1, hi));

		//�� ��� �� �ִ�ġ�� ��ȯ�Ѵ�.
		return max(left + right, single);
	}

	//O(n)
	int fastestMaxSum(const vector<int>& A)
	{
		int N = A.size(), ret = MIN, psum = 0;
		for (int i = 0; i < N; i++)
		{
			//maxAt(i) = max(0, maxAt(i-1)) + A[i]
			psum = max(psum, 0) + A[i];
			ret = max(psum, ret);
		}
		return ret;

	}
};
