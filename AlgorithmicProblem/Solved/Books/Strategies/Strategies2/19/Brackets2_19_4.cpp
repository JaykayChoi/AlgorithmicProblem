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

//https://algospot.com/judge/problem/read/BRACKETS2

class Brackets2_19_4
{
public:
	void Solve()
	{
		Input();
	}
private:
	void Input()
	{
		string filePath = "Brackets2_19_4_Input.txt";
		queue<string> inputs = GetLine_InputFileAsQueue(filePath);

		int problems = stoi(Dequeue(inputs));

		REP(i, problems)
		{
			string str = Dequeue(inputs);
			cout << wellMatched(str) << endl;
		}
	}

	bool wellMatched(const string& formula)
	{
		//���� ��ȣ ���ڵ�� �ݴ� ��ȣ ���ڵ�
		const string opening("({["), closing(")}]");

		//�̹� ���� ��ȣ���� ������� ��� ����
		stack<char> openStack;

		REP(i, formula.sz)
		{
			//���� ��ȣ���� �ݴ� ��ȣ���� Ȯ��
			if (opening.find(formula[i]) != -1)
			{
				//���� ��ȣ��� ������ ���ÿ� ����ִ´�.
				openStack.push(formula[i]);
			}
			else
			{
				//�� ���� ��� ���� �� ���� ���ڿ� ���纸��
				//������ ��� �ִ� ��쿡�� ����
				if (openStack.empty())
					return false;

				//���� ¦�� ���� �ʾƵ� ����
				if (opening.find(openStack.top()) != closing.find(formula[i]))
					return false;

				//¦�� ���� ��ȣ�� ���ÿ��� ����
				openStack.pop();
			}
		}
		return openStack.empty();
	}
};
