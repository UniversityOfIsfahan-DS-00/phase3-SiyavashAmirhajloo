#include "Calculate.h"

int main()
{
	string a;
	bool c = true;
	while (c) {
		try {
			getline(cin, a);
			Calculate x(a);
			cout << "\nEnter a character for new or 0 for exit.\n";
			char temp;
			cin >> temp;
			cin.ignore();
			if (temp != '0') {
				system("cls");
				c = true;
			}
			else
				c = false;
		}
		catch (logic_error ex) {
			cout << ex.what();
			c = true;
		}
	}
	return 0;
}