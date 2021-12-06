#include <iostream>

using namespace std;

template <typename T>
class Stack
{
public:
	virtual void push(T) = 0;
	virtual T top() = 0;
	virtual T pop() = 0;
	virtual int Size() = 0;
	virtual bool isEmpty() = 0;
};