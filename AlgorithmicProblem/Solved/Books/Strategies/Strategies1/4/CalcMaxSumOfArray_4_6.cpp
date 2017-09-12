#include <limits>       // std::numeric_limits
#include <vector>
#include <algorithm> 
#include <ctime>
#include <iostream>

using namespace std;

//문제
//
//N개의 정수를 담고 있는 배열 A가 주어졌을 때, 여기서 가능한 연속 부분합을 구하는 프로그램을 작성하라.
//
//여기서 연속 합이라는 것은 배열 A = { a1, a2, ..., aN } 에서 아무 값도 선택을 하지 않거나(이 경우 합은 0), 배열의 임의의 i번째 수 부터 j번째 수 까지(ai, ai + 1, ..., aj) (1 <= i <= j <= N)를 합한 값을 뜻한다.
//
//입력
//
//입력의 첫번째 줄에는 테스트 케이스의 개수 T가 입력된다.
//그리고 그 다음줄 부터 한줄에 하나씩 T개의 테스트 케이스가 입력된다.
//테스트 케이스의 첫번째 줄에는 정수 N(1 <= N <= 105)가 입력된다.
//그리고 그 다음줄에는 N개의 배열에 담긴 숫자가 순서대로 입력된다.숫자의 범위는 - 100이상 100이하의 정수다.
//
//출력
//
//한줄에 하나씩 테스트 케이스의 순서대로 각 테스트케이스에 대한 가장 큰 연속 부분합을 출력한다.
//
//예제 입력
//
//2
//4
//1 2 3 4
//3
//- 1 0 1
//
//예제 출력
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

	//A[lo..hi]의 연속된 부분 구간의 최대 합을 구한다. O(nlgn)
	int fastMaxSum(const vector<int>& A, int lo, int hi)
	{
		//구간의 길이가 1일 경우.
		if (lo == hi)
			return A[lo];

		//배열을 A[lo..mid], A[mid+1..hi]의 두 조각으로 나눈다.
		int mid = (lo + hi) / 2;

		//두 부분에 모두 걸쳐있는 최대 합 구간을 찾는다 이 구간은 A[i..mid]와 A[mid+1..j] 형태를 갖는 구간의 합으로 이루어진다.
		//A[i..mid]형태를 갖는 최대 구간을 찾는다.
		int left = MIN, right = MIN, sum = 0;
		for (int i = mid; i >= lo; i--)
		{
			sum += A[i];
			left = max(left, sum);
		}
		
		//A[mid+1..j] 형태를 갖는 최대 구간을 찾는다.
		sum = 0;
		for (int j = mid + 1; j <= hi; j++)
		{
			sum += A[j];
			right = max(right, sum);
		}

		//최대 구간이 두 조각 중 하나에만 속해 있는 경우의 답을 재귀 호출로 찾는다.
		int single = max(fastMaxSum(A, lo, mid), fastMaxSum(A, mid+1, hi));

		//두 경우 중 최대치를 반환한다.
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
