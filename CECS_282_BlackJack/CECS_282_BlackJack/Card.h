﻿#pragma once
#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <string>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>


using namespace std;

class Card
{

public:
	static enum SUIT { Hearts, Diamonds, Spades, Clubs };
	Card();
	Card(SUIT suit, string rank);
	SUIT getSuit();
	int getValue();
	void revertAceToOne();
	string getRank();
	void printCard();
	~Card();


private:
	SUIT suit;
	string rank;
	int value;
};
#endif


