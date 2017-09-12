#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#define CODE_WORKS true
using namespace std;

string convertInt(int num) {
	stringstream ss;
	ss << num;
	return ss.str();
}

char symbol(int num) { //sets some numbers to letters for bases over 10 (Only works up to base 36)
	string symbols = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return symbols[num];
}

string from_10(int num, int base) { //converts FROM base 10 to specified base
	vector<char> con_digs;

	int size = 0;
	while (num / base != 0) {
		con_digs.push_back(symbol(num % base));
		size++;

		num = num / base;
	}

	con_digs.push_back(symbol(num));
	size++;

	string con_num = "";

	for (int i = size - 1; i > -1; i--) {
		con_num += con_digs[i];
	}

	return con_num;
}

int width, height;
int roomNum = 0;

struct tile {
	int room;
	bool visited;
	bool walls[4]; //order: south, east, north, west
};

struct wall {
	int x, y;
	char direct;
	bool operator < (const wall & b) const {
		return x < b.x;
	}
};

vector<vector<tile> > castle;

int area;
bool removed = false;

void flood_fill(int n, int m) {
	if (n == -1 || m == -1 || n == height || m == width || castle[n][m].visited) return;
	else {
		castle[n][m].visited = true;
		castle[n][m].room = roomNum;
		area++;
		if (!castle[n][m].walls[0]) flood_fill(n + 1, m);
		if (!castle[n][m].walls[1]) flood_fill(n, m + 1);
		if (!castle[n][m].walls[2]) flood_fill(n - 1, m);
		if (!castle[n][m].walls[3]) flood_fill(n, m - 1);
	}
}

int main() {
	ifstream in("castle.in");
	ofstream out("castle.out");

	in >> width >> height;

	castle.resize(height);
	for (int i = 0; i < height; i++) castle[i].resize(width);

	for (int i = 0; i < height; i++) { //Input and corridor assignment
		for (int j = 0; j < width; j++) {
			int num;
			in >> num;
			string binum = from_10(num, 2);
			while (binum.length() != 4)  binum = "0" + binum;
			for (int k = 0; k < 4; k++) {
				if (binum[k] == '1') castle[i][j].walls[k] = true;
				else castle[i][j].walls[k] = false;
			}
			castle[i][j].visited = false;
		}
	}

	vector<int> rooms;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (!castle[i][j].visited) {
				area = 0;
				flood_fill(i, j);
				rooms.push_back(area);
				roomNum++;
			}
		}
	}

	int largeCArea = 0;
	int x, y;
	char direct;

	for (int i = 0; i < height; i++) 
	{
		for (int j = 0; j < width; j++) 
		{
			if (j != width - 1 && castle[i][j].walls[1] && castle[i][j].room != castle[i][j + 1].room) 
			{
				int cArea = rooms[castle[i][j].room] + rooms[castle[i][j + 1].room];
				if (cArea > largeCArea) {
					largeCArea = cArea;
					x = j; y = i;
					direct = 'E';
				}
				else if (cArea == largeCArea) {
					if (j < x) { x = j; y = i; direct = 'E'; }
					else if (j == x && i > y) { y = i; direct = 'E'; }
				}
			}
			if (i != 0 && castle[i][j].walls[2] && castle[i][j].room != castle[i - 1][j].room) 
			{
				int cArea = rooms[castle[i][j].room] + rooms[castle[i - 1][j].room];
				if (cArea > largeCArea) {
					largeCArea = cArea;
					x = j; y = i;
					direct = 'N';
				}
				else if (cArea == largeCArea) {
					if (j < x) { x = j; y = i; direct = 'N'; }
					else if (j == x && i > y) { y = i; direct = 'N'; }
					else if (j == x && i == y && direct == 'E') direct = 'N';
				}
			}
		}
	}

	sort(rooms.begin(), rooms.begin() + rooms.size());
	out << roomNum << endl << rooms[roomNum - 1] << endl;
	out << largeCArea << endl << y + 1 << " " << x + 1 << " " << direct << endl;
}