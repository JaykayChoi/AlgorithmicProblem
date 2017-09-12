#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <string>
using namespace std;
//https://www.acmicpc.net/problem/1029
const int MAX_N = 15;
int n;
int prices[MAX_N + 1][MAX_N + 1];
int cache[1 << MAX_N][10][MAX_N + 1];

int getMaxBuyingPeople(int bought, int price, int seller)
{
	if (bought == ((1 << n) - 1))
		return 0;
	bool buyable = false;
	for (int buyerCandidate = 0; buyerCandidate < n; buyerCandidate++)
	{
		if (bought & (1 << buyerCandidate))
			continue;

		for (int sellerCandidate = 0; sellerCandidate < n; sellerCandidate++)
		{
			if (bought & (1 << buyerCandidate))
				continue;
			if (prices[sellerCandidate][buyerCandidate] >= price)
			{
				buyable = true;
				break;
			}
		}
		if (buyable)
			break;
	}
	if (buyable == false)
		return 0;

	int& ret = cache[bought][price][seller];
	if (ret != -1)
		return ret;
	ret = 0;

	for (int buyer = 0; buyer < n; buyer++)
	{
		if (bought & (1 << buyer))
			continue;
		if (prices[seller][buyer] >= price)
			ret = max(ret, getMaxBuyingPeople(bought + (1 << buyer), prices[seller][buyer], buyer) + 1);
	}
	return ret;
}

int main()
{
	memset(cache, -1, sizeof(cache));
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		string str;
		cin >> str;
		for (int j = 0; j < n; j++)
			prices[i][j] = str[j] - '0';
	}
	cout << getMaxBuyingPeople(1, 0, 0) + 1 << endl;

	return 0;
}