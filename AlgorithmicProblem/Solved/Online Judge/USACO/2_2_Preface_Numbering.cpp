#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

//http://jaykaychoi.tistory.com/75

int pageNumbers[7];
void calcPageNumber(int number)
{
	int num = number;

	int quotient = num / 1000;
	pageNumbers[6] += quotient;
	num %= 1000;

	if (num >= 900)
	{
		pageNumbers[6]++;
		pageNumbers[4]++;
		num %= 900;
	}

	quotient = num / 500;
	pageNumbers[5] += quotient;
	num %= 500;

	quotient = num / 100;
	if (quotient == 4)
	{
		pageNumbers[5]++;
		pageNumbers[4]++;
	}
	else
		pageNumbers[4] += quotient;
	num %= 100;

	if (num >= 90)
	{
		pageNumbers[4]++;
		pageNumbers[2]++;
		num %= 90;
	}

	quotient = num / 50;
	pageNumbers[3] += quotient;
	num %= 50;

	quotient = num / 10;
	if (quotient == 4)
	{
		pageNumbers[3]++;
		pageNumbers[2]++;
	}
	else
		pageNumbers[2] += quotient;
	num %= 10;

	if (num >= 9)
	{
		pageNumbers[2]++;
		pageNumbers[0]++;
		num %= 9;
	}

	quotient = num / 5;
	pageNumbers[1] += quotient;
	num %= 5;

	if (num == 4)
	{
		pageNumbers[1]++;
		pageNumbers[0]++;
	}
	else
		pageNumbers[0] += num;
}

int main()
{
	ifstream fin("preface.in");
	ofstream fout("preface.out");

	int n;
	fin >> n;

	for (int i = 1; i <= n; i++)
		calcPageNumber(i);

	for (int i = 0; i < 7; i++)
	{
		if (pageNumbers[i] == 0)
			continue;

		switch (i)
		{
		case 0:
			fout << "I " << pageNumbers[i] << endl;
			break;
		case 1:
			fout << "V " << pageNumbers[i] << endl;
			break;
		case 2:
			fout << "X " << pageNumbers[i] << endl;
			break;
		case 3:
			fout << "L " << pageNumbers[i] << endl;
			break;
		case 4:
			fout << "C " << pageNumbers[i] << endl;
			break;
		case 5:
			fout << "D " << pageNumbers[i] << endl;
			break;
		case 6:
			fout << "M " << pageNumbers[i] << endl;
			break;
		default:
			break;
		}
	}

	fin.close();
	fout.close();
	return 0;
}
