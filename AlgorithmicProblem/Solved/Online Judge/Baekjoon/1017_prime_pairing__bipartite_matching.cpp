#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

//https://www.acmicpc.net/problem/1017

const int MAX_NUMBER = 2001;
const int MAX_NUMBERS = 50;

int maxNum = 2000;
unsigned char sieve[(MAX_NUMBER + 7) / 8];

vector<int> adjacent[MAX_NUMBERS / 2];
int aMatch[MAX_NUMBERS / 2], bMatch[MAX_NUMBERS / 2];
bool visited_ForDFS[MAX_NUMBERS / 2];

int n;
vector<int> numbers;
vector<int> id[2];

bool isPrime(int number)
{
	return sieve[number >> 3] & (1 << (number & 7));
}

void removeFromSieve(int number)
{
	sieve[number >> 3] &= ~(1 << (number & 7));
}

void eratosthenes()
{
	memset(sieve, 255, sizeof(sieve));

	removeFromSieve(0);
	removeFromSieve(1);

	int sqrtn = int(sqrt(maxNum));
	for (int i = 2; i <= sqrtn; ++i)
	{
		if (isPrime(i))
		{
			for (int j = i*i; j <= maxNum; j += i)
				removeFromSieve(j);
		}
	}
}

bool dfs(int a)
{
	if (visited_ForDFS[a])
		return false;
	visited_ForDFS[a] = true;

	for (vector<int>::iterator b = adjacent[a].begin(); b != adjacent[a].end(); b++)
	{
		if (bMatch[*b] == -1 || dfs(bMatch[*b]))
		{
			aMatch[a] = *b;
			bMatch[*b] = a;
			return true;
		}
	}
	return false;
}

void bipartiteMatching(int count)
{
	vector<int> ret;

	for (vector<int>::iterator it = adjacent[0].begin(); it != adjacent[0].end(); it++)
	{
		memset(aMatch, -1, sizeof(aMatch));
		memset(bMatch, -1, sizeof(bMatch));

		aMatch[0] = *it;
		bMatch[*it] = 0;
		int matching = 1;
		for (int i = 1; i < count; i++)
		{
			memset(visited_ForDFS, 0, sizeof(visited_ForDFS));
			visited_ForDFS[0] = true;
			if (dfs(i))
				matching++;
		}

		if (matching == n / 2)
		{
			ret.push_back(id[1][*it]);
		}
	}
	if (ret.empty())
		cout << -1 << endl;
	else
	{
		sort(ret.begin(), ret.end());
		bool isFirst = true;
		for (vector<int>::iterator it = ret.begin(); it != ret.end(); it++)
		{
			if (isFirst)
				isFirst = false;
			else
				cout << " ";
			cout << *it;
		}
		cout << endl;
	}

}

void placeNumber()
{
	int firstNumberType = 0;
	for (int i = 0; i < n; i++)
	{
		if (i == 0)
			firstNumberType = numbers[i] % 2;

		if (numbers[i] % 2 == firstNumberType)
			id[0].push_back(numbers[i]);
		else
			id[1].push_back(numbers[i]);
	}

	if (id[0].size() != id[1].size())
	{
		cout << -1 << endl;
		return;
	}

	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			if (isPrime(id[0][i] + id[1][j]))
				adjacent[i].push_back(j);
		}
	}

	bipartiteMatching(n / 2);
}



int main()
{
	eratosthenes();

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int num;
		cin >> num;
		numbers.push_back(num);
	}
	placeNumber();

	return 0;
}
