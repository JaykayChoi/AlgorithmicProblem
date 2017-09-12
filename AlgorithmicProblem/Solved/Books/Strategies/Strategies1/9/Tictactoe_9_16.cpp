#include "Utils.h"
using namespace std;
using namespace Utils;

//����
//
//ƽ����� 3x3 ũ���� �����ǿ��� �ϴ� 3�� �����Դϴ�.�� ���� �����ư��� o�� x�� �������� �� ĭ�� ����, ���� ���� ���ڸ� ����, ���� Ȥ�� �밢������ 3�� ���̵��� �ϴ� ���� �̱�ϴ�.���� ���, ���� �������� x�� �̱� �������Դϴ�.
//
//xoo
//.x.
//..x
//������ �׻� x���� �����մϴ�.
//
//ƽ���� �������� ���� ���°� �־����ϴ�.�� ��� ��� �ּ��� ���Ѵٰ� ������ ��, ������� �̱��� �Ǵ��ϴ� ���α׷��� �ۼ��ϼ���.
//
//�Է�
//
//�Է��� ù �ٿ��� �׽�Ʈ ���̽��� �� C(<= 50)�� �־����ϴ�.�� �׽�Ʈ ���̽��� �� �ٿ� �� �� ���ڷ� �������� �� ��ġ�� ���� ���ڰ� �־����ϴ�.���ڰ� ���� ĭ�� ��ħǥ(.)�� ǥ���մϴ�.
//
//���
//
//�� �׽�Ʈ ���̽����� �� ���� ����մϴ�.�� ����� ��� �ּ��� ���� ��� ���ٸ� TIE��, �ƴ� ��� �̱�� ����� ���ڸ� ����մϴ�.
//
//���� �Է�
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
//���� ���
//
//TIE
//x
//o

class Tictactoe_9_16
{
public:

private:
#pragma region answer
	// turn �� �� ���� ����������� ��ȯ�Ѵ�
	bool isFinished(const vector<string>& board, char turn) {
		return false;
	}


	// ƽ���� �������� �־��� �� [0,19682] ������ ������ ��ȯ�Ѵ�
	int bijection(const vector<string>& board) {
		int ret = 0;
		for (int y = 0; y < 3; ++y)
			for (int x = 0; x < 3; x++) {
				ret = ret * 3;	//3����.
				if (board[y][x] == 'o') ++ret;
				else if (board[y][x] == 'x') ret += 2;
			}
		return ret;
	}

	// cache[] �� -2 �� �ʱ�ȭ�Ѵ�
	int cache[19683];

	// ���� �̱� �� ������ 1 ��, ��� �� ������ 0 ��, ���� -1 �� �����Ѵ�
	int canWin(vector<string>& board, char turn) {
		// ���� ���: �������� ��밡 �ּ� ������ ������� ���
		if (isFinished(board, 'o' + 'x' - turn)) return -1;
		int& ret = cache[bijection(board)];
		if (ret != -2) return ret;
		// �� ��ȯ�� �� ��밡 �̱�� ��� (1) ���� ���� ��� (0),
		// ���� ������� ��밡 ���� ��� (-1)�� ���Ѵ�:
		// ��� ��ȯ���� min �� ������
		int minValue = 2;
		for (int y = 0; y < 3; ++y)
			for (int x = 0; x < 3; ++x) {
				if (board[y][x] == '.') {
					board[y][x] = turn;
					minValue = min(minValue, canWin(board, 'o' + 'x' - turn));
					board[y][x] = '.';
				}
			}
		// �÷����Ҽ� ���ų�, ��� �ص� ���� ���� �ּ��� ���
		if (minValue == 2 || minValue == 0) return ret = 0;
		// �ּ��� ��밡 �̱�� �Ŷ�� �� ������ ����, ��밡 ���� �Ŷ�� �� �̱��
		return ret = -minValue;
	}
#pragma endregion

};