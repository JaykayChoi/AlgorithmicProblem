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
		//���� ��Ƽ�� ���� ��� ������ ��Ƽ������ �Űܾ� �ϴ� ���� Ž��.
		while (arr[left] < pivot)
		{
			left++;
		}

		//������ ��Ƽ�� ���� ��� ���� ��Ƽ������ �Űܾ� �ϴ� ���� Ž��.
		while (arr[right] > pivot)
		{
			right--;
		}

		//���ҵ� �ڸ��� �ٲٰ� left �� right �� �̵�.
		if (left <= right)
		{
			//swap(arr, left, right);	//���ҵ��� �ڸ��ٲ�.
			left++;
			right--;
		}
	}
	return left;
}

void quickSort(int arr[], int left, int right)
{
	int index = partition(arr, left, right);
	//���� ��Ƽ�� ����
	if (left < index - 1)
	{
		quickSort(arr, left, index - 1);
	}

	//������ ��Ƽ�� ����
	if (index < right)
	{
		quickSort(arr, index, right);
	}
}

int main()
{

	return 0;
}

