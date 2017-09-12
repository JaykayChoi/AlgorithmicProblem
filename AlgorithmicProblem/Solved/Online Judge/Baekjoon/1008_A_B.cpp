#include <fstream>
#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

//https://www.acmicpc.net/problem/1008
int main()
{
	double a, b;
	cin >> a >> b;
	cout.precision(numeric_limits<double>::max_digits10);
	cout << fixed << a / b << endl;

	return 0;
}
