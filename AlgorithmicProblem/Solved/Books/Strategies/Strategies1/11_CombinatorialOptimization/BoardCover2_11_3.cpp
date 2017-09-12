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

//https://algospot.com/judge/problem/read/BOARDCOVER2

class BoardCover2_11_3
{
public:

private:
	int boardH, boardW;
	int covered[50][50];
	vector<string> board;
	int blockSize;

	// ����� �� ȸ���� ���¸� ��� ��ǥ�� ������� ������ �д�
	vector<vector<pair<int, int> > > rotations;

	// 2���� �迭 arr �� �ð�������� 90�� ���� ����� ��ȯ�Ѵ�
	vector<string> rotate(const vector<string>& arr) {
		vector<string> ret(arr[0].size(), string(arr.size(), ' '));
		for (int i = 0; i < arr.size(); i++)
			for (int j = 0; j < arr[0].size(); j++)
				ret[j][arr.size() - i - 1] = arr[i][j];
		return ret;
	}

	// block �� 4���� ȸ�� ���¸� ����� �̵��� ��� ��ǥ�� ������� ��ȯ�Ѵ�.
	void generateRotations(vector<string> block) {
		rotations.clear();
		rotations.resize(4);
		for (int rot = 0; rot < 4; rot++) {
			int originY = -1, originX = -1;
			for (int i = 0; i < block.size(); i++)
				for (int j = 0; j < block[i].size(); j++)
					if (block[i][j] == '#') {
						if (originY == -1) {
							originY = i;
							originX = j;
						}
						rotations[rot].push_back(make_pair(i - originY, j - originX));
					}
			// ����� �ð� �������� 90�� ȸ���Ѵ�
			block = rotate(block);
		}
		// 4���� ȸ�� ���� �� �ߺ��� ���� ��� �̸� �����Ѵ�
		sort(rotations.begin(), rotations.end());
		rotations.erase(unique(rotations.begin(), rotations.end()), rotations.end());
		blockSize = rotations[0].size();
	}

	// (y,x) �� (0,0) ���� �ؼ� cells �� ǥ���� ����� �������ų�, ���ø���.
	// delta �� 1 �̸� ��������, -1 �̸� ���ø���.
	// ����� ���� ĭ�̳� �ٸ� ��ϰ� ��ġ�ų� ������ ������ ������ false �� ��ȯ�Ѵ�.
	bool set(int y, int x, const vector<pair<int, int> >& cells, int delta) {
		bool ok = true;
		for (int i = 0; i < cells.size(); i++) {
			int cy = y + cells[i].first, cx = x + cells[i].second;
			if (cy < 0 || cx < 0 || cy >= boardH || cx >= boardW)
				ok = false;
			else {
				covered[cy][cx] += delta;
				if (covered[cy][cx] > 1) ok = false;
			}
		}
		return ok;
	}

	int best;

	// placed: ���ݱ��� ���� ����� ��
	// blanks: ���� ��ĭ�� ��
	void search(int placed, int blanks) {
		// ��ĭ �� ���� ���� ���ʿ� �ִ�
		int y = -1, x = -1;
		for (int i = 0; i < boardH; i++) {
			for (int j = 0; j < boardW; j++)
				if (covered[i][j] == 0) {
					y = i;
					x = j;
					break;
				}
			if (y != -1) break;
		}
		// ���� ���: �������� ��� ĭ�� ó���� ���
		if (y == -1) {
			best = max(best, placed);
			return;
		}

		// ����ġ��
		int upperBound = blanks / blockSize + placed;
		if (upperBound <= best) return;

		// �� ĭ�� ���´�
		for (int i = 0; i < rotations.size(); i++) {
			if (set(y, x, rotations[i], 1))
				search(placed + 1, blanks - blockSize);
			set(y, x, rotations[i], -1);
		}

		// �� ĭ�� ���� �ʰ� ���� �д�
		covered[y][x]++;
		search(placed, blanks - 1);
		covered[y][x]--;
	}

	int solve() {
		int blanks = 0;
		for (int i = 0; i < boardH; i++)
			for (int j = 0; j < boardW; j++)
				if (board[i][j] == '.')
					++blanks;
		best = 0;
		for (int i = 0; i < boardH; i++) {
			for (int j = 0; j < boardW; j++)
				covered[i][j] = (board[i][j] == '#' ? 1 : 0);
		}

		//clock_t begin = clock();
		search(0, blanks);
		//double elapsed = (clock() - begin) * 1.0 / CLOCKS_PER_SEC;
		//fprintf(stderr, "%d,%d,%.4lf\n", blanks, blockSize, elapsed);
		return best;
	}

	int CInput() {
		/*
		ifstream inp("samples.txt");
		int s;
		set<int> samples;
		while(inp >> s) samples.insert(s);
		*/

		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc) {
			int blockH, blockW;
			cin >> boardH >> boardW >> blockH >> blockW;
			board.resize(boardH);
			vector<string> block(blockH);

			for (int i = 0; i < boardH; i++)
				cin >> board[i];
			for (int i = 0; i < blockH; i++)
				cin >> block[i];
			/*
			if(samples.count(cc)) {
			fprintf(stderr, "%d %d %d %d\n", boardH, boardW, blockH, blockW);
			for(int i = 0; i < boardH; i++)
			fprintf(stderr, "%s\n", board[i].c_str());
			for(int i = 0; i < blockH; i++)
			fprintf(stderr, "%s\n", block[i].c_str());
			}*/

			generateRotations(block);
			cout << solve() << endl;
		}
	}
};