#include <iostream>
#include <memory>


using namespace std;

//이미지를 표현하는 NxN 배열이 있다. 이미지의 각 픽셀은 4바이트로 표현된다.
//이때, 이미지를 90도 회전시키는 메서드를 작성.
//부가적인 행렬을 사용하지 않는다.

void rotate(int* matrix, int n)
{
	for (int layer = 0; layer < n / 2; ++layer)
	{
		int first = layer;
		int last = n - 1 - layer;

		for (int i = first; i < last; ++i)
		{
			int offset = i - first;
			// save top
			int top = matrix[first * n + i];

			// left to top
			matrix[first * n + i] = matrix[(last - offset) * n + first];

			// bottom to left
			matrix[(last - offset) * n + first] = matrix[last * n + (last - offset)];

			// right to bottom
			matrix[last * n + (last - offset)] = matrix[i * n + last];

			// top to right
			matrix[i * n + last] = top;
		}
	}
}

void printMatrix(int* matrix, int m, int n)
{
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cout << matrix[i * n + j] << " ";
		}

		cout << endl;
	}
}

int run()
{
	int matrix[][5] = { { 1, 2, 3, 4, 5 },
	{ 6, 7, 8, 9, 10 },
	{ 11, 12, 13, 14, 15 },
	{ 16, 17, 18, 19, 20 },
	{ 21, 22, 23, 24, 25 } };
	int* matrixPtr = (int*)matrix;

	cout << "original matrix is :" << endl;
	printMatrix(matrixPtr, 5, 5);
	rotate(matrixPtr, 5);
	cout << "rotated matrix is: " << endl;
	printMatrix(matrixPtr, 5, 5);

	return 0;
}