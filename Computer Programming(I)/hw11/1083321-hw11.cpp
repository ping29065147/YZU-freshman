#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <string.h>
#include <string>
using namespace::std;

char foods[14][48] = { "",
						   "Pork XiaoLongBao (12)",
						   "Steamed Vegetable and Ground Pork Dumplings (8)",
						   "Steamed Shrimp and Pork Dumplings (8)",
						   "Steamed Fish Dumplings (8)",
						   "Steamed Vegetarian Mushroom Dumplings (8)",
						   "Steamed Shrimp and Pork Shao Mai (12)",
						   "Pork Buns (5)",
						   "Vegetable and Ground Pork Buns (5)",
						   "Red Bean Buns (5)",
						   "Sesame Buns (5)",
						   "Taro Buns (5)",
						   "Vegetarian Mushroom Buns (5)",
						   "Golden Lava Buns (5)" };

int price[14] = { 0, 220, 176, 216, 200, 200, 432, 225,
					   225, 200, 200, 225, 250, 225 };

struct Date
{
	int year;
	int month;
	int day;
};

struct Account
{
	char email[40]; // used as the account number
	char password[20];
	char name[12];
	char address[80];
	char phone[12];
	int cart[14]; // Cart[i] is the quantity of food #i in the shopping cart
};

struct Order
{
	char orderNumber[12];
	char email[40];
	Date deliveryDate;
	Date arrivalDate;
	int quantity[14]; // quantity[i] is the quantity of food #i in the order
};

// input an integer in the range [ begin, end ]
int inputAnInteger(int begin, int end);

// add a new account to the file Accounts.dat
void registration(vector< Account > &accountDetails);

// return true if email belongs to accountDetails
bool exists(char email[], const vector< Account > &accountDetails);

// save all elements in accountDetails to the file Accounts.dat
void saveAllAccounts(const vector< Account > &accountDetails);

// login and call shopping
void login(vector< Account > &accountDetails);

// load all accounts details from the file Accounts.dat
void loadAccountDetails(vector< Account > &accountDetails);

// return true if there exists an account with specified email and password; and
// put the account with specified email and password into account
bool valid(char email[], char password[], Account &account,
	const vector< Account > &accountDetails);

// add chosen Foods to the shopping cart
void shopping(Account &account);

// return true if the shopping cart is empty
bool emptyCart(const Account &account);

// display the shopping cart in account
bool displayCart(const Account &account);

// append account in the file Accounts.dat
void saveAccount(const Account &account);

// update the shopping cart in account
void updateCart(Account &account);

// generate a Bill and reset account.cart
void check(Account &account);

// compute the current date
void compCurrentDate(Date &currentDate);

// open the file Orders.txt and call displayOrderDetails twice
void createOrder(const Account &account, const Order &order);

// write an order to Orders.txt or display it on the output window depending on os
void displayOrderDetails(ostream &os, const Account &account, const Order &order);

int main()
{
	vector< Account > accountDetails; // account details for all accounts

	cout << "Welcome to DintaiFung Shopping Mall!\n";
	srand(static_cast<int>(time(0)));

	int choice;

	while (true)
	{
		cout << "\n1 - Registration\n";
		cout << "2 - Login\n";
		cout << "3 - End\n";

		do cout << "\nEnter your choice (1~3): ";
		while ((choice = inputAnInteger(1, 3)) == -1);
		cout << endl;

		switch (choice)
		{
		case 1:
			registration(accountDetails);
			break;

		case 2:
			login(accountDetails);
			break;

		case 3:
			cout << "Thank you! Goodbye!\n\n";
			system("pause");
			return 0;
		}
	}

	system("pause");
}

int inputAnInteger(int begin, int end)
{
	string input;
	int trans;
	cin >> input;

	if (input.size() == 2)
		trans = (input[0] - '0') * 10 + (input[1] - '0');
	else
		trans = (input[0] - '0');

	if (trans >= begin && trans <= end)
		return trans;
	else
		return -1;
}

void registration(vector< Account > &accountDetails)
{
	Account re;
	int a;

	cout << "Email address (Account number): ";
	cin >> re.email;

	if (exists(re.email, accountDetails))
		cout << "\nYou are already a member!\n";
	else {
		cout << "Password: ";
		cin >> re.password;

		cout << "Name: ";
		cin >> re.name;

		cout << "Shipping address: ";
		cin >> re.address;

		cout << "Contact phone number: ";
		cin >> re.phone;

		for (a = 0; a < 14; a++)
			re.cart[a] = 0;

		accountDetails.push_back(re);
		cout << "\nRegistration Completed!\n";

		saveAllAccounts(accountDetails);
	}


}

