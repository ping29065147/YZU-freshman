#include <iostream>
#include "ATM.h"
using namespace std;

int main()
{
	atm user;
	user.add_menber("12345", "54321", 1000.0, 1200.0);
	user.add_menber("98765", "56789", 200.0, 200.0);

	while (1) {
		cout << "Welcome!\n\n";
		user.login();
		//user.print();

		while (1) {
			switch (user.main_menu()) {
				case '1':
					user.print_balance();
					break;
				case '2':
					user.withdraw();
					break;
				case '3':
					user.deposit();
					break;
				case '4':
					cout << "Exiting the system...\n\nThank you!Goodbye!\n\n";
					system("cls");
					goto end;
				default:
					cout << "Wrong selection. Please choice the right selection again.\n\n";
					break;
			}
		}
		end:
			continue;
	}

	return 0;
}