#pragma warning (disable:4996)
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
#include <vector>

using namespace std;

//bool solution2(vector<int> arr)
//{
//	sort(arr.begin(), arr.end());
//	for (int i = 0; i < arr.size(); i++)
//	{
//		if (arr[i] != i + 1)
//		{
//			return false;
//		}
//	}
//	return true;
//}
//
//int cache[1000][1000];
//int solution4(vector<vector<int>> board)
//{
//	int ret = 0;
//	int n = board.size();
//	int m = board[0].size();
//
//	for (int i = 0; i < m; i++)
//	{
//		if (board[0][i])
//		{
//			cache[0][i] = 1;
//			ret = 1;
//		}
//	}
//	for (int i = 0; i < n; i++)
//	{
//		if (board[i][0])
//		{
//			cache[i][0] = 1;
//			ret = 1;
//		}
//	}
//
//	for (int i = 1; i < n; i++)
//	{
//		for (int j = 1; j < m; j++)
//		{
//			if (board[i][j])
//			{
//				cache[i][j] = min(min(cache[i - 1][j], cache[i][j - 1]), cache[i - 1][j - 1]) + 1;
//				if (cache[i][j] > ret)
//				{
//					ret = cache[i][j];
//				}
//			}
//		}
//	}
//	return ret * ret;
//}

//int cache[100000][4];
//int path(int y, int x, const vector<vector<int>>& land)
//{
//	if (y == land.size() - 1) {
//		return land[y][x];
//	}
//	int temp = 0;
//	int& ret = cache[y][x];
//	if (ret != -1)
//		return ret;
//	for (int i = 0; i < 4; i++) {
//		if (i == x)
//			continue;
//		temp = max(temp, path(y + 1, i, land));
//		ret = temp + land[y][x];
//	}
//	return ret;
//}
//int solution5()
//{
//	memset(cache, -1, sizeof(cache));
//
//	vector<vector<int>> land;
//
//	vector<int> temp0;
//	vector<int> temp1;
//	vector<int> temp2;
//
//
//	temp0.push_back(1);
//	temp0.push_back(2);
//	temp0.push_back(3);
//	temp0.push_back(5);
//
//	temp1.push_back(5);
//	temp1.push_back(6);
//	temp1.push_back(7);
//	temp1.push_back(8);
//
//	temp2.push_back(4);
//	temp2.push_back(3);
//	temp2.push_back(2);
//	temp2.push_back(1);
//
//	land.push_back(temp0);
//	land.push_back(temp1);
//	land.push_back(temp2);
//
//
//
//	int ret = 0;
//	for (int i = 0; i < 4; i++) {
//		ret = max(ret, path(0, i, land));
//	}
//	return ret;
//}

//int cache[100001][2];
//int recursive(int i, bool bIsFirstSelected, const vector<int>& sticker)
//{
//	if (i >= sticker.size())
//		return 0;
//
//	if (i == sticker.size() - 1) {
//		if (bIsFirstSelected) {
//			return cache[i][bIsFirstSelected] = 0;
//		}
//		cache[i][bIsFirstSelected] = sticker[i];
//		return sticker[i];
//	}
//
//	int& ret = cache[i][bIsFirstSelected];
//	if (ret != -1)
//		return ret;
//
//	return ret = max(recursive(i + 1, bIsFirstSelected, sticker), recursive(i + 2, bIsFirstSelected, sticker) + sticker[i]);
//}
//int solution6(vector<int> sticker)
//{
//	memset(cache, -1, sizeof(cache));
//	int ret = 0;
//	ret = max(recursive(1, false, sticker), recursive(2, true, sticker) + sticker[0]);
//	return ret;
//}


//["ba", "na", "n", "a"]	"banana"	3
//["app", "ap", "p", "l", "e", "ple", "pp"]	"apple"	2
//["ba", "an", "nan", "ban", "n"]	"banana" - 1

int solution(vector<string> strs, string t)
{
	int answer = 0;

	return answer;
}

int main()
{
	vector<int> num;
	num.push_back(14);
	num.push_back(6);
	num.push_back(5);
	num.push_back(11);
	num.push_back(3);
	num.push_back(9);
	num.push_back(2);
	num.push_back(10);
	printf("%d", solution(num));

	return 0;
}

