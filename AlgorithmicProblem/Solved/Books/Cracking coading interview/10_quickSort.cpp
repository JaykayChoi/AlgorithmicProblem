#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <string>
using namespace std;

int partition(int arr[], int left, int right)
{
	int pivot = arr[(left + right) / 2];
	while (left <= right)
	{
		//왼쪽 파티션 원소 가운데 오른쪽 파티션으로 옮겨야 하는 원소 탐색.
		while (arr[left] < pivot)
		{
			left++;
		}

		//오른쪽 파티션 원소 가운데 왼쪽 파티션으로 옮겨야 하는 원소 탐색.
		while (arr[right] > pivot)
		{
			right--;
		}

		//원소들 자리를 바꾸고 left 와 right 를 이동.
		if (left <= right)
		{
			//swap(arr, left, right);	//원소들을 자리바꿈.
			left++;
			right--;
		}
	}
	return left;
}

void quickSort(int arr[], int left, int right)
{
	int index = partition(arr, left, right);
	//왼쪽 파티션 정렬
	if (left < index - 1)
	{
		quickSort(arr, left, index - 1);
	}

	//오른쪽 파티션 정렬
	if (index < right)
	{
		quickSort(arr, index, right);
	}
}

int main()
{

	return 0;
}

