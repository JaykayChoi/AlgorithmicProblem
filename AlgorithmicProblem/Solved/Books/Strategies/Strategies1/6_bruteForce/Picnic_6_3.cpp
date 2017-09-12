#include<cassert>
#include<vector>
#include<iostream>
#include<cstring>
# include <algorithm>
# include <fstream>
#include <iterator>
#include <string>

using namespace std;
using std::ifstream;
using std::istream_iterator;

//����
//
//�ȵ�θ޴� ��ġ�� �ͽ��������ݿ����� ���� �ֿ� ������������ ��ǳ�� ���ϴ�.���� �������� ��ǳ �� �л����� �� �� ¦�� ���� �ൿ�ϰ� �Ϸ��� �մϴ�.�׷��� ���� ģ���� �ƴ� �л��鳢�� ¦�� ���� �ָ� ���� �ο�ų� ���� ���ƴٴ��� �ʱ� ������, �׻� ���� ģ���� �л��鳢���� ¦�� ���� ��� �մϴ�.
//
//�� �л����� �ֿ� ���� �̵��� ���� ģ������ ���ΰ� �־��� ��, �л����� ¦������ �� �ִ� ����� ���� ����ϴ� ���α׷��� �ۼ��ϼ���.¦�� �Ǵ� �л����� �Ϻθ� �ٸ����� �ٸ� ����̶�� ���ϴ�.���� ��� ���� �� ���� ����� ���� �ٸ� ����Դϴ�.
//
//(�¿�, ����ī) (���, Ƽ�Ĵ�) (ȿ��, ����)
//(�¿�, ����ī) (���, ����) (ȿ��, Ƽ�Ĵ�)
//�Է�
//
//�Է��� ù �ٿ��� �׽�Ʈ ���̽��� �� C(C <= 50) �� �־����ϴ�.�� �׽�Ʈ ���̽��� ù �ٿ��� �л��� �� n(2 <= n <= 10) �� ģ�� ���� �� m(0 <= m <= n*(n - 1) / 2) �� �־����ϴ�.�� ���� �ٿ� m ���� ���� ������ ���� ģ���� �� �л��� ��ȣ�� �־����ϴ�.��ȣ�� ��� 0 ���� n - 1 ������ �����̰�, ���� ���� �Է¿� �� �� �־����� �ʽ��ϴ�.�л����� ���� ¦���Դϴ�.
//
//���
//
//�� �׽�Ʈ ���̽����� �� �ٿ� ��� �л��� ģ�������� ¦������ �� �ִ� ����� ���� ����մϴ�.
//
//���� �Է�
//
//3
//2 1
//0 1
//4 6
//0 1 1 2 2 3 3 0 0 2 1 3
//6 10
//0 1 0 2 1 2 1 3 1 4 2 3 2 4 3 4 3 5 4 5
//���� ���
//
//1
//3
//4
class Picnic_6_3
{
public:
	int n, m;
	bool areFriends[10][10];

	int countPairings(bool taken[10]) {
		// ���� �л��� �� ���� ��ȣ�� ���� �л��� ã�´� (�ߺ��� ���� ���ϰ� �ٸ� ���� ���� ���� �ʱ� ���� ���� �� �߿��� ���������� ���� ���� ���� �� �ϳ����� ���� ���� ���)
		int firstFree = -1;
		for (int i = 0; i < (n); i++) {
			if (!taken[i]) {
				firstFree = i;
				break;
			}
		}
		// ���� ���: ��� �л��� ¦�� ã������ �� ���� ����� ã������ �����Ѵ�.
		if (firstFree == -1) return 1;
		int ret = 0;
		for (int pairWith = (firstFree + 1); pairWith < (n); pairWith++) {
			if (!taken[pairWith] && areFriends[firstFree][pairWith]) {
				taken[firstFree] = taken[pairWith] = true;
				ret += countPairings(taken);
				taken[firstFree] = taken[pairWith] = false;
			}
		}
		return ret;
	}

	int sub_main()
	{
		ifstream fin("Picnic_6_3_Input.txt");
		int cases;
		fin >> cases;
		while (cases--) {
			fin >> n >> m;
			assert(n <= 10);
			memset(areFriends, 0, sizeof(areFriends));
			for (int i = 0; i < (m); i++) {
				int a, b;
				fin >> a >> b;
				assert(0 <= a && a < n && 0 <= b && b < n);
				assert(!areFriends[a][b]);
				areFriends[a][b] = areFriends[b][a] = true;
			}
			bool taken[10];
			memset(taken, 0, sizeof(taken));
			cout << countPairings(taken) << endl;
		}
		return 0;
	}

};