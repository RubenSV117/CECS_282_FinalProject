#include "Card.h"

Card::Card()
{
}

Card::Card(SUIT suit, string rank)
{
	this->suit = suit;
	this->rank = rank;
	
	//numbered rank
	if (isdigit(rank[0]))
		value = stoi(rank);

	//Ace, value will be converted to 1 if the sum of current hand exceeds 21
	else if (rank[0] == 'A')
		value = 11;

	//J, Q, K
	else
		value = 10;
}

Card::SUIT Card::getSuit()
{
	return suit;
}

int Card::getValue()
{
	return value;
}

void Card::printCard()
{
	//rank
	cout << rank;

	//set output mode to unicode to print the symbol
	_setmode(_fileno(stdout), _O_U16TEXT);

	//symbol for suit in unicode
	switch (suit)
	{
	case Spades:
		wprintf(L"\x2660 ");
			break;

	case Hearts:
		wprintf(L"\x2665 ");
			break;

	case Diamonds:
		wprintf(L"\x2666 ");
		break;

	case Clubs:
		wprintf(L"\x2663 ");
		break;
	}
	
	//set output mode back to normal text
	_setmode(_fileno(stdout), _O_TEXT);
}


Card::~Card()
{
}
