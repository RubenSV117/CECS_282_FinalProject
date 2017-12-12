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
	{
		cout << "\nInsufficient funds to withdraw amount of $" << amount
			<< ", current balance is $" << balance << endl;
	}
		
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

Account::Account(Player p, int accountNum)
{
	owner = p;
	balance = getInitialBal();
	id = accountNum;
}

double Account::getInitialBal()
{

	cout << "\nEnter initial balance: $";

	string amountStr;
	cin >> amountStr;

	bool isValid = true;

	for (char c : amountStr)
	{
		if (!isdigit(c) && c != '.')
			isValid = false;
	}

	if (isValid && stoi(amountStr) < 0)
		isValid = false;

	while (!isValid)
	{

		cout << "\nInavlid Amount, Enter intitial balance: $";
		cin >> amountStr;

		isValid = true;

		for (char c : amountStr)
		{
			if (!isdigit(c) && c != '.')
				isValid = false;
		}

		if (isValid && stoi(amountStr) < 0)
			isValid = false;
	}

	return stod(amountStr);
}

Account::~Account()
{
}
