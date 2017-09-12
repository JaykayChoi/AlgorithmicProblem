#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

//문자열 두 개를 입력으로 받아 그 중 하나가 다른 하나의 순열인지 판별.
//대소문자 구별함
//공백도 문자 하나로 취급

bool permutation(const string& a, const string& b)
{
	// Create a copy of the two strings, we do not wish to modify those that were passed as parameters.
	string str_a(a);
	string str_b(b);

	if (str_a.length() != str_b.length())
	{
		return false;
	}

	sort(str_a.begin(), str_a.end());
	sort(str_b.begin(), str_b.end());

	for (int i = 0; i < str_a.length(); i++)
	{
		if (str_a[i] != str_b[i])
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