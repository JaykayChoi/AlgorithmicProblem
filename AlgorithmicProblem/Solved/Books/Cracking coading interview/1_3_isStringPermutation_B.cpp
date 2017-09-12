#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

//���ڿ� �� ���� �Է����� �޾� �� �� �ϳ��� �ٸ� �ϳ��� �������� �Ǻ�.
//��ҹ��� ������
//���鵵 ���� �ϳ��� ���

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