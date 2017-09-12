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

//https://algospot.com/judge/problem/read/RUNNINGMEDIAN

class RunningMedian_23_3
{
public:

private:
	struct RNG {
		int seed, a, b;
		RNG(int _a, int _b) : a(_a), b(_b), seed(1983) {}
		int next() {
			int ret = seed;
			seed = ((seed * (long long)a) + b) % 20090711;
			return ret;
		}
	};

	typedef int KeyType;
	// Ʈ���� �� ��带 �����Ѵ�
	struct Node {
		// ��忡 ����� Ű
		KeyType key;
		// �� ����� �켱���� (priority)
		// �� ��带 ��Ʈ�� �ϴ� ����Ʈ���� ũ�� (size)
		int priority, size;
		// �� �ڽ� ����� ������
		Node *left, *right;

		// �����ڿ��� ���� �켱������ �����ϰ�, size �� left/right �� �ʱ�ȭ�Ѵ�
		Node(const KeyType& _key) : key(_key), priority(rand()),
			size(1), left(NULL), right(NULL) {
		}
		void setLeft(Node* newLeft) { left = newLeft; calcSize(); }
		void setRight(Node* newRight) { right = newRight; calcSize(); }
		// size ����� �����Ѵ�
		void calcSize() {
			size = 1;
			if (left) size += left->size;
			if (right) size += right->size;
		}
	};

	// key �̻��� �� �� ���� ���� ���� ��ġ�� ��ȯ�Ѵ�
	Node* lowerBound(Node* root, KeyType key) {
		if (root == NULL) return NULL;
		if (root->key < key) return lowerBound(root->right, key);
		Node* ret = lowerBound(root->left, key);
		if (!ret) ret = root;
		return ret;
	}

	bool exists(Node* root, KeyType key) {
		Node* node = lowerBound(root, key);
		return node != NULL && node->key == key;
	}

	// root �� ��Ʈ�� �ϴ� Ʈ�� �߿��� k��° ���Ҹ� ��ȯ�Ѵ�
	Node* kth(Node* root, int k) {
		int ls = (root->left ? root->left->size : 0);
		int rs = (root->right ? root->right->size : 0);
		if (k <= ls) return kth(root->left, k);
		if (k == ls + 1) return root;
		return kth(root->right, k - ls - 1);
	}

	// key ���� ���� Ű���� ���� ��ȯ�Ѵ�
	int countLessThan(Node* root, KeyType key) {
		if (root == NULL) return 0;
		if (root->key >= key)
			return countLessThan(root->left, key);
		int ls = (root->left ? root->left->size : 0);
		return ls + 1 + countLessThan(root->right, key);
	}

	typedef pair<Node*, Node*> NodePair;

	// root �� ��Ʈ�� �ϴ� Ʈ���� key �̸��� ���� �̻��� ���� ����
	// �� ���� Ʈ������ �и��Ѵ�.
	NodePair split(Node* root, KeyType key) {
		if (root == NULL) return NodePair(NULL, NULL);
		// ��Ʈ�� key �̸��̸� �������� �Ϻθ� �߶󳽴�
		if (root->key < key) {
			NodePair rs = split(root->right, key);
			root->setRight(rs.first);
			return NodePair(root, rs.second);
		}
		// ��Ʈ�� key �̻��̸� ������ �Ϻθ� �߶󳽴�
		NodePair ls = split(root->left, key);
		root->setLeft(ls.second);
		return NodePair(ls.first, root);
	}

	// root �� ��Ʈ�� �ϴ� Ʈ���� �� ��� node �� ������ �� ��� Ʈ����
	// ��Ʈ�� ��ȯ�Ѵ�.
	Node* insert(Node* root, Node* node) {
		if (root == NULL) return node;
		// node �� ��Ʈ�� ��ü�ؾ� �Ѵ�: �ش� ����Ʈ���� ������ �߶�
		// ���� �ڼ����� �Ѵ�
		if (root->priority < node->priority) {
			NodePair splitted = split(root, node->key);
			node->setLeft(splitted.first);
			node->setRight(splitted.second);
			return node;
		}
		else if (node->key < root->key)
			root->setLeft(insert(root->left, node));
		else
			root->setRight(insert(root->right, node));
		return root;
	}

	// a �� b �� �� ���� Ʈ���̰�, max(a) < min(b) �϶� �� ���� ��ģ��
	Node* merge(Node* a, Node* b) {
		if (a == NULL) return b;
		if (b == NULL) return a;

		if (a->priority < b->priority) {
			b->setLeft(merge(a, b->left));
			return b;
		}
		a->setRight(merge(a->right, b));
		return a;
	}

	// root �� ��Ʈ�� �ϴ� Ʈ������ key �� �����
	Node* erase(Node* root, KeyType key) {
		if (root == NULL) return root;
		// root �� ����� �� ����Ʈ���� ��ģ �� ��ȯ�Ѵ�
		if (root->key == key) {
			Node* ret = merge(root->left, root->right);
			delete root;
			return ret;
		}
		if (key < root->key)
			root->setLeft(erase(root->left, key));
		else
			root->setRight(erase(root->right, key));
		return root;
	}

	// rng �� �����ϴ� ù n���� ������ ������ �߰��ϸ� �߰����� ���Ѵ�
	int runningMedian(int n, RNG rng) {
		Node* root = NULL;
		int ret = 0;
		for (int cnt = 1; cnt <= n; ++cnt) {
			root = insert(root, new Node(rng.next()));
			int median = kth(root, (cnt + 1) / 2)->key;
			ret = (ret + median) % 20090711;
		}
		return ret;
	}

	int runningMedian2(int n, RNG rng) {
		priority_queue<int, vector<int>, less<int> > maxHeap;
		priority_queue<int, vector<int>, greater<int> > minHeap;
		int ret = 0;
		// �ݺ��� �Һ� ����:
		// 1. maxHeap �� ũ��� minHeap �� ũ��� ���ų� 1 �� ũ��
		// 2. maxHeap.top() <= minHeap.top()
		for (int cnt = 1; cnt <= n; ++cnt) {
			// �켱 1�� �Һ� ���Ǻ��� ������Ų��
			if (maxHeap.size() == minHeap.size())
				maxHeap.push(rng.next());
			else
				minHeap.push(rng.next());
			// 2�� �Һ� ������ ������ ��� ��������
			if (!minHeap.empty() && !maxHeap.empty() &&
				minHeap.top() < maxHeap.top()) {
				int a = maxHeap.top(), b = minHeap.top();
				maxHeap.pop(); minHeap.pop();
				maxHeap.push(b);
				minHeap.push(a);
			}
			ret = (ret + maxHeap.top()) % 20090711;
		}
		return ret;
	}

	void CInput() {
		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc) {
			int n;
			unsigned a, b;
			cin >> n >> a >> b;
			RNG rng1(a, b), rng2(a, b);
			{
				int a = runningMedian(n, rng1);
				int b = runningMedian2(n, rng2);
				if (a != b) {
					printf("n = %d a = %d b = %d\n", n, a, b);
				}
				assert(a == b);
				printf("%d\n", a);
			}
		}
	}
};