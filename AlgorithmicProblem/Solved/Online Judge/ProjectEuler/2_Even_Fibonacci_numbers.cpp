#include <iostream>
#include <map>
#include <ctime>

using namespace std;

//https://projecteuler.net/problem=2

const int limit = 4000000;

map<int, int> cache;
int recursive(int num)
{
	map<int, int>::iterator it = cache.find(num);
	if (it != cache.end())
		return it->second;

	int ret = 0;
	if (num == 0)
		ret = 0;
	else if (num == 1)
		ret = 1;
	else
		ret = recursive(num - 1) + recursive(num - 2);

	cache.insert(make_pair(num, ret));

	return ret;
}

int sub_main()
{
	int ret = 0;
	int num = 0;
	int i = 0;

	while (true)
	{
		num = recursive(i);

		if (num > limit)
			break;

		if (num % 2 == 0)
			ret += num;

		i++;
	}

	cout << ret << endl;

	system("pause");
	return 0;
}