#pragma once
#ifndef CARDDECK_H
#define CARDDECK_H
#include <vector>
#include "Card.h"

class CardDeck
{
private:
	vector<Card> deck;

public:
	CardDeck();
	void initialize();
	vector<Card> getDeck();
	int getSize();
	void clear();
	Card get(int index);
	void remove(int index);
	void add(Card c);
	void printHand(int numToPrint);
	int getHandValue();
	~CardDeck();
};
#endif

