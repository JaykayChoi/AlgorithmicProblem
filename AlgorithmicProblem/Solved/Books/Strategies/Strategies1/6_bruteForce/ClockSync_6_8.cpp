#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//2
//12 6 6 6 6 6 12 12 12 12 12 12 12 12 12 12
//12 9 3 12 6 6 9 3 12 9 12 9 12 12 6 6

//https://algospot.com/judge/problem/read/CLOCKSYNC

const int INF = 9999, SWITCHES = 10, CLOCKS = 16;

class ClockSync_6_8
{
public:
	void Solve()
	{
		int cases;
		cin >> cases;
		for (int cc = 0; cc < (cases); cc++) {
			vector<int> clocks(16, 0);
			for (int i = 0; i < (16); i++)
				cin >> clocks[i];
			int ret = solve(clocks, 0);
			cout << (ret >= INF ? -1 : ret) << endl;

		}
	}
private:
	//linked[i][j] = 'x': i�� ����ġ�� j�� �ð谡 ����Ǿ� �ִ�
	//linked[i][j] = '.': i�� ����ġ�� j�� �ð谡 ����Ǿ� ���� �ʴ�.
	const char linked[SWITCHES][CLOCKS + 1] = {
		// 0123456789012345
		"xxx.............",
		"...x...x.x.x....",
		"....x.....x...xx",
		"x...xxxx........",
		"......xxx.x.x...",
		"x.x...........xx",
		"...x..........xx",
		"....xx.x......xx",
		".xxxxx..........",
		"...xxx...x...x.." };

	//��� �ð谡 12�ø� ����Ű�� �ִ��� Ȯ���Ѵ�.
	bool areAligned(const vector<int>& clocks) {
		for (int i = 0; i < CLOCKS; i++)
			if (clocks[i] % 4 != 0) return false;
		return true;
	}

	//swtch�� ����ġ�� ������.
	void push(vector<int>& clocks, int swtch) {
		for (int clock = 0; clock < CLOCKS; ++clock)
			if (linked[swtch][clock] == 'x')
				clocks[clock] += 3;
	}

	//clocks: ���� �ð���� ����
	//swtch: �̹��� ���� ����ġ�� ��ȣ
	//�� �־��� ��, ���� ����ġ���� ������ clcks�� 12�÷� ���� �� �ִ� �ּ� Ƚ���� ��ȯ
	//���� �Ұ����ϴٸ� INF �̻��� ū ���� ��ȯ.
	int solve(vector<int>& clocks, int swtch) {
		if (swtch == SWITCHES) return areAligned(clocks) ? 0 : INF;
		//�� ����ġ�� 0�� ������ ������ �� �� ������ �������� ��� �õ�.
		int ret = INF;
		for (int cnt = 0; cnt < 4; ++cnt) {
			ret = min(ret, cnt + solve(clocks, swtch + 1));
			push(clocks, swtch);
		}
		//push(clocks,swtch)�� �� �� ȣ��Ǿ����� clocks�� ������ ���� ���°� �ȴ�.
		return ret;
	}

};