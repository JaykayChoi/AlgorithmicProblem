#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

//���ڿ� �� ���� �Է����� �޾� �� �� �ϳ��� �ٸ� �ϳ��� �������� �Ǻ�.
//��ҹ��� ������
//���鵵 ���� �ϳ��� ���

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