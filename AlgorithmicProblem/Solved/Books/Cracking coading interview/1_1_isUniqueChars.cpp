#include <string>

using namespace std;

//문자열에 포함된 문자들이 전부 유일한지 검사하는 알고리즘을 구현. 다른 자료구조를 사용할 수 없다.
//ASCII 문자열인지 유니코드인지 질문을 해야 됨.

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