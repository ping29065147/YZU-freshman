#include  <iostream>
#include <string>
#include  "StackType.h"
using namespace std;

int main()
{
	unsigned int a, b;
	string data[7] = { "(x)", "x{}", "x{x[]}", "(x[x)]", "(x(x[]x", "(xx)]", "(x(((((" };

	for (a = 0; a < 7; a++) {

		StackType test;
		cout << a + 1 << "   " << data[a];

		for (b = 0; b < data[a].size(); b++) {
			try {
				if (data[a][b] == '(' || data[a][b] == '[' || data[a][b] == '{')
					test.Push(data[a][b]);   // ([{ push進去
				else if ((data[a][b] == ')' && test.Top() == '(') || (data[a][b] == ']' && test.Top() == '[') || (data[a][b] == '}' && test.Top() == '{'))
					test.Pop();  // ([{ pop出來
				else if (data[a][b] == 'x')
					continue;
				else
					break;
			}
			catch (FullStack& full) {  //例外 跳出
				cout << full.what();
				goto print;
			}
			catch (EmptyStack& empty) {  //例外 跳出
				cout << empty.what();
				goto print;
			}
		}
		if (b == data[a].size() && test.IsEmpty())
			cout << "   Well formed\n";
		else {
			print:
			cout << "   Not well formed\n";
		}
	}


	return 0;
}