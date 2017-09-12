#include "Utils.h"
using namespace std;
using namespace Utils;

//문제
//
//여행을 떠나기 전날까지 절대 짐을 싸지 않는 버릇이 있는 재훈이는 오늘도 비행기 타기 전날에야 가방을 싸기 위해 자리에 앉았습니다.비행기 규정상 재훈이는 캐리어를 하나만 가지고 갈 수 있는데, 아무래도 가져가고 싶은 물건들이 캐리어 안에 다 들어가지 않을 것 같습니다.재훈이는 가져가고 싶은 각 물건들의 부피와 얼마나 필요한지를 나타내는 절박도를 조사해 다음과 같은 목록을 만들었습니다.
//
//물건	노트북 컴퓨터	카메라	XBOX365	커피그라인더	아령	백과사전
//부피	4	2	6	4	2	10
//절박도	7	10	6	7	5	4
//캐리어의 용량이 정해져 있기 때문에 가져갈 수 있는 물건들의 부피 합은 캐리어의 용량 w 이하여야 합니다.이때 절박도를 최대화할 수 있는 물건들의 목록을 계산하는 프로그램을 작성하세요.
//
//입력
//
//입력의 첫 줄에는 테스트 케이스의 수 C(1≤C≤50)가 주어집니다.각 테스트 케이스의 첫 줄에는 가져가고 싶은 물건의 수 N(1≤N≤100)과 캐리어의 용량 W(1≤W≤1000)가 주어집니다.그 이후 N줄에 순서대로 각 물건의 정보가 주어집니다.한 물건에 대한 정보는 물건의 이름, 부피, 절박도 순서대로 주어지며, 이름은 공백 없는 알파벳 대소문자 1글자 이상 20글자 이하의 문자열, 부피와 절박도는 1000 이하의 자연수입니다.
//
//출력
//
//각 테스트 케이스별 출력의 첫 줄에는 가져갈 수 있는 물건들의 최대 절박도 합과 가져갈 물건들의 개수를 출력합니다.이후 한 줄에 하나씩 각 물건들의 이름을 출력합니다.만약 절박도를 최대화하는 물건들의 조합이 여럿일 경우 아무 것이나 출력해도 좋습니다.
//
//예제 입력
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
//예제 출력
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

	// 캐리어에 남은 용량이 capacity 일 때, item 이후의 물건들을 담아 얻을 수 있는 최대
	// 절박도의 합을 반환한다
	int pack(int capacity, int item) {
		// 기저 사례: 더 담을 물건이 없을 때
		if (item == items) return 0;
		// 메모이제이션
		int& ret = cache[capacity][item];
		if (ret != -1) return ret;
		// 이 물건을 담지 않을 경우
		ret = pack(capacity, item + 1);
		// 이 물건을 담을 경우
		if (capacity >= volume[item])
			ret = max(ret, pack(capacity - volume[item], item + 1) + need[item]);
		return ret;
	}

	// pack(capacity, item) 이 선택한 물건들의 목록을 picked 에 저장한다
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