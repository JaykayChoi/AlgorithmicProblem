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

class Tree_21_2
{
public:

private:
	struct TreeNode {
		string label; // ������ �ڷ�
		TreeNode* parent; // �θ� ��带 ����Ű�� ������
		vector<TreeNode*> children; // �ڼ� ������ ����Ű�� �������� �迭
	};

	// �־��� Ʈ���� �� ��忡 ����� ������ ��� ����Ѵ�
	void printLabels(TreeNode* root) {
		// ��Ʈ�� ����� ������ ����Ѵ�
		cout << root->label << endl;
		// �� �ڼյ��� ��Ʈ�� �ϴ� ����Ʈ���� ��������� ����Ѵ�
		for (int i = 0; i < root->children.size(); ++i)
			printLabels(root->children[i]);
	}

	// root �� ��Ʈ�� �ϴ� Ʈ���� ���̸� ���Ѵ�
	int height(TreeNode* root) {
		int h = 0;
		for (int i = 0; i < root->children.size(); ++i)
			h = max(h, 1 + height(root->children[i]));
		return h;
	}
};