bool exists(char email[], const vector< Account > &accountDetails)
{
	int a;
	for (a = 0; a < accountDetails.size(); a++) {
		if (!(strcmp(email, accountDetails[a].email)))
			return true;
	}
	return false;
}

void saveAllAccounts(const vector< Account > &accountDetails)
{
	int a;
	ofstream outFile("Accounts.dat", ios::out | ios::binary);

	for (a = 0; a < accountDetails.size(); a++) {
		outFile.write(reinterpret_cast<const char*> (&(accountDetails[a])), sizeof(Account));
	}
	outFile.close();
}

void login(vector< Account > &accountDetails)
{
	loadAccountDetails(accountDetails);

	int a, choice;
	char mail[40], pass[20];
	bool check = true;
	Account current;

	while (1) {
		cout << "Email address (0 to end): ";
		cin >> mail;
		if (strlen(mail) == 1 && mail[0] == '0')
			return;
		cout << "Password: ";
		cin >> pass;
		cout << endl;

		if (valid(mail, pass, current, accountDetails))
			break;
		else
			cout << "Invalid email address or password. Please try again.\n\n";
	}

	shopping(current);
}

void loadAccountDetails(vector< Account > &accountDetails)
{
	ifstream inFile("Accounts.dat", ios::binary | ios::in);
	accountDetails.clear();
	Account input;

	while (inFile.read((char*)&input, sizeof(Account)))
		accountDetails.push_back(input);

	inFile.close();
}

bool valid(char email[], char password[], Account &account,
	const vector< Account > &accountDetails)
{
	int a;

	for (a = 0; a < accountDetails.size(); a++) {
		if (!(strcmp(email, accountDetails[a].email)) && !(strcmp(password, accountDetails[a].password))) {
			account = accountDetails[a];
			return true;
		}
	}
	return false;
}

void shopping(Account &account)
{
	int a, choice, k, q;

	for (a = 1; a < 14; a++)
		cout << setw(2) << right << a << ". " << setw(50) << left << foods[a] << price[a] << endl;
	k = 13;

	if (!emptyCart(account)) {
		cout << endl << "14. " << "View your shopping cart" << endl;
		k = 14;
	}

	do cout << "\nEnter your choice (0 to logout): ";
	while ((choice = inputAnInteger(0, k)) == -1);

	if (choice == 0)
		return;
	else if (choice == 14) {
		cout << "Your Shopping Cart Contents:\n\n";
		displayCart(account);
	}
	else {
		do cout << "\nEnter the quantity: ";
		while ((q = inputAnInteger(0, 1000)) == -1);
		cout << endl;

		account.cart[choice] += q;

		saveAccount(account);
		cout << "Your Shopping Cart Contents:\n\n";
		displayCart(account);
	}

	while (true) {
		cout << "\n1. Continue Shopping\n";
		cout << "2. Update Cart\n";
		cout << "3. Check\n";

		do cout << "\nEnter your choice (1~3): ";
		while ((choice = inputAnInteger(1, 3)) == -1);
		cout << endl;

		switch (choice)
		{
		case 1:
			shopping(account);
			return;

		case 2:
			updateCart(account);
			break;

		case 3:
			check(account);
			return;
		}
	}

}

bool emptyCart(const Account &account)
{
	int a;

	for (a = 1; a < 14; a++) {
		if (account.cart[a] != 0)
			return false;
	}
	return true;
}

bool displayCart(const Account &account)
{
	int a, total = 0;

	cout << "Code" << setw(50) << right << "Item" << setw(7) << "Price" << setw(10) << "Quantity" << setw(10) << "Subtotal" << endl;

	for (a = 1; a < 14; a++) {
		if (account.cart[a] != 0) {
			cout << setw(4) << right << a << setw(50) << foods[a] << setw(7) << price[a] << setw(10) << account.cart[a] << setw(10) << price[a] * account.cart[a] << endl;
			total += price[a] * account.cart[a];
		}
	}
	cout << "\nTotal Cost: " << total << endl;

	return true;
}

