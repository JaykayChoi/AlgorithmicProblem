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

	//메모리에 모든 숫자를 저장할 수 없다는 제약 조건을 무시한 가장 간단한 알고리즘
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

	//오프라인 최적화된 알고리즘
	int optimized(const vector<int>& signals, int k)
	{
		int ret = 0, tail = 0, rangeSum = signals[0];
		REP(head, signals.sz)
		{
			//rangeSum이 k 이상인 최초의 구간을 만날 때까지 tail을 옮긴다
			while (rangeSum < k && tail +1 < signals.sz)
			{
				rangeSum += signals[++tail];
			}

			if (rangeSum == k)
				ret++;

			//signals[head]는 이제 구간에서 빠진다
			rangeSum -= signals[head];
		}
		return ret;
	}

	//선형 합동 난수 생성기 (linear congruential random number generator)
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

	//온라인 알고리즘
	int countRanges(int k, int n)
	{
		RNG rng;	//신호값을 생성하는 난수 생성기
		queue<int> range;	//현재 구간에 들어 있는 숫자들을 저장하는 큐
		int ret = 0, rangeSum = 0;
		REP(i, n)
		{
			//구간에 숫자를 추가
			int newSignal = rng.next();
			rangeSum += newSignal;
			range.push(newSignal);

			//구간의 합이 k를 초과하는 동안 구간에서 숫자를 뺀다
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