

//http://jaykaychoi.tistory.com/17


/*
ID: jkchoik1
PROG: transform
LANG: C++11
*/

#include <fstream>
#include <iostream>
using namespace std;

//동적 2차 배열을 더블 포인터로 표현

char** createMatrix(int row, int column)
{
	char **matrix = new char*[row];

	for (int i = 0; i < row; i++)
		matrix[i] = new char[column];

	return matrix;
}

void deleteMatrix(char** matrix, int row)
{
	for (int i = 0; i < row; i++)
		delete[] matrix[i];

	delete[]matrix;
}


void rotateMatrix90Degree(char **matrix, int N)
{
	for (int i = 0; i < N / 2; i++)
	{
		for (int j = i; j < N - i - 1; j++)
		{
			char temp = matrix[i][j];
			matrix[i][j] = matrix[N - 1 - j][i];
			matrix[N - 1 - j][i] = matrix[N - 1 - i][N - 1 - j];
			matrix[N - 1 - i][N - 1 - j] = matrix[j][N - 1 - i];
			matrix[j][N - 1 - i] = temp;
		}
	}
}

void reflectMatrix(char **matrix, int row, int column)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column / 2; j++)
		{
			char temp = matrix[i][j];
			matrix[i][j] = matrix[i][column - 1 - j];
			matrix[i][column - 1 - j] = temp;
		}
	}
}

bool isSame(char **a, char **b, int row, int column)
{
	bool ok = true;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (a[i][j] != b[i][j])
			{
				ok = false;
				break;
			}
		}
		if (ok == false)
			break;
	}
	return ok;
}

int sub_main()
{
	ofstream fout("transform.out");
	ifstream fin("transform.in");

	int N;

	fin >> N;

	char **before = createMatrix(N, N);
	char **after = createMatrix(N, N);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			fin >> before[i][j];
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			fin >> after[i][j];
		}
	}

	while (true)
	{
		rotateMatrix90Degree(before, N);
		if (isSame(before, after, N, N))
		{
			fout << 1 << endl;
			break;
		}

		rotateMatrix90Degree(before, N);
		if (isSame(before, after, N, N))
		{
			fout << 2 << endl;
			break;
		}

		rotateMatrix90Degree(before, N);
		if (isSame(before, after, N, N))
		{
			fout << 3 << endl;
			break;
		}

		rotateMatrix90Degree(before, N);
		if (isSame(before, after, N, N))
		{
			fout << 6 << endl;
			break;
		}

		reflectMatrix(before, N, N);
		if (isSame(before, after, N, N))
		{
			fout << 4 << endl;
			break;
		}

		rotateMatrix90Degree(before, N);
		if (isSame(before, after, N, N))
		{
			fout << 5 << endl;
			break;
		}

		rotateMatrix90Degree(before, N);
		if (isSame(before, after, N, N))
		{
			fout << 5 << endl;
			break;
		}

		rotateMatrix90Degree(before, N);
		if (isSame(before, after, N, N))
		{
			fout << 5 << endl;
			break;
		}

		fout << 7 << endl;
		break;
	}

	deleteMatrix(before, N);
	deleteMatrix(after, N);

	return 0;
}