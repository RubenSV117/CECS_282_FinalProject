#include "CardDeck.h"



CardDeck::CardDeck()
{
	initialize();
}


void CardDeck::initialize()
{
	Card::SUIT currentSuit;

	for (int i = 0; i < 4; i++)
	{
		//iterate throught the suits of the deck
		switch (i)
		{
		case 0:
			currentSuit = Card::SUIT::Hearts;
			break;
		case 1:
			currentSuit = Card::SUIT::Diamonds;
			break;
		case 2:
			currentSuit = Card::SUIT::Spades;
			break;
		case 3:
			currentSuit = Card::SUIT::Clubs;
			break;
		}

		//assign the numbered ranks
		for (int j = 2; j < 11; j++)
		{
			string numStr = to_string(j);
			Card numberedCard(currentSuit, numStr);
			deck.push_back(numberedCard);
		}

		//assign the face ranks
		Card jack(currentSuit, "J");
		deck.push_back(jack);

		Card queen(currentSuit, "Q");
		deck.push_back(queen);

		Card king(currentSuit, "K");
		deck.push_back(king);

		Card ace(currentSuit, "A");
		deck.push_back(ace);
		
	}
}

vector<Card> CardDeck::getDeck()
{
	return deck;
}

int CardDeck::getSize()
{
	return deck.size();
}

void CardDeck::clear()
{
	deck.clear();
}

Card CardDeck::get(int index)
{
	return deck.at(index);
}

void CardDeck::remove(int index)
{
	//vectors use an iterator to destroy indexes, deck.begin() is at index 0
	deck.erase(deck.begin() + index);
}

void CardDeck::add(Card c)
{
	deck.push_back(c);
}

void CardDeck::printHand(int numToPrint)
{
	cout << "Hand: ";

	for (int i = 0; i < numToPrint; i++)
		deck.at(i).printCard();

	cout << "\nHand Value: " << getHandValue();
}

int CardDeck::getHandValue()
{
	//add sum of card values for entire hand
	int value = 0;

	for (int i = 0; i < deck.size(); i++)
	{
		value += deck.at(i).getValue();
	}

	//if value is over 21, reduce the value of the Aces (if any) to 1 
	if (value > 21)
	{
		//get the number of aces
		int numOfAces = 0;
		for (Card c : deck)
		{
			if (c.getRank() == "A")		
				numOfAces++;					
		}

		//for each ace, reduce the value by 10  and see if the total hand value is still over 21
		for (int i = 0; i < numOfAces; i++)
		{
			if (value > 21)
			{
				value -= 10;
			}

			else
				break;
		}
	}


	return value;
}


CardDeck::~CardDeck()
{
}
