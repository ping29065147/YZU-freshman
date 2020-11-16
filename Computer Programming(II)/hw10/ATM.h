#ifndef ATM_H
#define ATM_H

#include <string>
#include <iomanip>
#include <vector>
using namespace std;

struct account {
	string account_;
	string pin;
	double available_balance;
	double total_balance;
};

class atm
{
	private:
		vector<account> data;
		account* ptr;
		int cash = 10000;
	public:

		void add_menber(string act, string pin, double a_b, double t_b) {
			account temp;
			temp.account_ = act;
			temp.pin = pin;
			temp.available_balance = a_b;
			temp.total_balance = t_b;
			data.push_back(temp);
		}

		void login() {
			string input_account, input_pin;
			while (1) {
				cout << "Please enter your account number: ";
				cin >> input_account;
				int a;
				for (a = 0; a < data.size(); a++) {
					if (input_account == data[a].account_) {
						cout << "Enter your PIN: ";
						cin >> input_pin;
						if (input_pin == data[a].pin) {
							cout << endl;
							ptr = &data[a];
							goto end;
						}
						else {
							cout << "Wrong PIN! Please enter again.\n\n";
							break;
						}
					}
				}
				if (a == data.size())
					cout << "Account doesn't exist! Please enter again.\n\n";
			}
			end:
				return;
		}

		void print() {
			cout << "account number: " << ptr->account_ << endl;
			cout << "PIN: " << ptr->pin << endl;
			cout << "available balance: " << ptr->available_balance << endl;
			cout << "total balance: " << ptr->total_balance << "\n\n";
		}

		char main_menu() {
			char choice;
			cout << "Main menu:\n1 - View my balance\n2 - Withdraw cash\n3 - Deposit funds\n4 - Exit\n\nEnter a choice : ";
			cin >> choice;
			cout << endl;
			return choice;
		}

		void print_balance() {
			cout << "Balance Information:\n";
			cout << setw(25) << " - Available balance : $" << ptr->available_balance << endl;
			cout << setw(25) << " - Total balance : $" << ptr->total_balance << "\n\n";
		}

		void withdraw() {
			char choice;
			int money = 0;
			cout << "Withdrawal options:\n1 - $20\n2 - $40\n3 - $60\n4 - $100\n5 - $200\n6 - Cancel transaction\n\nChoose a withdrawal option(1 - 6) : ";
			cin >> choice;
			cout << endl; 
			if (choice == '1')
				money = 20;
			else if (choice == '2')
				money = 40;
			else if (choice == '3')
				money = 40;
			else if (choice == '4')
				money = 100;
			else if (choice == '5')
				money = 200;
			else if (choice == '6')
				return;
			else
				cout << "There is no selection " << choice << ". Please choice the right selection again.\n\n";

			if (ptr->available_balance - money < 0)
				cout << "There is not enough money in your account.\n\n";
			else if (cash - money < 0)
				cout << "There is no enough money. Please come earlier tomorrow.\n\n";
			else {
				ptr->available_balance -= money;
				ptr->total_balance -= money;
				cout << "Please take your cash from the cash dispenser.\n\n";
			}
		}

		void deposit() {
			double cents;
			cout << "Please enter a deposit amount in CENTS (or 0 to cancel): ";
			cin >> cents;
			if (cents == 0)
				return;
			cents /= 100;
			cout << "\nPlease insert a deposit envelope containing " << cents << " in the deposit slot.\n\nYour envelope has been received.\nNOTE: The money deposited will not be available until we\nverify the amount of any enclosed cash, and any enclosed checks clear.\n\n";
			ptr->total_balance += cents;
		}
};

#endif //ATM_H