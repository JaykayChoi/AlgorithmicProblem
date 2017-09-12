#include <iostream>
#include <string>
using namespace std;

//did not post 

//https://projecteuler.net/problem=4

string reverseString(string str)
{
	//reverse(str.begin(), str.end());
	//return str;

	string ret = "";
	for (int i = str.length() - 1; i >= 0; i--)
		ret += str[i];
	return ret;
}

bool isPalindromic(int num)
{
	string str = to_string(num);
	return str == reverseString(str);
}

int submain()
{
	int ret = 0;
	for (int i = 100; i < 1000; i++)
	{
		for (int j = 100; j < 1000; j++)
		{
			int multi = i * j;
			if (multi < ret)
				continue;
			if (isPalindromic(multi))
				ret = multi;
		}
	}

	cout << ret << endl;

	system("pause");
	return 0;
}