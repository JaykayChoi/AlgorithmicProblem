#include "Utils.h"
using namespace std;
using namespace Utils;


class NumberBlock_9_19
{
public:

private:
	vector<int> moves;
	inline int cell(int y, int x) { return 1 << (y * 5 + x); }
	// �����ǿ� ���� �� �ִ� ��ϵ��� ��ġ�� �̸� ����Ѵ�
	void precalc() {
		// 3ĭ¥�� L�� ��� ��ϵ��� ����Ѵ�
		for (int y = 0; y < 4; ++y)
			for (int x = 0; x < 4; x++) {
				vector<int> cells;
				for (int dy = 0; dy < 2; ++dy)
					for (int dx = 0; dx < 2; dx++)
						cells.push_back(cell(y + dy, x + dx));
				int square = cells[0] + cells[1] + cells[2] + cells[3];
				for (int i = 0; i < 4; i++)
					moves.push_back(square - cells[i]);
			}
		// 2ĭ¥�� ��ϵ��� ����Ѵ�
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 4; j++) {
				moves.push_back(cell(i, j) + cell(i, j + 1));
				moves.push_back(cell(j, i) + cell(j + 1, i));
			}
		cerr << moves.size() << " moves generated." << endl;
	}

	char cache[1 << 25];
	// ���� ������ ���°� board �� �� ���� ������ ����� �¸����� ���θ� ��ȯ�Ѵ�
	// (y,x) ĭ�� ����� �ִ� <=> (y*5+x) �� ��Ʈ�� ���� �ִ�
	char play(int board) {
		// �޸������̼�
		char& ret = cache[board];
		if (ret != -1) return ret;
		ret = 0;
		for (int i = 0; i < moves.size(); ++i)
			if ((moves[i] & board) == 0)
				if (!play(board | moves[i])) {
					ret = 1;
					break;
				}
		return ret;
	}

	int CInput() {
		precalc();
		memset(cache, -1, sizeof(cache));

		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc) {
			int state = 0;
			for (int y = 0; y < 5; y++) {
				string board;
				cin >> board;
				for (int x = 0; x < 5; x++)
					if (board[x] == '#')
						state += (1 << (y * 5 + x));
			}
			if (play(state))
				printf("WINNING\n");
			else
				printf("LOSING\n");
		}

	}
};
