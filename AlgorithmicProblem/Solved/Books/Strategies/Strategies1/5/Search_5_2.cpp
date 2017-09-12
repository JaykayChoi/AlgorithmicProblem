#include <vector>
#include <algorithm> 
#include <iostream>

using namespace std;
class InductiveMethod_5_2
{
public:
	void Solve()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(3);
		v.push_back(5);
		v.push_back(10);
		v.push_back(11);
		v.push_back(12);
		v.push_back(100);

		int answer = binsearch(v, 9);

		cout << answer << endl;
	}
private:
	//�ʼ�����: A�� ������������ ���ĵǾ� �ִ�.
	//���: A[i-1] < x <= A[i] �� i �� ��ȯ�Ѵ�.
	//A[i-1] = ���� ���Ѵ�, A[n] = ���� ���Ѵ�� �����Ѵ�.
	int binsearch(const vector<int>& A, int x)
	{
		int n = A.size();
		int lo = -1, hi = n;
		//�ݺ��� �Һ��� 1: lo < hi
		//�ݺ��� �Һ��� 2: A[lo] < x <= A[Hi]
		while (lo + 1 < hi)
		{
			int mid = (lo + hi) / 2;
			if (A[mid] < x)
				lo = mid;
			else
				hi = mid;
		}
		return hi;
	}

	int sequentialSearch(const vector<int>& numbers, int target)
	{
		for (int i = 0; i < numbers.size(); i++)
		{
			if (target == numbers[i])
				return i;
			//else if (x < numbers[i])	//if array is sorted, it can use.
			//	return -1;
		}
		return -1;
	}
	int binarySearch(const vector<int>& numbers, int target)
	{
		int n = numbers.size();
		int low = 0;
		int high = n - 1;

		while (low <= high)
		{
			int mid = (low + high) / 2;
			if (numbers[mid] > target)
				high = mid - 1;
			else if (target > numbers[mid])
				low = mid + 1;
			else
				return mid;
		}

		return -1;
	}

	int binarySearchRecursive(int a[], int x, int low, int high)
	{
		if (low > high)
		{
			return -1;
		}
		int mid = (low + high) / 2;
		if (a[mid] < x)
		{
			return binarySearchRecursive(a, x, mid + 1, high);
		}
		else if (a[mid] > x)
		{
			return binarySearchRecursive(a, x, low, mid - 1);
		}
		else
		{
			return mid;
		}
	}
};