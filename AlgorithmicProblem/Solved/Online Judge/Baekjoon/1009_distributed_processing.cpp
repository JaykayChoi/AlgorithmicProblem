#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

//https://www.acmicpc.net/problem/1009
int main()
{
	int cases;
	cin >> cases;
	for (int i = 0; i < cases; i++)
	{
		int a, b;
		cin >> a >> b;

		string str = to_string(a);
		a = str[str.size() - 1] - '0';

		b--;
		b %= 4;
		int ret = a;
		for (int j = 0; j < b; j++)
		{
			ret *= a;
			str = to_string(ret);
			ret = str[str.size() - 1] - '0';
			if (ret == 0)
				break;
		}
		if (ret == 0)
			cout << 10 << endl;
		else
			cout << ret << endl;
	}

	return 0;
}
