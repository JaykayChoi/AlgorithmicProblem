#include<iostream>
#include<memory>
#include<string>

using namespace std;

//�־��� ���ڿ� ���� ��� ������ %20 ���� �ٲٴ� �ż��� �ۼ�.
//���ڿ� ���� �߰��� �ʿ��� ���ڵ��� ���� �� �ִ� ����� ������ �ִٰ� ����
//�׸��� ������ �����ϴ� ���ڿ��� ���̵� �Բ� �־���.

void replaceSpaces(unique_ptr<char[]> &str, int length) //char str[]
{
	int newLength, spaceCount = 0;

	//count the number of spaces in the given string.
	for (int i = 0; i < length; i++)
	{
		if (str[i] == ' ')
		{
			spaceCount++;
		}
	}

	//calculate new string size.
	newLength = length + spaceCount * 2;
	str[newLength] = '\0';

	//copying the characters backwards and inserting %20
	for (int i = length - 1; i >= 0; i--)
	{
		if (str[i] == ' ')
		{
			str[newLength - 1] = '0';
			str[newLength - 2] = '2';
			str[newLength - 3] = '%';
			newLength -= 3;
		}
		else
		{
			str[newLength - 1] = str[i];
			newLength--;
		}
	}
}

int run()
{
	string str = "abc d e f";

	// Increasing length of the string to meet question requirement of 'true' length by using char array. (Note: using a unique_ptr here)
	auto newStr = make_unique<char[]>(str.length() + 3 * 2 + 1);

	for (int i = 0; i < str.length(); i++)
	{
		newStr[i] = str[i];
	}

	cout << "Original string is " << str << endl;
	replaceSpaces(newStr, str.length());
	cout << "New string with %20 is " << newStr.get() << endl;

	return 0;
}