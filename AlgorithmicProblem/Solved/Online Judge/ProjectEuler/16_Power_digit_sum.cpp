#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

//https://projecteuler.net/problem=16

#pragma region Karatsuba
#pragma region helper func
//a += b * (10^k)
void addForKaratsuba(vector<int>& a, const vector<int>& b, int k)
{
	int aSize = a.size();
	int bSize = b.size();
	int count = max(aSize, bSize + k);

	int tempK = k;
	for (int i = 0; i < count; i++)
	{
		if (tempK <= 0)
		{
			if (bSize + k - i > 0)
			{
				if (aSize - i > 0)
				{
					int sum = a[i] + b[i - k];
					if (sum >= 10)
					{
						a[i] = sum % 10;

						if (aSize > i + 1)
							a[i + 1] += 1;
						else
						{
							a.push_back(1);
							aSize++;
						}
					}
					else
						a[i] = sum;

				}
				else
				{
					a.push_back(b[i - k]);
					aSize++;
				}
			}
		}
		else
		{
			if (aSize - i <= 0)
			{
				a.push_back(0);
				aSize++;
			}
		}
		tempK--;
	}
}

//a -= b. a >= b ¸¦ °¡Á¤.
void subtractForKaratsuba(vector<int>& a, const vector<int>& b)
{
	if (a.size() < b.size())
		return;
	int aSize = a.size();
	int bSize = b.size();
	for (int i = 0; i < aSize; i++)
	{
		if (bSize - i > 0)
		{
			int ret = a[i] - b[i];

			if (ret <= -1)
			{
				ret = a[i] + 10 - b[i];
				a[i + 1] -= 1;
			}

			a[i] = ret;
		}
	}
}

void normalize(vector<int>& numbers)
{
	numbers.push_back(0);
	for (int i = 0; i < numbers.size() - 1; i++)
	{
		if (numbers[i] >= 0)
		{
			numbers[i + 1] += numbers[i] / 10;
			numbers[i] %= 10;
		}
		else
		{
			int borrow = (abs(numbers[i]) + 9) / 10;
			numbers[i + 1] -= borrow;
			numbers[i] += borrow * 10;
		}
	}
	while (numbers.size() > 1 && numbers.back() == 0)
		numbers.pop_back();
}
#pragma endregion

vector<int> multiplyNaive(const vector<int>& a, const vector<int>& b)
{
	vector<int> ret(a.size() + b.size() + 1, 0);
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = 0; j < b.size(); j++)
			ret[i + j] += a[i] * b[j];
	}

	normalize(ret);
	return ret;
}

vector<int> karatsuba(const vector<int>& a, const vector<int>& b)
{
	int an = a.size(), bn = b.size();

	if (an < bn)
		return karatsuba(b, a);

	if (an == 0 || bn == 0)
		return vector<int>();

	if (an <= 10)
		return multiplyNaive(a, b);

	int half = an / 2;

	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
	vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());

	//z2 = a1 * b1
	vector<int> z2 = karatsuba(a1, b1);
	//z0 = a0 * b0
	vector<int> z0 = karatsuba(a0, b0);

	//a0 = a0 + a1
	//b0 = b0 + b1
	addForKaratsuba(a0, a1, 0);
	addForKaratsuba(b0, b1, 0);

	//z1 = (a0 * b0) - z0 - z2;
	vector<int> z1 = karatsuba(a0, b0);
	subtractForKaratsuba(z1, z0);
	subtractForKaratsuba(z1, z2);

	//ret = z0 + z1 * 10^half + z2 * 10^(half * 2)
	vector<int> ret;
	addForKaratsuba(ret, z0, 0);
	addForKaratsuba(ret, z1, half);
	addForKaratsuba(ret, z2, half + half);
	return ret;
}
#pragma endregion

string multiply(string& strA, string& strB)
{
	vector<int> a;
	vector<int> b;

	for (string::size_type i = strA.size(); i > 0; i--)
		a.push_back(strA[i - 1] - '0');
	for (string::size_type i = strB.size(); i > 0; i--)
		b.push_back(strB[i - 1] - '0');

	vector<int> answer = karatsuba(a, b);

	string ret = "";

	for (int i = answer.size() - 1; i >= 0; i--)
		ret += to_string(answer[i]);

	return ret;
}


string solve(int n)
{
	if (n == 1)
		return "2";
	if (n % 2 == 1)
		return multiply(solve(n - 1), string("2"));

	return multiply(solve(n / 2), solve(n / 2));
}

int submain()
{
	string str = solve(1000);

	int ret = 0;
	for (int i = 0; i < str.size(); i++)
		ret += (str[i] - '0');

	cout << ret << endl;

	system("pause");
	return 0;
}
