#include"Card.h"
#include "CardDeck.h"
#include "Player.h"
#include "Account.h"
#include <iostream>
#include <iomanip>
#include "BlackJackPlayer.h"

using namespace std;

double getBet(Account& playerAcc)
{

	cout << "\nEnter amount to Bet: $";

	string amountStr;
	cin >> amountStr;

	bool isValid = true;

	for (char c : amountStr)
	{
		if (!isdigit(c))
			isValid = false;
	}

	if (isValid && (stod(amountStr) < 0 || stod(amountStr) > playerAcc.getBalance()))
		isValid = false;

	if (stod(amountStr) > playerAcc.getBalance())
	{
		cout << "\nInsuffienct funds to place bet of $" << stod(amountStr)
			<< " , your balance is $" << playerAcc.getBalance() << endl;
	}
	

	while (!isValid)
	{

		cout << "\nEnter valid amount to bet: $";

		cin >> amountStr;

		isValid = true;

		for (char c : amountStr)
		{
			if (!isdigit(c))
				isValid = false;
		}

		if (isValid && (stod(amountStr) < 0 || stod(amountStr) > playerAcc.getBalance()))
			isValid = false;

		if (stod(amountStr) > playerAcc.getBalance())
		{
			cout << "\nInsuffienct funds to place bet of $" << stod(amountStr)
				<< " , your balance is $" << playerAcc.getBalance() << endl;
		}
	}
		
	return stod(amountStr);
}


int getAccountNumber()
{
	cout << "Enter Account Number: " << endl;

	string accountNumStr;
	cin >> accountNumStr;

	bool isNum = true;
	for (char c : accountNumStr)
	{
		if (!isdigit(c))
			isNum = false;
	}

	while (!isNum)
	{
		cout << "Invalid Number, Enter Account Number: " << endl;

		cin >> accountNumStr;

		isNum = true;
		for (char c : accountNumStr)
		{
			if (!isdigit(c))
				isNum = false;
		}
	}

	return stoi(accountNumStr);;
}

int main()
{
	cout << fixed << showpoint << setprecision(2);

	//create account and make the balance the initial bet
	int accountNum = getAccountNumber();
	Player p1;
	Account playerAccount(p1, accountNum);

	//create game deck and player's hand
	CardDeck gameDeck;
	CardDeck playerHand;

	bool done = false;

	while (!done)
	{
		//recreate the deck
		gameDeck.initialize();
		playerHand.clear();

		getBet(playerAccount);



		if (playerAccount.getBalance() > 0)
			cout << "\nPlay another round? Enter 1 for Yes, 0 for No: " << endl;
		
		string choice;
		cin >> choice;
		done = (choice == "1" ? false : true);
	}

	

	for (int i = 0; i < gameDeck.getDeck().size(); i++)
	{
		gameDeck.getDeck().at(i).printCard();
		cout << " value : " << gameDeck.getDeck().at(i).getValue() << endl;
	}


	cout << endl;
	system("pause");
	return 0;
}


