#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <string>
using namespace std;
typedef long long ll;

//https://www.acmicpc.net/problem/1025
int n, m;
int numbers[10][10];

bool isSquareNumber(ll number)
{
	ll sqrtN = sqrt(number);
	return sqrtN * sqrtN == number;
}

int getMaxSquareNumber()
{
	ll ret = -1;
	for (int y = 1; y <= n; y++)
	{
		for (int dY = -1 * (n - 1); dY < n; dY++)
		{
			for (int x = 1; x <= m; x++)
			{
				for (int dX = -1 * (m - 1); dX < m; dX++)
				{
					if (dY == 0 && dX == 0)
						continue;
					string strNum = "";
					for (int i = 0; ; i++)
					{
						int curY = y + dY * i;
						int curX = x + dX * i;
						if (curY <= 0 || curY > n || curX <= 0 || curX > m || numbers[curY][curX] == -1)
							break;
						strNum += to_string(numbers[curY][curX]);
						ll num = stoll(strNum);
						if (isSquareNumber(num))
							ret = max(ret, num);
					}
				}
			}
		}
	}
	return ret;
}

int main()
{
	memset(numbers, -1, sizeof(numbers));
	cin >> n >> m;
	if (n == 0 || m == 0)
	{
		cout << -1 << endl;
		return 0;
	}
	for (int i = 1; i <= n; i++)
	{
		string str;
		cin >> str;
		for (int j = 1; j <= m; j++)
			numbers[i][j] = str[j - 1] - '0';
	}

	cout << getMaxSquareNumber() << endl;

	return 0;
}