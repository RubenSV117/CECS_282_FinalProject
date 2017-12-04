#include"Card.h"
#include "CardDeck.h"
#include "Player.h"
#include "Account.h"

using namespace std;

int main()
{

	CardDeck deck;

	for (int i = 0; i < deck.getDeck().size(); i++)
	{
		deck.getDeck().at(i).printCard();
		cout << " value: " << deck.getDeck().at(i).getValue() << endl;
	}


	cout << endl;
	system("pause");
	return 0;
}