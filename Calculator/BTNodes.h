#include <iostream>
#include <exception>

using namespace std;

template<typename T>
class node
{
public:
	node() {}
	node(T e) { element = e; }
	node(node<T>* p) { parent = p; }
	bool isInternal() { return numChildren; }
	bool isExternal() { return !numChildren; }
	node<T>* parent = nullptr;
	T element = "";
	node<T>* left = nullptr;
	node<T>* right = nullptr;
	int numChildren = 0;

};