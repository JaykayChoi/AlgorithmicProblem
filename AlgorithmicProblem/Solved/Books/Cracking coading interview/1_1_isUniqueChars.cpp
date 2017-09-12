#include <string>

using namespace std;

//���ڿ��� ���Ե� ���ڵ��� ���� �������� �˻��ϴ� �˰����� ����. �ٸ� �ڷᱸ���� ����� �� ����.
//ASCII ���ڿ����� �����ڵ����� ������ �ؾ� ��.

bool isUniqueChars1(const string& str)
{
	if (str.length() > 256)
	{
		return false;
	}

	bool ascii_set[256] = { false };

	for (int i = 0; i < str.length(); ++i)
	{
		int value = str[i];

		if (ascii_set[value])
		{
			return false;
		}

		ascii_set[value] = true;
	}

	return true;
}

bool isUniqueChars2(const string& str)
{
	if (str.length() > 256)
	{
		return false;
	}

	unsigned int checker = 0;

	for (int i = 0; i < str.length(); ++i)
	{
		int value = str[i] - 'a';

		if ((checker & (1 << value)) != 0)
		{
			return false;
		}

		checker |= (1 << value);
	}

	return true;
}