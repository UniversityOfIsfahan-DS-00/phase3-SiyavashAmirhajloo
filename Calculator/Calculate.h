#include <stdexcept>
#include <string>
#include "LinkedListStack.h"

class Calculate
{
public:
	Calculate(string);
	void process(string);
	string toPostfix(string);
	string toInfix(string);
	bool checkCorrect(string);
	void deleteSpaces(string&);
	bool isOperator(char);
	bool isOperand(char);
	bool eqlOrHigher(char, char);
	void afterPlusOrMinus(string&, int);
	double sum(double a, double b) { return a + b; }
	double subtraction(double a, double b) { return a - b; }
	double product(double a, double b) { return a * b; }
	double division(double a, double b) { return a / b; }
	double exponentiation(double a, double b) { return pow(a, b); }
};