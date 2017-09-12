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
	//linked[i][j] = 'x': i번 스위치와 j번 시계가 연결되어 있다
	//linked[i][j] = '.': i번 스위치와 j번 시계가 연결되어 있지 않다.
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

	//모든 시계가 12시를 가르키고 있는지 확인한다.
	bool areAligned(const vector<int>& clocks) {
		for (int i = 0; i < CLOCKS; i++)
			if (clocks[i] % 4 != 0) return false;
		return true;
	}

	//swtch번 스위치를 누른다.
	void push(vector<int>& clocks, int swtch) {
		for (int clock = 0; clock < CLOCKS; ++clock)
			if (linked[swtch][clock] == 'x')
				clocks[clock] += 3;
	}

	//clocks: 현제 시계들의 상태
	//swtch: 이번에 누를 스위치의 번호
	//가 주어질 때, 남은 스위치들을 눌러서 clcks를 12시로 맞출 수 있는 최소 횟수를 반환
	//만약 불가능하다면 INF 이상의 큰 수를 반환.
	int solve(vector<int>& clocks, int swtch) {
		if (swtch == SWITCHES) return areAligned(clocks) ? 0 : INF;
		//이 스위치를 0번 누르는 경우부터 세 번 누르는 경우까지를 모두 시도.
		int ret = INF;
		for (int cnt = 0; cnt < 4; ++cnt) {
			ret = min(ret, cnt + solve(clocks, swtch + 1));
			push(clocks, swtch);
		}
		//push(clocks,swtch)가 네 번 호출되었으니 clocks는 원래와 같은 상태가 된다.
		return ret;
	}

};