#include "Utils.h"
using namespace std;
using namespace Utils;
#define FOR(i,a,b) for(int i = (a); i < (b); ++i)
#define REP(i,n) FOR(i,0,n)
#define FORE(it,x) for(typeof(x.begin()) it=x.begin();it!=x.end();++it)
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define CLEAR(x,with) memset(x,with,sizeof(x))
#define sz size()
typedef long long ll;

//https://algospot.com/judge/problem/read/BOARDCOVER

class BoardCover_6_6
{
public:

private:
	// �־��� ĭ�� ���� �� �ִ� 4���� ���
	// ����� �����ϴ� 3ĭ�� ����� ��ġ (dy,dx) �� ���
	const int coverType[4][3][2] = {
		{ { 0, 0 },{ 1, 0 },{ 0, 1 } },
		{ { 0, 0 },{ 0, 1 },{ 1, 1 } },
		{ { 0, 0 },{ 1, 0 },{ 1, 1 } },
		{ { 0, 0 },{ 1, 0 },{ 1, -1 } } };

	// board �� (y,x) �� type �� ������� ���ų�, ������ ����� ���ش�.
	// delta = 1 �̸� ����, -1 �̸� ������ ����� ���ش�.
	// ���� ����� ����� ������ ���� ��� (������ ������ �����ų�,
	// ��ġ�ų�, ���� ĭ�� ���� ��) false �� ��ȯ�Ѵ�.
	bool set(vector<vector<int> >& board, int y, int x, int type, int delta) 
	{
		bool ok = true;
		for (int i = 0; i < 3; ++i) {
			const int ny = y + coverType[type][i][0];
			const int nx = x + coverType[type][i][1];
			if (ny < 0 || ny >= board.size() || nx < 0 || nx >= board[0].size())
				ok = false;
			else if ((board[ny][nx] += delta) > 1)
				ok = false;
		}
		return ok;
	}

	// board �� ��� �� ĭ�� ���� �� �ִ� ����� ���� ��ȯ�Ѵ�
	// board[i][j] = 1 �̹� ���� ĭ Ȥ�� ���� ĭ
	// board[i][j] = 0 ���� ������ ���� ĭ
	int cover(vector<vector<int> >& board) {
		// ���� ä���� ���� ĭ �� ���� ���� ���ʿ� �ִ� ĭ�� ã�´�
		int y = -1, x = -1;
		for (int i = 0; i < board.size(); ++i) 
		{
			for (int j = 0; j < board[i].size(); ++j)
			{
				if (board[i][j] == 0)
				{
					y = i;
					x = j;
					break;
				}
			}
			if (y != -1) 
				break;
		}
		// ���� ���: ��� ĭ�� ä������ 1�� ��ȯ�Ѵ�
		if (y == -1) 
			return 1;

		int ret = 0;
		for (int type = 0; type < 4; ++type) 
		{
			// ���� board[y][x] �� type ���·� ���� �� ������ ���ȣ���Ѵ�
			if (set(board, y, x, type, 1))
				ret += cover(board);
			// ������ ����� ġ���
			set(board, y, x, type, -1);
		}
		return ret;
	}

	int CInput() {
		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc) {
			int height, width;
			cin >> height >> width;
			assert(1 <= height && height <= 20);
			assert(1 <= width && width <= 20);
			vector<vector<int> > board(height, vector<int>(width, 0));
			int whites = 0;
			for (int i = 0; i < (height); i++) {
				string s;
				cin >> s;
				for (int j = 0; j < (width); j++) {
					if (s[j] == '#')
						board[i][j] = 1;
				}
				whites += count(board[i].begin(), board[i].end(), 0);
			}
			assert(whites <= 50);
			int ways = cover(board);
			cout << ways << endl;
		}
	}
};