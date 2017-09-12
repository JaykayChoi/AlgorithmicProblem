#include "Utils.h"
using namespace std;
using namespace Utils;

//문제
//
//틱택토는 3x3 크기의 게임판에서 하는 3목 게임입니다.두 명이 번갈아가며 o와 x를 게임판의 빈 칸에 쓰되, 먼저 같은 글자를 가로, 세로 혹은 대각선으로 3개 쓰이도록 하는 쪽이 이깁니다.예를 들어, 다음 게임판은 x가 이긴 게임판입니다.
//
//xoo
//.x.
//..x
//게임은 항상 x부터 시작합니다.
//
//틱택토 게임판의 현재 상태가 주어집니다.두 사람 모두 최선을 다한다고 가정할 때, 어느쪽이 이길지 판단하는 프로그램을 작성하세요.
//
//입력
//
//입력의 첫 줄에는 테스트 케이스의 수 C(<= 50)가 주어집니다.각 테스트 케이스는 세 줄에 각 세 글자로 게임판의 각 위치에 쓰인 글자가 주어집니다.글자가 없는 칸은 마침표(.)로 표현합니다.
//
//출력
//
//각 테스트 케이스마다 한 줄을 출력합니다.두 사람이 모두 최선을 다할 경우 비긴다면 TIE를, 아닌 경우 이기는 사람의 글자를 출력합니다.
//
//예제 입력
//
//3
//...
//...
//...
//xx.
//oo.
//...
//xox
//oo.
//x.x
//예제 출력
//
//TIE
//x
//o

class Tictactoe_9_16
{
public:

private:
#pragma region answer
	// turn 이 한 줄을 만들었는지를 반환한다
	bool isFinished(const vector<string>& board, char turn) {
		return false;
	}


	// 틱택토 게임판이 주어질 때 [0,19682] 범위의 정수로 변환한다
	int bijection(const vector<string>& board) {
		int ret = 0;
		for (int y = 0; y < 3; ++y)
			for (int x = 0; x < 3; x++) {
				ret = ret * 3;	//3진수.
				if (board[y][x] == 'o') ++ret;
				else if (board[y][x] == 'x') ret += 2;
			}
		return ret;
	}

	// cache[] 는 -2 로 초기화한다
	int cache[19683];

	// 내가 이길 수 있으면 1 을, 비길 수 있으면 0 을, 지면 -1 을 리턴한다
	int canWin(vector<string>& board, char turn) {
		// 기저 사례: 마지막에 상대가 둬서 한줄이 만들어진 경우
		if (isFinished(board, 'o' + 'x' - turn)) return -1;
		int& ret = cache[bijection(board)];
		if (ret != -2) return ret;
		// 각 반환값 중 상대가 이기는 결과 (1) 보다 비기는 결과 (0),
		// 비기는 결과보다 상대가 지는 결과 (-1)를 원한다:
		// 모든 반환값의 min 을 취하자
		int minValue = 2;
		for (int y = 0; y < 3; ++y)
			for (int x = 0; x < 3; ++x) {
				if (board[y][x] == '.') {
					board[y][x] = turn;
					minValue = min(minValue, canWin(board, 'o' + 'x' - turn));
					board[y][x] = '.';
				}
			}
		// 플레이할수 없거나, 어떻게 해도 비기는 것이 최선인 경우
		if (minValue == 2 || minValue == 0) return ret = 0;
		// 최선이 상대가 이기는 거라면 난 무조건 지고, 상대가 지는 거라면 난 이긴다
		return ret = -minValue;
	}
#pragma endregion

};