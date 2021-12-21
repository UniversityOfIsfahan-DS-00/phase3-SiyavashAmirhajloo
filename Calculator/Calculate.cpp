#include "Calculate.h"

Calculate::Calculate(string c)
{
	deleteSpaces(c);
	if (checkCorrect(c)) {
		string p = toPostfix(c);
		process(p);
		string preForTree = postToPre(p);
		cout << endl;
		int i = 0;
		BinaryTree<string> CBT;
		CBT.makeStringBinaryTree(preForTree, i, CBT.root);
		string temp = "";
		CBT.showBinaryTree(temp, CBT.root, false);
	}
}

void Calculate::process(string pos)
{
	LinkedListStack<string> result;
	BinaryTree<string> tree;
	double d1, d2;
	for (int i = 0; i < pos.length(); i++) {
		if (isOperand(pos[i]) || pos[i] == '-' && isOperand(pos[i + 1])) {
			string cal;
			while (pos[i] != ' ' && pos[i] != '\0') {
				cal += pos[i];
				i++;
			}
			result.push(cal);
		}
		else if (isOperator(pos[i])) {
			d2 = stod(result.top());
			result.pop();
			d1 = stod(result.top());
			result.pop();
			string temp;
			switch (pos[i]) {
			case '+':
				temp = to_string(sum(d1, d2));
				resizeString(temp);
				result.push(temp);
				break;
			case '-':
				temp = to_string(subtraction(d1, d2));
				resizeString(temp);
				result.push(temp);
				break;
			case '*':
				temp = to_string(product(d1, d2));
				resizeString(temp);
				result.push(temp);
				break;
			case '/':
				if (d2 == 0)
					throw logic_error("Undefined\n");
				temp = to_string(division(d1, d2));
				resizeString(temp);
				result.push(temp);
				break;
			case '^':
				if (d1 < 0 && d2 < 1 && d2>0)
					throw logic_error("Undefined\n");
				temp = to_string(exponentiation(d1, d2));
				resizeString(temp);
				result.push(temp);
				break;
			default:
				break;
			}
			int j = i, count = 0;
			while (count < 3) {
				if (j == 0)
					count++;
				else if (pos[j] == ' ')
					count++;
				if (count < 3)
					j--;
			}
			if (j == 0) {
				pos = pos.substr(0, j) + result.top() + pos.substr(i + 1);
				i = j + result.top().length();
			}
			else {
				pos = pos.substr(0, j) + " " + result.top() + pos.substr(i + 1);
				i = j + result.top().length(); +1;
			}
			cout << "\n--> " << toInfix(pos) << endl;
		}
	}
	if (!result.isEmpty()) {
		cout << "\nFinal: " << stod(result.top()) << endl;
		result.pop();
	}
}

