/*
ID: jkchoik1
PROG: castle
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <string>
#include <map>
using namespace std;

ofstream fout("castle.out");
int width, height;
int floorplan[50][50];
set<int> totalVisitedRooms;
vector<int> sizes;
map<int, int> roomNumber;
map<int, int> roomSize;

//direction 0: west, 1: north, 2: east, 3: south
bool isWall(int curPosition, int direction)
{
	int curY = curPosition / 50;
	int curX = curPosition % 50;

	int cur = floorplan[curY][curX];

	if (cur & 1 << direction)
		return true;
	else
		return false;
}

int movingResult(int curPosition, int direction)
{
	int curY = curPosition / 50;
	int curX = curPosition % 50;

	switch (direction)
	{
	case 0:
		curX--;
		break;
	case 1:
		curY--;
		break;
	case 2:
		curX++;
		break;
	case 3:
		curY++;
		break;
	default:
		break;
	}

	if (curX < 0 || curY < 0 || curY >= height || curX >= width)
		return -1;

	return curY * 50 + curX;
}

bool isCheckmate(int prePosition, int curPosition)
{
	for (int i = 0; i < 4; i++)
	{
		if (isWall(curPosition, i) == false && prePosition != movingResult(curPosition, i))
			return false;
	}

	return true;
}

int searchRooms(vector<int>& path, set<int>& visited)
{
	int prePosition = path.size() > 1 ? path[path.size() - 2] : -51;
	int curPosition = path.back();

	if (isCheckmate(prePosition, curPosition))
		return visited.size();

	for (int i = 0; i < 4; i++)
	{
		if (isWall(path.back(), i))
			continue;

		int movingPosition = movingResult(path.back(), i);
		if (prePosition > 0 && (movingPosition == prePosition || movingPosition < 0))
			continue;

		set<int>::iterator it = visited.find(movingPosition);
		if (it != visited.end())
			continue;

		path.push_back(movingPosition);
		visited.insert(movingPosition);
		totalVisitedRooms.insert(movingPosition);
		searchRooms(path, visited);
		path.pop_back();
	}

	return visited.size();
}

void solveWithRemoving()
{
	sort(sizes.begin(), sizes.end());
	int maxRoomSize = sizes[sizes.size() - 1] + sizes[sizes.size() - 2];
	int largesRoom = 0;
	int retY, retX;
	string direction;
	for (int x = 0; x < width; x++)
	{
		for (int i = 1; i <= 2; i++)
		{
			for (int y = height - 1; y >= 0; y--)
			{
				if (isWall(y * 50 + x, i) == false)
					continue;
				int movingPosition = movingResult(y * 50 + x, i);
				if (movingPosition == -1)
					continue;
				map<int, int>::iterator it1 = roomNumber.find(y * 50 + x);
				map<int, int>::iterator it2 = roomNumber.find(movingPosition);
				int curRoomNumber = it1->second;
				int movingRoomNumber = it2->second;
				if (curRoomNumber == movingRoomNumber)
					continue;
				totalVisitedRooms.clear();

				it1 = roomSize.find(curRoomNumber);
				it2 = roomSize.find(movingRoomNumber);
				int rooms = it1->second + it2->second;
				if (rooms > largesRoom)
				{
					largesRoom = rooms;
					retY = y;
					retX = x;
					direction = i == 1 ? "N" : "E";
				}

				if (maxRoomSize == largesRoom)
					break;
			}
			if (maxRoomSize == largesRoom)
				break;
		}
		if (maxRoomSize == largesRoom)
			break;
	}

	fout << largesRoom << endl;
	fout << retY + 1 << " " << retX + 1 << " " << direction << endl;
}

void solve()
{
	int largesRoom = 0;
	int rooms = 0;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			set<int>::iterator it = totalVisitedRooms.find(y * 50 + x);
			if (it != totalVisitedRooms.end())
				continue;
			vector<int> path;
			path.push_back(y * 50 + x);
			set<int> visited;
			visited.insert(y * 50 + x);
			int num = searchRooms(path, visited);
			rooms++;
			sizes.push_back(num);
			for (set<int>::iterator it = visited.begin(); it != visited.end(); it++)
				roomNumber.insert(make_pair(*it, rooms));
			roomSize.insert(make_pair(rooms, num));
			largesRoom = max(largesRoom, num);

		}
	}

	fout << rooms << endl;
	fout << largesRoom << endl;
}

int main()
{
	ifstream fin("castle.in");

	fin >> width >> height;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int num;
			fin >> num;
			floorplan[y][x] = num;
		}
	}

	solve();
	solveWithRemoving();

	fin.close();
	fout.close();
	return 0;
}