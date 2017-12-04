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
		for (int j = 1; j < 11; j++)
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


CardDeck::~CardDeck()
{
}