string Calculate::toPostfix(string ent)
{
	string pos;
	LinkedListStack<char> s;
	s.push('(');
	ent += ')';
	for (int i = 0; i < ent.length(); i++) {
		if (ent[i] == ')') {
			if (!s.isEmpty()) {
				while (s.top() != '(') {
					pos += " ";
					pos += s.top();
					s.pop();
				}
				s.pop();
			}
		}
		if (ent[i] == '(') {
			s.push('(');
		}
		if (isOperand(ent[i]) || ent[i] == '.') {
			if (i == 0)
				pos += ent[i];
			else if (ent[i - 1] == '.' || isOperand(ent[i - 1]))
				pos += ent[i];
			else {
				if (pos.empty())
					pos += ent[i];
				else {
					pos += " ";
					pos += ent[i];
				}
			}
		}
		if (isOperator(ent[i])) {
			switch (ent[i])
			{
			case '-':
				if (i == 0) {
					if (pos.empty())
						pos += "-1";
					else
						pos += " -1";
					s.push('*');
				}
				else if (ent[i - 1] == '(') {
					if (pos.empty())
						pos += "-1";
					else
						pos += " -1";
					s.push('*');
				}
				else if (isOperator(ent[i - 1])) {
					if (pos.empty())
						pos += "-1";
					else
						pos += " -1";
					s.push('*');
				}
				else if (!s.isEmpty()) {
					while (s.top() != '(') {
						pos += " ";
						pos += s.top();
						s.pop();
					}
					s.push('-');
				}
				break;
			case '+':
				if (i == 0) {
					ent.erase(0, 1);
					i--;
				}
				else if (isOperator(ent[i - 1]) || ent[i - 1] == '(') {
					ent.erase(0, 1);
					i--;
				}
				else if (!s.isEmpty()) {
					while (s.top() != '(') {
						pos += " ";
						pos += s.top();
						s.pop();
					}
					s.push('+');
				}
				break;
			case '/':
				if (!s.isEmpty()) {
					while (s.top() != '(') {
						if (eqlOrHigher(s.top(), ent[i])) {
							pos += " ";
							pos += s.top();
							s.pop();
						}
						else
							break;
					}
					s.push('/');
				}
				break;
			case '*':
				if (!s.isEmpty()) {
					while (s.top() != '(')
						if (eqlOrHigher(s.top(), ent[i])) {
							pos += " ";
							pos += s.top();
							s.pop();
						}
						else
							break;
					s.push('*');
				}
				break;
			case '^':
				s.push('^');
				break;
			default:
				break;
			}
		}
	}
	return pos;
}

string Calculate::toInfix(string pos)
{
	LinkedListStack<string> s;
	for (int i = 0; i < pos.length(); i++) {
		if (isOperand(pos[i]) || pos[i] == '-' && isOperand(pos[i + 1])) {
			string op;
			while (pos[i] != ' ' && pos[i] != '\0') {
				op += pos[i];
				i++;
			}
			s.push(op);
		}
		else if (isOperator(pos[i])) {
			string op1 = s.top();
			s.pop();
			string op2 = s.top();
			s.pop();
			s.push("(" + op2 + pos[i] + op1 + ")");
		}
	}
	if (!s.isEmpty())
		return s.top();
	return "";
}

string Calculate::postToPre(string post)
{
	LinkedListStack<string> s;
	for (int i = 0; i < post.length(); i++) {
		if (post[i] == ' ')
			continue;
		if (isOperator(post[i]) && !isOperand(post[i + 1])) {
			string op2 = s.top();
			s.pop();
			string op1 = s.top();
			s.pop();
			string temp = "";
			temp += post[i];
			temp += (" " + op1);
			if (op1[op1.length() - 1] != ' ')
				temp += " ";
			temp += op2;
			if (op2[op2.length() - 1] != ' ')
				temp += " ";
			s.push(temp);
		}
		else {
			string op = "";
			op += post[i];
			i++;
			while (post[i] != ' ') {
				op += post[i];
				i++;
			}
			s.push(op);
		}
	}
	string pre;
	while (!s.isEmpty()) {
		pre += s.top();
		s.pop();
	}
	return pre;
}

