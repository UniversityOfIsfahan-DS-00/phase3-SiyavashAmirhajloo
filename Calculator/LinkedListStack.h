#include "Stack.h"

template <typename T>
class LinkedListStack : public Stack<T>
{
public:
	class Node
	{
	public:
		Node(T e) { element = e; }
		T element;
		Node* next;
	};
	LinkedListStack() : size(0) {}
	void push(T e)
	{
		Node* x = new Node(e);
		if (head == nullptr)
			tail = x;
		else
			x->next = head;
		head = x;
		size++;
	}
	T top() { return head->element; }
	T pop()
	{
		T temp;
		temp = top();
		Node* p = head;
		head = head->next;
		delete p;
		size--;
		return temp;
	}
	int Size() { return size; }
	bool isEmpty() { return !size; }
	~LinkedListStack() {}
private:
	int size;
	Node* head;
	Node* tail;
};