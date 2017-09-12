#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

//GCD is Greatest common divisor
int calcGCD(int a, int b)
{
	int remainder;
	if (a < 1 || b < 1)
		return 0;

	if (a < b)
		return calcGCD(b, a);

	while ((remainder = a % b) != 0)
	{
		a = b;
		b = remainder;
	}
	return b;
}

int main()
{
	int cases, a, b;
	cin >> cases;
	for (int c = 0; c < cases; c++)
	{
		cin >> a >> b;
		int GCD = calcGCD(a, b);
		cout << a * b / GCD << " " << GCD << endl;
	}

	return 0;
}