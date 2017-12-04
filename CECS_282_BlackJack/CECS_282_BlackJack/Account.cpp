#include "Account.h"



int Account::getId()
{
	return id;
}

int Account::getBalance()
{
	return balance;
}

void Account::withdraw(double amount)
{
	cout << fixed << showpoint << setprecision(2);

	if (balance - amount < 0)
		cout << "\nInsufficient funds to place bet of $" << amount;

	else
		balance -= amount;

}

void Account::deposit(double amount)
{
	balance += amount;
}

Account::Account()
{
	owner = Player();
	balance = 0;
}

Account::Account(Player p, double initialBal)
{
	owner = p;
	balance = initialBal;
}


Account::~Account()
{
}
