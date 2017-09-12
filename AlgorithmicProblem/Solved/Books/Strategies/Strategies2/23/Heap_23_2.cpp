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

//http://blog.naver.com/c_18/220026838448

class Heap_23_2
{
public:

private:
	vector<int> heap;

	// ������ ��� �ִ� �� heap �� �� ���� newValue �� �����Ѵ�
	void push_heap(vector<int>& heap, int newValue) {
		// ���� �� ���� newValue �� �����Ѵ�
		heap.push_back(newValue);
		// ���� newValue �� ��ġ
		int idx = heap.size() - 1;
		// ��Ʈ�� �����ϰų� newValue �̻��� ���Ҹ� ���� ������ ���� ������
		while (idx > 0 && heap[(idx - 1) / 2] < heap[idx]) {
			swap(heap[idx], heap[(idx - 1) / 2]);
			idx = (idx - 1) / 2;
		}
	}

	// ������ ��� �ִ� �� heap ���� heap[0] �� �����Ѵ�
	void pop_heap(vector<int>& heap) {
		// ���� �� ������ ���� ������ ��Ʈ�� ������
		heap[0] = heap.back();
		heap.pop_back();
		int here = 0;
		while (true) {
			int left = here * 2 + 1, right = here * 2 + 2;
			// ������ ������ ���
			if (left >= heap.size()) break;
			// heap[here] �� ������ ��ġ�� ã�´�
			int next = here;
			if (heap[next] < heap[left]) next = left;
			if (right < heap.size() && heap[next] < heap[right]) next = right;
			if (next == here) break;
			swap(heap[here], heap[next]);
			here = next;
		}
	}

	void CInput() {
		priority_queue<int> a;
		vector<int> b;
		for (int i = 0; i < 1000000; i++) {
			if (i % 10 > 8) {
				for (int i = 0; i < 6; i++) {
					int aa = a.top(); a.pop();
					int bb = b[0]; pop_heap(b);
					assert(aa == bb);
				}
			}
			else {
				int elem = rand() % 100000;
				a.push(elem);
				push_heap(b, elem);
			}
		}
		printf("all good.\n");
	}
};