bool Calculate::checkCorrect(string c)
{
	LinkedListStack<char> p;
	for (int i = 0; i < c.length(); i++) {
		switch (c[i]) {
		case '(':
			p.push(c[i]);
			break;
		case ')':
			if (!p.isEmpty()) {
				if (c[i - 1] == '(')
					throw logic_error("The parentheses are incorrect.\n");
				p.pop();
			}
			else
				throw logic_error("The parentheses are incorrect.\n");
			break;
		case '.':
			if (i == 0 || i == c.length() - 1)
				throw logic_error("Incorrect decimal form.\n");
			if (!isOperand(c[i - 1]) || !isOperand(c[i + 1]))
				throw logic_error("Incorrect decimal form.\n");
			int j;
			for (j = i + 1; j < c.length() && isOperand(c[j]); j++);
			if ((j == i + 1 || c[j] == '.') && j < c.length())
				throw logic_error("Incorrect decimal form.\n");
			break;
		case '+':
			afterPlusOrMinus(c, i);
			if (c[i] == '+') {
				if (!isOperand(c[i + 1]) && c[i + 1] != '(')
					throw logic_error("Operator '+' does not have operands.\n");
			}
			else
				i--;
			break;
		case '-':
			afterPlusOrMinus(c, i);
			if (c[i] == '-') {
				if (!isOperand(c[i + 1]) && c[i + 1] != '(')
					throw logic_error("Operator '-' does not have operands.\n");
			}
			else
				i--;
			break;
		case '*':
			if (i == 0)
				throw logic_error("Operator '*' does not have operands.\n");
			if (c[i - 1] != ')' && !isOperand(c[i - 1]))
				throw logic_error("Operator '*' does not have operands.\n");
			if (c[i + 1] != '+' && c[i + 1] != '-' && c[i + 1] != '(' && !isOperand(c[i + 1]))
				throw logic_error("Operator '*' does not have operands.\n");
			break;
		case '/':
			if (i == 0)
				throw logic_error("Operator '/' does not have operands.\n");
			if (c[i - 1] != ')' && !isOperand(c[i - 1]))
				throw logic_error("Operator '/' does not have operands.\n");
			if (c[i + 1] != '+' && c[i + 1] != '-' && c[i + 1] != '(' && !isOperand(c[i + 1]))
				throw logic_error("Operator '/' does not have operands.\n");
			break;
		case '^':
			if (i == 0)
				throw logic_error("Operator '^' does not have operands.\n");
			if (c[i - 1] != ')' && !isOperand(c[i - 1]))
				throw logic_error("Operator '^' does not have operands.\n");
			if (c[i + 1] != '+' && c[i + 1] != '-' && c[i + 1] != '(' && !isOperand(c[i + 1]))
				throw logic_error("Operator '^' does not have operands.\n");
			break;
		default:
			if(!isOperand(c[i]))
				throw logic_error("Illegal entry form\n");
			break;
		}
	}
	if (!p.isEmpty()) {
		throw logic_error("The parentheses are incorrect.\n");
	}
	return true;
}

void Calculate::deleteSpaces(string& ent)
{
	for (int i = 0; i < ent.length(); i++)
		if (ent[i] == ' ') {
			ent.erase(i, 1);
			i--;
		}
}

bool Calculate::isOperator(char a)
{
	if (a == '-' || a == '+' || a == '/' || a == '*' || a == '^')
		return true;
	return false;
}

bool Calculate::isOperand(char a)
{
	if (a <= '9' && a >= '0')
		return true;
	return false;
}

bool Calculate::eqlOrHigher(char a, char b)
{
	int aa = 0, bb = 0;
	if (a == '+' || a == '-')
		aa = 1;
	if (b == '+' || b == '-')
		bb = 1;
	if (a == '*' || a == '/')
		aa = 2;
	if (b == '*' || b == '/')
		bb = 2;
	return (aa >= bb) ? true : false;
}

void Calculate::afterPlusOrMinus(string& c, int i)
{
	for (int j = i + 1; j < c.length() && (c[j] == '+' || c[j] == '-'); j++) {
		if (c[j] == '+') {
			c.erase(j, 1);
			j--;
		}
		else if (c[j] == '-') {
			if (c[i] == '+') {
				c[i] = '-';
				c.erase(j, 1);
				j--;
			}
			else if (c[i] == '-') {
				c[i] = '+';
				c.erase(j, 1);
				j--;
			}
		}
	}
}

void Calculate::resizeString(string& num)
{
	while (num[num.length() - 1] != '.') {
		if (num[num.length() - 1] == '0')
			num.resize(num.length() - 1);
		else
			break;
	}
	if (num[num.length() - 1] == '.')
		num.resize(num.length() - 1);
}