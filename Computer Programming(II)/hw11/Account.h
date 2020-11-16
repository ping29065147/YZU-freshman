// Account.h
// Account class definition. Represents a bank account.
#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account
{
public:
   Account( int theAccountNumber, int thePIN, double theAvailableBalance,
            double theTotalBalance ); // constructor sets attributes
   bool validatePIN( int userPIN ) const; // is user-specified PIN correct?
   double getAvailableBalance() const; // returns available balance
   double getTotalBalance() const; // returns total balance
   void credit( double amount ); // adds an amount to the Account balance
   void debit( double amount ); // subtracts an amount from the Account balance
   int getAccountNumber() const; // returns account number
private:
   int accountNumber; // account number
   int pin; // PIN for authentication
   double availableBalance; // funds available for withdrawal
   double totalBalance; // funds available + funds waiting to clear
}; // end class Account

Account::Account(int theAccountNumber, int thePIN, double theAvailableBalance, double theTotalBalance)
{
    accountNumber = theAccountNumber;
    pin = thePIN;
    availableBalance = theAvailableBalance;
    totalBalance = theTotalBalance;
}

bool Account::validatePIN(int userPIN) const
{
    return (pin == userPIN);
}

double Account::getAvailableBalance() const
{
    return availableBalance;
}

double Account::getTotalBalance() const
{
    return totalBalance;
}

void Account::credit(double amount)
{
    totalBalance += amount;
}

void Account::debit(double amount)
{
    availableBalance -= amount;
    totalBalance -= amount;
}

int Account::getAccountNumber() const
{
    return accountNumber;
}

#endif // ACCOUNT_H