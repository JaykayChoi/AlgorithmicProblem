#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

//http://jaykaychoi.tistory.com/66

vector<string> readTxtFile(const string& path)
{
	ifstream file(path);

	vector<string> ret;
	string str;

	while (getline(file, str, ','))
	{
		str = str.substr(1, str.size() - 2);
		ret.push_back(str);
	}

	return ret;
}

int sumAlphabeticalValue(const string& str)
{
	int ret = 0;
	for (int i = 0; i < str.size(); i++)
		ret += str[i] - 'A' + 1;
	return ret;
}

int main()
{
	vector<string> names = readTxtFile("names.txt");
	sort(names.begin(), names.end());

	ll ret = 0;
	for (int i = 0; i < names.size(); i++)
		ret += ((i + 1) * sumAlphabeticalValue(names[i]));

	cout << ret << endl;
	system("pause");
	return 0;
}