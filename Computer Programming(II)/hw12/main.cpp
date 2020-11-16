#include <iostream>
#include "book.h"
using namespace std;

int main()
{
	book user;
	cout << "Taiwan High Speed Rail Booking System\n";

	while (1) {
		cout << "\nEnter Your Choice\n1. Booking\n2. Booking History\n3. End Program\n? ";
		switch (user.input_num(1, 3)) {
			case 1:
				user.booking();
				break;
			case 2:
				if (user.login()) {
					cout << "\nEnter Your Choice\n1. Cancellation\n2. Reduce\n3. End\n? ";
					switch (user.input_num(1, 3)) {
						cout << endl;
						case 1:
							user.cancellation();
							break;
						case 2:
							user.reduce();
							break;
						case 3:
							break;
					}
				}
				break;
			case 3:
				cout << "\nThank you. Goodbye.\n\n";
				return 0;
		}
	}

	return 0;
}