void saveAccount(const Account &account)
{
	vector<Account> data;
	Account input;
	int a, b;

	ifstream inFile("Accounts.dat", ios::in | ios::binary);

	while (inFile.read((char*)&input, sizeof(Account)))
		data.push_back(input);
	inFile.close();

	for (a = 0; a < data.size(); a++) {
		if (!strcmp(account.email, data[a].email)) {
			for (b = 0; b < 14; b++)
				data[a].cart[b] = account.cart[b];
		}
	}

	ofstream outFile("Accounts.dat", ios::out | ios::binary);

	for (a = 0; a < data.size(); a++) {
		outFile.write(reinterpret_cast<const char*> (&(data[a])), sizeof(Account));
	}
	outFile.close();

}

void updateCart(Account &account)
{
	int code, q;

	while (1) {
		cout << "Enter the product code: ";
		cin >> code;
		cout << endl;
		if (account.cart[code] != 0)
			break;
	}

	do cout << "\nEnter the quantity: ";
	while ((q = inputAnInteger(0, 1000)) == -1);
	cout << endl;

	account.cart[code] = q;
	saveAccount(account);

	cout << "Your Shopping Cart Contents:\n\n";
	displayCart(account);
}

void check(Account &account)
{
	int a;
	Order neworder;

	strcpy_s(neworder.email, account.email);

	cout << "Enter arrival dateDate";
	cout << "\nyear: ";
	cin >> neworder.arrivalDate.year;
	cout << "month: ";
	cin >> neworder.arrivalDate.month;
	cout << "day: ";
	cin >> neworder.arrivalDate.day;

	srand(time(NULL));
	neworder.orderNumber[0] = (rand() % 26) + 'A';
	for (a = 1; a <= 9; a++)
		neworder.orderNumber[a] = (rand() % 10) + '0';

	compCurrentDate(neworder.deliveryDate);

	for (a = 0; a < 14; a++)
		neworder.quantity[a] = account.cart[a];

	cout << "\n";
	createOrder(account, neworder);
	cout << "\nAn order has been created.\n";

	for (a = 0; a < 14; a++)
		account.cart[a] = 0;
	saveAccount(account);
}

void compCurrentDate(Date &currentDate)
{
	tm structtime;
	time_t rawtime = time(0);
	localtime_s(&structtime, &rawtime);
	currentDate.year = structtime.tm_year + 1900;
	currentDate.month = structtime.tm_mon + 1;
	currentDate.day = structtime.tm_mday;
}

void createOrder(const Account &account, const Order &order)
{
	ofstream outFile("Orders.txt", ios::app);
	outFile.close();

	ifstream inFile("Orders.txt", ios::in);
	displayOrderDetails(cout, account, order);
	displayOrderDetails(outFile, account, order);

	inFile.close();
}

void displayOrderDetails(ostream &os, const Account &account, const Order &order)
{
	int a, total = 0;

	os << "Order number: ";
	for (a = 0; a < 10; a++)
		os << order.orderNumber[a];
	os << "\nDelivery Date: " << order.deliveryDate.year << "/" << order.deliveryDate.month << "/" << order.deliveryDate.day << endl;
	os << "\nArrival Date: " << order.arrivalDate.year << "/" << order.arrivalDate.month << "/" << order.arrivalDate.day << endl;

	os << "Recipient: " << account.name << endl;
	os << "Contact Phone Number: " << account.phone << endl;
	os << "Shipping address: " << account.address << endl;

	os << "\nShopping details:\n\n";
	os << "Code" << setw(50) << right << "Item" << setw(7) << "Price" << setw(10) << "Quantity" << setw(10) << "Subtotal" << endl;
	for (a = 1; a < 14; a++) {
		if (account.cart[a] != 0) {
			os << setw(4) << right << a << setw(50) << foods[a] << setw(7) << price[a] << setw(10) << account.cart[a] << setw(10) << price[a] * account.cart[a] << endl;
			total += price[a] * account.cart[a];
		}
	}
	os << "\nTotal Cost: " << total << endl;
}


<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head><meta http-equiv="Content-Type" content="text/html; charset=utf-8" /><title>

</title></head>
<body>
    <form method="post" action="./File_DownLoad_Wk_zip.aspx?File_name=1083321-hw11.cpp&amp;type=3&amp;id=2838395" id="form1">
<div class="aspNetHidden">
<input type="hidden" name="__VIEWSTATE" id="__VIEWSTATE" value="/wEPDwUKLTEzNDM3NzkxOWRkwneTr34MFXJYUKyKKda+DU4gQVM=" />
</div>

<div class="aspNetHidden">

	<input type="hidden" name="__VIEWSTATEGENERATOR" id="__VIEWSTATEGENERATOR" value="629601C3" />
</div>
    <div>
    
    </div>
    </form>
</body>
</html>
