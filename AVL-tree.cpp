#include <iostream>

using namespace std;

template <class T>
class BinaryTree {
	struct TreeNode {
		T data;
		unsigned char height;
		TreeNode* left;
		TreeNode* right;

		TreeNode() {
			height = 0;
			left = NULL;
			right = NULL;
		}

		TreeNode(T data){
			height = 1;
			this->data = data;
			left = NULL;
			right = NULL;
		}
	};
	unsigned char getHeight(TreeNode* someNode) { if (someNode) return someNode->height; else return 0; }
	short balanceF(TreeNode* someNode) {
		if ((!someNode->left) && (!someNode->right))
			return 0;
		if (!someNode->left)
			return someNode->right->height;
		if (!someNode->right)
			return someNode->left->height;
		return someNode->right->height - someNode->left->height;
	}

	void fixHeight(TreeNode* someNode) {
		if ((!someNode->left) && (!someNode->right))
			return;
		unsigned char lefth = getHeight(someNode->left);
		unsigned char righth = getHeight(someNode->right);
		if (righth > lefth)
			someNode->height = righth + 1;
		else
			someNode->height = lefth + 1;
	}

	TreeNode* rightrot(TreeNode* someNode) {
		TreeNode* newNode = someNode->left;
		someNode->left = newNode->right;
		newNode->right = someNode;
		fixHeight(someNode);
		fixHeight(newNode);
		return newNode;
	}

	TreeNode* leftrot(TreeNode* someNode) {
		TreeNode * newNode = someNode->right;
		someNode->right = newNode->left;
		newNode->left = someNode;
		fixHeight(someNode);
		fixHeight(newNode);
		return newNode;
	}

	TreeNode* balance(TreeNode* someNode) {
		fixHeight(someNode);
		if (balanceF(someNode) == 2) {
			if (balanceF(someNode->right) < 0)
				someNode->right = rightrot(someNode->right);
			return leftrot(someNode);
		}
		if (balanceF(someNode) == -2) {
			if (balanceF(someNode->left) < 0)
				someNode->left = leftrot(someNode->left);
			return rightrot(someNode);
		}
		return someNode;
	}
	TreeNode* insert(T data, TreeNode* someNode) {
		if (!someNode) {
			count++;
			return new TreeNode(data);
		}
		if (data < someNode->data)
			someNode->left = insert(data, someNode->left);
		else
			someNode->right = insert(data, someNode->right);
		return balance(someNode);
	}
	TreeNode* findmin(TreeNode* someNode) {
		TreeNode* tmp = someNode;
		while (tmp->left)
			tmp = tmp->left;
		return tmp;
	}
	TreeNode* delmin(TreeNode* someNode) {
		if (someNode->left)
			return someNode->right;
		someNode->left = delmin(someNode->left);
		return balance(someNode);
	}
	TreeNode* del(T data, TreeNode* someNode) {
		if (!someNode)
			return NULL;
		if (data < someNode->data)
			someNode->left = del(data, someNode->left);
		else if (data > someNode->data)
			someNode->right = del(data, someNode->right);
		else {
			TreeNode* right = someNode->right;
			TreeNode* left = someNode->left;
			delete someNode;
			count--;
			if (!right) return left;
			TreeNode* minim = findmin(right);
			minim->right = delmin(right);
			minim->left = left;
			return balance(minim);
		}
		return balance(someNode);
	}

	TreeNode* head;
	int count;
public:
	BinaryTree() { head = NULL; count = 0; }
	~BinaryTree() { if (head) delete head; }
	void Add(T data) { head = insert(data, head); }
	void Del(T data) { head = del(data, head); }
	bool find(T data) {
		TreeNode* tmp = head;
		while (tmp) {
			if (data < tmp->data) {
				tmp = tmp->left;
				continue;
			}
			if (data > tmp->data) {
				tmp = tmp->right;
				continue;
			}
			if (data == tmp->data)
				return 1;
		}
		return 0;
	}

	int getCount() { return count; }
};

int main() {
	BinaryTree<int> test;
	test.Add(5);
	test.Add(6);
	test.Add(4);
	cout << test.find(22) << endl;
	cout << "Count test: " << test.getCount() << endl;
	return 0;
}