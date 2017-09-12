#include<iostream>
#include<memory>
#include<string>

using namespace std;

//주어진 문자열 내의 모든 공백을 %20 으로 바꾸는 매서드 작성.
//문자열 끝에 추가로 필요한 문자들을 더할 수 있는 충분한 공간이 있다고 가정
//그리고 공백을 포함하는 문자열의 길이도 함께 주어짐.

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