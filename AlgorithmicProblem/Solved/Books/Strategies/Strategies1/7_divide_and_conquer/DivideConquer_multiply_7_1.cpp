#include <vector>
#include <algorithm>
#include "Utils.h"
#include <cstdlib>
#include <iostream>
using namespace std;

//큰 두 수의 곱.

class DivideConquer_multiply_7_1
{
public:
	void Solve()
	{
		cout << multiply(string("57957435165759068546235724743689"), string("45808567254727890871135784"), false) << endl;
		cout << multiply(string("57957435165759068546235724743689"), string("45808567254727890871135784"), true) << endl;

	}
private:
	string multiply(string& strA, string& strB, bool isKaratsuba)
	{
		vector<int> vA;
		vector<int> vB;

		//string strA = Utils::LongToString(_a);
		//string strB = Utils::LongToString(_b);
		
		for (string::size_type i = strA.size(); i > 0; i--)
			vA.push_back(strA[i-1] - '0');
		for (string::size_type i = strB.size(); i > 0; i--)
			vB.push_back(strB[i - 1] - '0');

		vector<int> answer;
		
		if (isKaratsuba)
			answer = karatsuba(vA, vB);
		else
			answer = multiplyNaive(vA, vB);

	
		string strAnswer = "";

		for (int i = answer.size() - 1; i >= 0; i--)
			strAnswer += Utils::IntToString(answer[i]);

		return strAnswer;
	}
	void normalize(vector<int>& num)
	{
		num.push_back(0);
		//자릿수 올림 처리.
		for (int i = 0; i < num.size() - 1; i++)
		{
			if (num[i] < 0)
			{
				int borrow = (abs(num[i]) + 9) / 10;
				num[i + 1] -= borrow;
				num[i] += borrow * 10;
			}
			else
			{
				num[i + 1] += num[i] / 10;
				num[i] %= 10;
			}
		}
		while (num.size() > 1 && num.back() == 0)
			num.pop_back();
	}

	//자연수의 곱을 반환.
	//각 배열에는 각 수의 자릿수가 1의 자리에서부터 시작해 저장되어 있다.
	//ex) multiply ({3,2,1},{6,5,4}) = 123 * 456 = 56088 = {8,8,0,6,5}
	vector<int> multiplyNaive(const vector<int>& a, const vector<int>& b)
	{
		vector<int> c(a.size() + b.size() + 1, 0);
		for (int i = 0; i < a.size(); i++)
			for (int j = 0; j < b.size(); j++)
				c[i + j] += a[i] * b[j];

		normalize(c);
		return c;
	}

	//https://ko.wikipedia.org/wiki/%EC%B9%B4%EB%9D%BC%EC%B6%94%EB%B0%94_%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98
	//카라츠바의 곱 연산 알고리즘.
	vector<int> karatsuba(const vector<int>& a, const vector<int>& b)
	{
		int an = a.size(), bn = b.size();

		//a가 b보다 짧을 경우 둘을 바꾼다.
		if (an < bn)
			return karatsuba(b, a);

		//a나 b가 비어 있는 경우
		if (an == 0 || bn == 0)
			return vector<int>();

		if (an <= 5)
			return multiplyNaive(a, b);

		int half = an / 2;

		//a와 b를 밑에서 half 자리와 나머지로 분리한다.
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
						int sum = a[i] + b[i-k];
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
	
	//a -= b. a >= b 를 가정.
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
		
};