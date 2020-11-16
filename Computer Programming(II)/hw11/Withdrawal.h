// Withdrawal.h
// Withdrawal class definition. Represents a withdrawal transaction.
#ifndef WITHDRAWAL_H
#define WITHDRAWAL_H

#include <vector> // class uses vector to store Account objects
using namespace std;
#include "Account.h" // Account class definition

class Withdrawal
{
public:
   Withdrawal( int userAccountNumber, vector< Account > &atmAccounts, int &atmRemainingBills );
   void execute(); // perform the withdrawal transaction
private:
   int accountNumber; // indicates account involved
   vector< Account > &accounts; // reference to the vector of the bank's Accounts
   int amount; // amount to withdraw
   int &remainingBills; // number of $20 bills remaining 

   // get pointer to Account object in "accounts" whose account number is equal to "accountNumber"
   Account * getAccount( int accountNumber, vector< Account > &accounts );

   // display a menu of withdrawal amounts and the option to cancel;
   // return the chosen amount or 0 if the user chooses to cancel
   int displayMenuOfAmounts() const;
}; // end class Withdrawal

Withdrawal::Withdrawal(int userAccountNumber, vector< Account >& atmAccounts, int& atmRemainingBills)
    :accountNumber(userAccountNumber), accounts(atmAccounts), amount(), remainingBills(atmRemainingBills)
{
}

void Withdrawal::execute()
{
    int choice = displayMenuOfAmounts();
    int money = 0;

    if (choice == 1)
        money = 20;
    else if (choice == 2)
        money = 40;
    else if (choice == 3)
        money = 40;
    else if (choice == 4)
        money = 100;
    else if (choice == 5)
        money = 200;
    else if (choice == 6)
        return;
    else
        cout << "There is no selection " << choice << ". Please choice the right selection again.\n\n";

    if (getAccount(accountNumber, accounts)->getAvailableBalance() - money < 0)
        cout << "There is not enough money in your account.\n\n";
    else if (remainingBills - money < 0)
        cout << "There is no enough money. Please come earlier tomorrow.\n\n";
    else {
        getAccount(accountNumber, accounts)->debit(money);
        remainingBills -= money;
        cout << "Please take your cash from the cash dispenser.\n\n";
    }
}

Account* Withdrawal::getAccount(int accountNumber, vector< Account >& accounts)
{
    Account* ptr = nullptr;
    for (unsigned int a = 0; a < accounts.size(); a++) {
        if (accounts[a].getAccountNumber() == accountNumber)
            ptr = &accounts[a];
    }

    return ptr;
}

int Withdrawal::displayMenuOfAmounts() const
{
    int choice;
    cout << "Withdrawal options:\n1 - $20\n2 - $40\n3 - $60\n4 - $100\n5 - $200\n6 - Cancel transaction\n\nChoose a withdrawal option(1 - 6) : ";
    cin >> choice;
    cout << endl;

    return choice;
}

#endif // WITHDRAWAL_H