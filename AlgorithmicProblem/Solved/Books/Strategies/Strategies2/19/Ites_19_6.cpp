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

//https://algospot.com/judge/problem/read/ITES

class Ites_19_6
{
public:
	void Solve()
	{
		Input();
	}
private:
	void Input()
	{
		string filePath = "Ites_19_6_Input.txt";
		queue<string> inputs = GetLine_InputFileAsQueue(filePath);

		int problems = stoi(Dequeue(inputs));

		REP(i, problems)
		{
			vector<int> kn = SplitStringToInt(Dequeue(inputs));
			cout << countRanges(kn[0], kn[1]) << endl;
		}
	}

	//�޸𸮿� ��� ���ڸ� ������ �� ���ٴ� ���� ������ ������ ���� ������ �˰���
	int simple(const vector<int>& signals, int k)
	{
		int ret = 0;
		REP(head, signals.sz)
		{
			int sum = 0;
			for (int tail = head; head < signals.sz; tail++)
			{
				sum += signals[tail];
				if (sum == k)
					ret++;
				if (sum >= k)
					break;
			}
		}
	}

	//�������� ����ȭ�� �˰���
	int optimized(const vector<int>& signals, int k)
	{
		int ret = 0, tail = 0, rangeSum = signals[0];
		REP(head, signals.sz)
		{
			//rangeSum�� k �̻��� ������ ������ ���� ������ tail�� �ű��
			while (rangeSum < k && tail +1 < signals.sz)
			{
				rangeSum += signals[++tail];
			}

			if (rangeSum == k)
				ret++;

			//signals[head]�� ���� �������� ������
			rangeSum -= signals[head];
		}
		return ret;
	}

	//���� �յ� ���� ������ (linear congruential random number generator)
	struct RNG 
	{
		unsigned seed;
		RNG() : seed(1983) {}

		unsigned next() 
		{
			unsigned ret = seed;
			seed = ((seed * 214013u) + 2531011u);
			return ret % 10000 + 1;
		}
	};

	//�¶��� �˰���
	int countRanges(int k, int n)
	{
		RNG rng;	//��ȣ���� �����ϴ� ���� ������
		queue<int> range;	//���� ������ ��� �ִ� ���ڵ��� �����ϴ� ť
		int ret = 0, rangeSum = 0;
		REP(i, n)
		{
			//������ ���ڸ� �߰�
			int newSignal = rng.next();
			rangeSum += newSignal;
			range.push(newSignal);

			//������ ���� k�� �ʰ��ϴ� ���� �������� ���ڸ� ����
			while (rangeSum > k)
			{
				rangeSum -= range.front();
				range.pop();
			}

			if (rangeSum == k)
				ret++;
		}
		return ret;
	}
};