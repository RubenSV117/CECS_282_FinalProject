#include"Card.h"
#include "CardDeck.h"
#include "Player.h"
#include "Account.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

//http://www.bicyclecards.com/how-to-play/blackjack/

//method prototypes
int getAccountNumber();
double getBet(Account& playerAcc);
void drawCards(CardDeck& handToAddTo, int numOfCards, bool isPlayerHand);
string getMove();
void resetGame();

//Game components
int accountNum = getAccountNumber();
Player p1;
Account playerAccount(p1, accountNum);

CardDeck gameDeck;
CardDeck playerHand;
CardDeck playerSecondHand;
CardDeck dealerHand;
bool donePlaying = false;
bool roundOver = false;
bool canSplit = false;
bool playerHasSplit = false;
bool hasPlayedSecondHand = false;
bool dealerGotBJ_inStand = false;
double currentBet = 0;
void hit();
void stand();
void split();

int main()
{
	srand(time(0));
	cout << fixed << showpoint << setprecision(2);

	while (!donePlaying)
	{
		cout << "--------------------------------------------------" << endl;
		//reset lose condition, player and dealer hands, and reset the gameDeck
		//Unless the player is playing their second hand after splitting
		if (!playerHasSplit)
		{
			resetGame();

			//new bet
			currentBet = getBet(playerAccount);

			//deal cards to player
			drawCards(playerHand, 2, true);


			//print player's hand and hand value
			cout << "\nYour ";
			playerHand.printHand(playerHand.getSize());
		}				
		
		//If the player has chosen to split and hasn't done so yet
		else if(playerHasSplit && !hasPlayedSecondHand)
		{
			playerHand.clear();

			Card c1 = playerSecondHand.get(0);
			Card c2 = playerSecondHand.get(1);

			playerHand.add(c1);
			playerHand.add(c2);

			playerSecondHand.clear();

			canSplit = false;
			hasPlayedSecondHand = true;
			playerHasSplit = false;

			cout << "Your ";
			playerHand.printHand(playerHand.getSize());

		}
			
		//draw dealer's hand
		drawCards(dealerHand, 2, false);
		
		while (!roundOver)
		{
			

			//print second hand if player split
			if (playerHasSplit)
			{
				//print player's second hand and hand value
				cout << "\n\nYour Second ";
				playerSecondHand.printHand(playerSecondHand.getSize());
			}

			//begin by only showing first card of the dealer's hand
			cout << "\n\nDealer's Hand: ";
			dealerHand.getDeck().at(0).printCard();
			cout << "__";

			string choice = getMove();
			cout << "-----------------------------" << endl;
			//Stand
			if (choice == "0")
				stand();

			//Hit
			else if (choice == "1")
				hit();
			
			//Split
			else if (choice == "2")
				split();
		
		}
		
		//If the round is over for the first hand, play the next round with the second hand
		if (playerHasSplit && !hasPlayedSecondHand)
		{
			cout << "--------------------------------------------------" << endl;
			cout << "\nNow playing your second hand" << endl;
		

			roundOver = false;
		}

		//If they still have money after the round, allow them another turn
		if (playerAccount.getBalance() > 0 && roundOver)
		{
			cout << "\nYour current balance is $" << playerAccount.getBalance()
				 << "\nPlay another round? Enter 1 for Yes, 0 for No: " << endl;

			string choice;
			cin >> choice;
			donePlaying = (choice == "1" ? false : true);
		}

		else if (playerAccount.getBalance() == 0 && roundOver)
		{
			cout << "\n\nYour balance is now $0.00" << endl;
			donePlaying = true;
		}
	}

	cout << "\nThanks for Playing" << endl;
	system("pause");
	return 0;
}


/*
Gets user inputed account number and validates that it is numeric
*/
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


/*
Gets user inputed bet amount and validates that it is greater than 0 but less than the player account balance
*/
double getBet(Account& playerAcc)
{

	cout << "\nEnter amount to Bet: $";

	string amountStr;
	cin >> amountStr;

	bool isValid = true;

	//validate that the user inputed a number
	for (char c : amountStr)
	{
		if (!isdigit(c) && c != '.')
			isValid = false;
	}

	//check that the number is non-negative and below the user's balance
	if (isValid && (stod(amountStr) <= 0 || stod(amountStr) > playerAcc.getBalance()))
		isValid = false;

	if (isValid && stod(amountStr) > playerAcc.getBalance())
	{
		cout << "\nInsuffienct funds to place a bet of $" << stod(amountStr)
			<< ", your balance is $" << playerAcc.getBalance() << endl;
	}

	//loop until they enter a valid amount
	while (!isValid)
	{

		cout << "\nEnter valid amount to bet: $";

		cin >> amountStr;

		isValid = true;

		for (char c : amountStr)
		{
			if (!isdigit(c) && c != '.')
				isValid = false;
		}

		if (isValid && (stod(amountStr) <= 0 || stod(amountStr) > playerAcc.getBalance()))
			isValid = false;

		if (isValid && stod(amountStr) > playerAcc.getBalance())
		{
			cout << "\nInsuffienct funds to place bet of $" << stod(amountStr)
				<< " , your balance is $" << playerAcc.getBalance() << endl;
		}
	}

	//withdraw the bet amount from their account
	playerAcc.withdraw(stod(amountStr));
	return stod(amountStr);
}

