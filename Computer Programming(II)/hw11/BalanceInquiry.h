// BalanceInquiry.h
// BalanceInquiry class definition. Represents a balance inquiry.
#ifndef BALANCE_INQUIRY_H
#define BALANCE_INQUIRY_H

#include <vector> // class uses vector to store Account objects
using namespace std;
#include "Account.h" // Account class definition

class BalanceInquiry
{
public:
   BalanceInquiry( int userAccountNumber, vector< Account > &atmAccounts ); // constructor
   void execute(); // perform the balance inquiry transaction
private:
   int accountNumber; // indicates account involved
   vector< Account > &accounts; // reference to the vector of the bank's Accounts

   // get pointer to Account object in "accounts" whose account number is equal to "accountNumber"
   Account * getAccount( int accountNumber, vector< Account > &accounts ); 
}; // end class BalanceInquiry

BalanceInquiry::BalanceInquiry(int userAccountNumber, vector< Account >& atmAccounts)
    :accountNumber(userAccountNumber), accounts(atmAccounts)
{
}

void BalanceInquiry::execute()
{
    cout << "Balance Information:\n";
    cout << setw(25) << " - Available balance : $" << getAccount(accountNumber, accounts)->getAvailableBalance() << endl;
    cout << setw(25) << " - Total balance : $" << getAccount(accountNumber, accounts)->getTotalBalance() << "\n\n";
}

Account* BalanceInquiry::getAccount(int accountNumber, vector< Account >& accounts)
{
    Account* ptr = nullptr;
    for (unsigned int a = 0; a < accounts.size(); a++) {
        if (accounts[a].getAccountNumber() == accountNumber)
            ptr = &accounts[a];
    }

    return ptr;
}

#endif // BALANCE_INQUIRY_H