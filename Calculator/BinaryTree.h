#include <fcntl.h>
#include <io.h>
#include "BTNodes.h"

template<typename T>
class BinaryTree
{
public:
	BinaryTree() {}
	BinaryTree(node<T>* r)
	{
		root = r; 
		size++;
	}
	bool isRoot(node<T>* p) { return p == root ? true : false; }
	bool isEmpty() { return !size; }
	int size = 0;
	node<T>* root = nullptr;
	void makeStringBinaryTree(string& pre, int& i, node<string>* temp)
	{
		string op;
		while (pre[i] != ' ' && i < pre.length()) {
			op += pre[i];
			i++;
		}
		i++;
		if (temp == nullptr) {
			node<string>* x = new node<string>(op);
			if (isEmpty()) {
				temp = x;
				root = temp;
			}
			else
				temp = x;
		}
		else
			temp->element = op;
		size++;
		if (temp->element[0] == '+' ||
			temp->element[0] == '-' &&
			temp->element.length() == 1 ||
			temp->element[0] == '*' ||
			temp->element[0] == '/' ||
			temp->element[0] == '^') {
			node<string>* xl = new node<string>(temp);
			temp->left = xl;
			makeStringBinaryTree(pre, i, temp->left);
			node<string>* xr = new node<string>(temp);
			temp->right = xr;
			makeStringBinaryTree(pre, i, temp->right);
		}
		return;
	}
	void showBinaryTree(string before, node<T>* x, bool isLeft)
	{
		if (x == nullptr) {
			return;
		}
		cout << before;
		cout << (isLeft ? "|-- " : "\\__ ");
		cout << "(" << x->element << ")" << endl;
		before += isLeft ? "|    " : "    ";
		showBinaryTree(before, x->left, true);
		showBinaryTree(before, x->right, false);
	}
};