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

typedef int KeyType;


class Treap_22_6
{
public:
	void Solve()
	{
		Input();
	}
private:
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

	void print(Node* node, int indent = 0) {
		if (indent == 0) printf("====================\n");
		for (int i = 0; i < indent; i++) printf(" ");
		printf("=>");
		if (node == NULL) { printf("\n"); return; }
		printf("Node(key=%d, priority=%d, size=%d)\n", node->key, node->priority, node->size);
		print(node->left, indent + 4);
		print(node->right, indent + 4);

	}

	void randomTest() {
		set<int> a;
		Node* b = NULL;
		srand(12378);
		const int ITER = 10000000;
		for (int i = 0; i < ITER; i++) {
			int num = rand() % 10000;
			int op = rand() % 4;
			if (op == 0) {
				bool ae = a.count(num) > 0;
				bool be = exists(b, num);
				if (ae != be) {
					printf("a \n");
					//for (typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
					for (set<int>::iterator it = a.begin(); it != a.end(); ++it)
						printf("%d ", *it);
					printf("\n");
					print(b);

				}
				assert(ae == be);
			}
			else if (op == 1) {
				bool ae = a.count(num) > 0;
				if (ae) {
					a.erase(num);
					b = erase(b, num);
				}
				else {
					a.insert(num);
					b = insert(b, new Node(num));
				}
			}
			else if (op == 2) {
				set<int>::iterator it = a.lower_bound(num);
				Node* jt = lowerBound(b, num);
				if (it == a.end())
					assert(jt == NULL);
				else
					assert(*it == jt->key);
			}
			else {
				int k = rand() % a.size() + 1;
				int skip = k, ak = 0;
				//for (typeof(a.begin()) it = a.begin(); it != a.end(); ++it) 
				for (set<int>::iterator it = a.begin(); it != a.end(); ++it)
				{
					if (--skip == 0) {
						ak = *it;
						break;
					}
				}
				if (ak != kth(b, k)->key) {

					printf("a \n");
					//for (typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
					for (set<int>::iterator it = a.begin(); it != a.end(); ++it)
						printf("%d ", *it);
					printf("\n");
					print(b);
					printf("k = %d, ak = %d, kth = %d\n", k, ak, kth(b, k)->key);
					assert(false);
				}
				assert(countLessThan(b, ak) == k - 1);
			}
		}
	}

	void Input() {
		Node* root = NULL;
		const int arr[10] = { 5, 7, 6, 9, 2, 3, 10, 12, 4 };
		for (int i = 0; i < 10; i++) {
			root = insert(root, new Node(arr[i]));
			print(root);
		}
		for (int i = 0; i < 10; ++i) {
			assert(lowerBound(root, arr[i])->key == arr[i]);
		}
		assert(lowerBound(root, 1)->key == 2);
		assert(lowerBound(root, 8)->key == 9);
		assert(lowerBound(root, 11)->key == 12);
		assert(lowerBound(root, 13) == NULL);
		root = erase(root, 5);
		print(root);
		root = erase(root, 2);
		print(root);
		root = erase(root, 10);
		print(root);
		assert(lowerBound(root, 5)->key == 6);
		assert(lowerBound(root, 2)->key == 3);
		assert(lowerBound(root, 10)->key == 12);

		randomTest();

		printf("all good.\n");
	}
};
