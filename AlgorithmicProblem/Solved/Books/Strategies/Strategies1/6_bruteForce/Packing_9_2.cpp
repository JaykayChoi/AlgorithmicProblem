#include "Utils.h"
using namespace std;
using namespace Utils;

//����
//
//������ ������ �������� ���� ���� ���� �ʴ� ������ �ִ� �����̴� ���õ� ����� Ÿ�� �������� ������ �α� ���� �ڸ��� �ɾҽ��ϴ�.����� ������ �����̴� ĳ��� �ϳ��� ������ �� �� �ִµ�, �ƹ����� �������� ���� ���ǵ��� ĳ���� �ȿ� �� ���� ���� �� �����ϴ�.�����̴� �������� ���� �� ���ǵ��� ���ǿ� �󸶳� �ʿ������� ��Ÿ���� ���ڵ��� ������ ������ ���� ����� ��������ϴ�.
//
//����	��Ʈ�� ��ǻ��	ī�޶�	XBOX365	Ŀ�Ǳ׶��δ�	�Ʒ�	�������
//����	4	2	6	4	2	10
//���ڵ�	7	10	6	7	5	4
//ĳ������ �뷮�� ������ �ֱ� ������ ������ �� �ִ� ���ǵ��� ���� ���� ĳ������ �뷮 w ���Ͽ��� �մϴ�.�̶� ���ڵ��� �ִ�ȭ�� �� �ִ� ���ǵ��� ����� ����ϴ� ���α׷��� �ۼ��ϼ���.
//
//�Է�
//
//�Է��� ù �ٿ��� �׽�Ʈ ���̽��� �� C(1��C��50)�� �־����ϴ�.�� �׽�Ʈ ���̽��� ù �ٿ��� �������� ���� ������ �� N(1��N��100)�� ĳ������ �뷮 W(1��W��1000)�� �־����ϴ�.�� ���� N�ٿ� ������� �� ������ ������ �־����ϴ�.�� ���ǿ� ���� ������ ������ �̸�, ����, ���ڵ� ������� �־�����, �̸��� ���� ���� ���ĺ� ��ҹ��� 1���� �̻� 20���� ������ ���ڿ�, ���ǿ� ���ڵ��� 1000 ������ �ڿ����Դϴ�.
//
//���
//
//�� �׽�Ʈ ���̽��� ����� ù �ٿ��� ������ �� �ִ� ���ǵ��� �ִ� ���ڵ� �հ� ������ ���ǵ��� ������ ����մϴ�.���� �� �ٿ� �ϳ��� �� ���ǵ��� �̸��� ����մϴ�.���� ���ڵ��� �ִ�ȭ�ϴ� ���ǵ��� ������ ������ ��� �ƹ� ���̳� ����ص� �����ϴ�.
//
//���� �Է�
//
//2
//6 10
//laptop 4 7
//camera 2 10
//xbox 6 6
//grinder 4 7
//dumbell 2 5
//encyclopedia 10 4
//6 17
//laptop 4 7
//camera 2 10
//xbox 6 6
//grinder 4 7
//dumbell 2 5
//encyclopedia 10 4
//���� ���
//
//24 3
//laptop
//camera
//grinder
//30 4
//laptop
//camera
//xbox
//grinder

class Packing_9_2
{
public:


private:

	//my soling
	int n;
	int w;
	string _items[100] = { "" };
	int volumes[100] = { 0 };
	int prioritys[100] = { 0 };
	void Input()
	{
		string filePath = "Packing_9_2_Input.txt";
		queue<string> vInputLines = GetLine_InputFileAsQueue(filePath);

		int numPloblems = stoi(Dequeue(vInputLines));

		for (int i = 0; i < numPloblems; i++)
		{
			string d = " ";
			vector<int> nw = SplitStringToInt(Dequeue(vInputLines), d);
			n = nw[0];
			w = nw[1];

			for (int j = 0; j < n; j++)
			{
				vector<string> item = StringSplit(Dequeue(vInputLines), d);
				_items[j] = item[0];
				volumes[j] = stoi(item[1]);
				prioritys[j] = stoi(item[2]);


			}
		}
	}

	void Pack()
	{
		
	}
	// /my solving




	int items, capacity;
	int volume[100], need[100];
	int cache[1001][100];
	string name[100];

	// ĳ��� ���� �뷮�� capacity �� ��, item ������ ���ǵ��� ��� ���� �� �ִ� �ִ�
	// ���ڵ��� ���� ��ȯ�Ѵ�
	int pack(int capacity, int item) {
		// ���� ���: �� ���� ������ ���� ��
		if (item == items) return 0;
		// �޸������̼�
		int& ret = cache[capacity][item];
		if (ret != -1) return ret;
		// �� ������ ���� ���� ���
		ret = pack(capacity, item + 1);
		// �� ������ ���� ���
		if (capacity >= volume[item])
			ret = max(ret, pack(capacity - volume[item], item + 1) + need[item]);
		return ret;
	}

	// pack(capacity, item) �� ������ ���ǵ��� ����� picked �� �����Ѵ�
	void reconstruct(int capacity, int item, vector<string>& picked) {
		if (item == items) return;
		if (pack(capacity, item) == pack(capacity, item + 1))
			reconstruct(capacity, item + 1, picked);
		else {
			picked.push_back(name[item]);
			reconstruct(capacity - volume[item], item + 1, picked);
		}
	}

	int greedy() {
		vector<pair<double, int> > order;
		for (int i = 0; i < items; i++) {
			order.push_back(make_pair(-need[i] / double(volume[i]), i));
		}
		sort(order.begin(), order.end());
		int cap = capacity;
		int val = 0;
		vector<string> chosen;
		for (int i = 0; i < items; i++) {
			int idx = order[i].second;
			if (volume[idx] <= cap) {
				// fprintf(stderr, "Greedy adding #%d: %s (%g)\n", i, name[idx].c_str(), order[i].first);
				cap -= volume[idx];
				val += need[idx];
				chosen.push_back(name[idx]);
			}
		}
		printf("%d %d\n", val, chosen.size());
		for (int i = 0; i < chosen.size(); ++i)
			printf("%s\n", chosen[i].c_str());
		return val;
	}

	int CInput() 
	{
		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc) {
			cin >> items >> capacity;
			for (int i = 0; i < items; i++) {
				cin >> name[i] >> volume[i] >> need[i];
			}
			memset(cache, -1, sizeof(cache));

			vector<string> picked;
			reconstruct(capacity, 0, picked);
			printf("%d %d\n", pack(capacity, 0), int(picked.size()));
			for (int i = 0; i < picked.size(); ++i)
				printf("%s\n", picked[i].c_str());
			//
			// int grdy = greedy();
			// if(pack(capacity, 0) != grdy) fprintf(stderr, "greedy fails: return %d\n", grdy);
		}
	}
};