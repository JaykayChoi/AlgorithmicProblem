#include<iostream>
#include<string>
#include<sstream>

using namespace std;

//���� ���ڰ� �������� �ݺ��� ���, �� Ƚ���� ����� ���ڿ��� ����
//aabccccccccaaa -> a2b1c8a3
//���� ����� ��������� ���ڿ��� ���� ���ڿ����� ���������� �ʴ� ���, �״�� ��ȯ.

int stringToInt(const string& value)
{
	int temp;
	stringstream(value) >> temp;

	return temp;
}

string intToString(int value)
{
	string temp;
	stringstream convert;
	convert << value;
	temp = convert.str();

	return temp;
}

int countCompression(const string& str)
{
	if (str.length() == 0)
	{
		return 0;
	}

	char last = str.at(0);
	int size = 0;
	int count = 1;

	for (int i = 1; i < str.length(); i++)
	{
		if (str.at(i) == last)
		{
			count++;
		}
		else
		{
			last = str.at(i);
			size = size + 1 + intToString(count).length();
			count = 1;
		}
	}
	size = size + 1 + intToString(count).length();

	return size;
}

string compressBetter(const string& str)
{
	int size = countCompression(str);

	if (size >= str.length())
	{
		return str;
	}

	string newstr;
	char last = str.at(0);
	int count = 1;

	for (int i = 1; i < str.length(); i++)
	{
		if (str.at(i) == last)
		{
			count++;
		}
		else
		{
			newstr += last;
			newstr.append(intToString(count));
			last = str.at(i);
			count = 1;
		}
	}
	newstr += last;
	newstr.append(intToString(count));

	return newstr;
}

int run()
{
	string str = "abbccccccde";
	string newstr = compressBetter(str);
	cout << "Original string is " << str << endl;
	cout << "Compressed string is " << newstr << endl;

	return 0;
}