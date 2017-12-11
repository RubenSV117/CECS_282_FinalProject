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
	void clear();
	~CardDeck();
};
#endif

