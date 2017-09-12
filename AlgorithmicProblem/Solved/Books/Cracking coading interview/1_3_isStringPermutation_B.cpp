#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

//문자열 두 개를 입력으로 받아 그 중 하나가 다른 하나의 순열인지 판별.
//대소문자 구별함
//공백도 문자 하나로 취급

bool permutation(const string& a, const string& b)
{
	if (a.length() != b.length())
	{
		return false;
	}

	int ascii_set[256] = { 0 };

	for (int i = 0; i < a.length(); i++)
	{
		int val = static_cast<int>(a[i]);
		ascii_set[val]++;
	}

	for (int i = 0; i < b.length(); i++)
	{
		int val = static_cast<int>(b[i]);

		if ((--ascii_set[val]) < 0)
		{
			return false;
		}
	}

	return true;
}

string result(bool value)
{
	if (value)
	{
		return "True";
	}

	return "False";
}

int run()
{
	string a = "apple";
	string b = "papel";

	cout << "Result for " << a << " and " << b << " is " << result(permutation(a, b)) << endl;

	return 0;
}