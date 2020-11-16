// Deposit.h
// Deposit class definition. Represents a deposit transaction.
#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <vector> // class uses vector to store Account objects
using namespace std;
#include "Account.h" // Account class definition

class Deposit
{
public:
   Deposit( int userAccountNumber, vector< Account > &atmAccounts );
   void execute(); // perform the deposit transaction
private:
   int accountNumber; // indicates account involved
   vector< Account > &accounts; // reference to the vector of the bank's Accounts
   double amount; // amount to deposit

   // get pointer to Account object in "accounts" whose account number is equal to "accountNumber"
   Account * getAccount( int accountNumber, vector< Account > &accounts ); 
   double promptForDepositAmount() const; // prompt user to enter a deposit amount in cents 
}; // end class Deposit

Deposit::Deposit(int userAccountNumber, vector< Account >& atmAccounts)
    :accountNumber(userAccountNumber), accounts(atmAccounts), amount()
{
}

void Deposit::execute()
{
    double cents = promptForDepositAmount();

    if (cents == 0)
        return;
    cout << "\nPlease insert a deposit envelope containing " << cents << " in the deposit slot.\n\nYour envelope has been received.\nNOTE: The money deposited will not be available until we\nverify the amount of any enclosed cash, and any enclosed checks clear.\n\n";
    getAccount(accountNumber, accounts)->credit(cents);
}

Account* Deposit::getAccount(int accountNumber, vector< Account >& accounts)
{
    Account* ptr = nullptr;
    for (unsigned int a = 0; a < accounts.size(); a++) {
        if (accounts[a].getAccountNumber() == accountNumber)
            ptr = &accounts[a];
    }

    return ptr;
}

double Deposit::promptForDepositAmount() const
{
    double cents;
    cout << "Please enter a deposit amount in CENTS (or 0 to cancel): ";
    cin >> cents;
    cents /= 100;

    return cents;
}

#endif // DEPOSIT_H