/*
Draw a specified number of cards from the game deck and inserts them into the specified deck
*/
void drawCards(CardDeck& handToAddTo, int numOfCards, bool isPlayerHand)
{
	for (int i = 0; i < numOfCards; i++)
	{
		int randomIndex = rand() % gameDeck.getDeck().size();
		Card c = gameDeck.getDeck().at(randomIndex);
		handToAddTo.add(c);
		gameDeck.remove(randomIndex);
	}

	//if the player has been dealt a pair and their account has enough for another bet of the same amount, allow them to split
	if (isPlayerHand && playerHand.getSize() == 2 && playerHand.get(0).getRank() == playerHand.get(1).getRank() && playerAccount.getBalance() > currentBet && !playerHasSplit)
		canSplit = true;

	//if dealer also got a blackjack, the player gets half their bet back
	if (handToAddTo.getHandValue() == 21)
	{

		if (isPlayerHand)
		{
			//if dealer also got a blackjack, the player gets half their bet back
			if (dealerHand.getHandValue() == 21)
			{
				cout << "\nBoth You and dealer got a blackjack, round ends in a tie. "
					<< "You are refunded half of your bet: $" << (currentBet / 2);

				playerAccount.deposit(currentBet / 2);
			}

			//else the player wins double the amount they bet
			else
			{
				cout << "\nBlackjack. You win this round and win double your bet: $" << (currentBet * 2) << endl;
				playerAccount.deposit(currentBet * 2);
			}

			roundOver = true;
		}

		else
		{
			dealerGotBJ_inStand = true;
			cout << "\n\nDealer's ";
			dealerHand.printHand(dealerHand.getSize());

			cout << "\n\nDealer has blackjack" << endl;
		}
			
		roundOver = true;
	}
}

/*
Gets user decision to hit or stand
*/
string getMove()
{
	string choice;
	//Hit or stand
	string choiceList = "\n\nEnter 0 to Stand, 1 to Hit";
	choiceList += (canSplit == true ? ", 2 to Split" : "");
	choiceList += ": ";

	cout << choiceList;

	cin >> choice;

	bool validChoice = true;
	if (choice.size() != 1 || !isdigit(choice[0]) || (stoi(choice) != 0 && stoi(choice) != 1 && stoi(choice) != 2))
		validChoice = false;

	while (!validChoice)
	{
		choiceList = "\n\nInvalid Choice, Enter 0 to Stand, 1 to Hit";
		choiceList += (canSplit == true ? ", 2 to Split" : "");
		choiceList += ": ";

		cout << choiceList;		
		cin >> choice;

		validChoice = true;
		if (choice.size() != 1 || !isdigit(choice[0]) || (stoi(choice) != 0 && stoi(choice) != 1 && stoi(choice) != 2))
			validChoice = false;
	}

	return choice;
}

/*
Resets the game to begin the next round
*/
void resetGame()
{
	roundOver = false;
	playerHasSplit = false;
	canSplit = false;
	dealerGotBJ_inStand = false;
	//empty player, dealer, and gameDeck before dealing them new cards
	playerHand.clear();
	playerSecondHand.clear();
	dealerHand.clear();
	gameDeck.clear();

	//recreate the deck
	gameDeck.initialize();
}

/*
Deals an additional card to the player, defines behavior for a Bust and a Blackjack
*/
void hit()
{
	//draw 1 card
	drawCards(playerHand, 1, true);

	//reprint your hand and new hand value
	cout << "\nYour ";
	playerHand.printHand(playerHand.getSize());

	//if hand values exceeds 21 after drawing a new card
	if (playerHand.getHandValue() > 21)
	{
		cout << "\n\nBust. Your hand value is over 21." << endl;
		roundOver = true;
	}

	
}

/*
Defines the behavior fo rthe dealer's turn once the player has decided to stand
*/
void stand()
{

	//dealer must keep Hitting until their hand value is 17 or above
	while (dealerHand.getHandValue() < 17)
	{
		drawCards(dealerHand, 1, false);
	}

	if (!dealerGotBJ_inStand)
	{
		cout << "\nDealer's ";
		dealerHand.printHand(dealerHand.getSize());

		//at this point the player has less than 21, so if the dealer gets blackjack,
		//the dealer wins the round
		if (dealerHand.getHandValue() == 21)
		{
			cout << "\n\nThe dealer has blackjack." << endl;
		}
	}
	

	//dealer busts
	if (dealerHand.getHandValue() > 21)
	{
		cout << "\n\nThe dealer busts. You win this round and win double your bet: $" << (currentBet * 2) << endl;
		playerAccount.deposit(currentBet * 2);
	}

	//both the player and dealer have less than 21, see who is closer, or if its a tie
	else
	{
		if (dealerHand.getHandValue() == playerHand.getHandValue())
		{
			cout << "\n\nThe dealer's hand has the same value as yours. Round ends in a tie. "
				<< "You are refunded half of your bet: $" << (currentBet / 2) << endl;

			playerAccount.deposit(currentBet / 2);
		}

		else if (dealerHand.getHandValue() > playerHand.getHandValue())
			cout << "\n\nThe dealer wins." << endl;
		
		else
		{
			cout << "\n\nYou win this round and win double your bet: $" << (currentBet * 2) << endl;
			playerAccount.deposit(currentBet * 2);
		}
	}
		
	roundOver = true;
}

/*
Draws card for a second hand that will be played separately from the player's first hand
*/
void split()
{
	canSplit = false;
	//split the first deck into the first and second  hand
	Card c = playerHand.get(1);
	playerSecondHand.add(c);
	playerHand.remove(1);

	//draw another card to each of the player hands
	drawCards(playerHand, 1, true);
	drawCards(playerSecondHand, 1, true);
	playerHasSplit = true;


	cout << "\nYour First ";
	playerHand.printHand(playerHand.getSize());

}







