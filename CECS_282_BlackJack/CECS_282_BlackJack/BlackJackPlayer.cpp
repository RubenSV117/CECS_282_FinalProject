#include"Card.h"

using namespace std;

int main()
{
	Card c1(Card::SUIT::Hearts, '3');
	Card c2(Card::SUIT::Diamonds, 'J');
	Card c3(Card::SUIT::Spades, 'A');
	Card c4(Card::SUIT::Clubs, 'K');

	c1.printCard();
	cout << " value: " << c1.getValue() << endl;
	c2.printCard();
	cout << " value: " << c2.getValue() << endl;
	c3.printCard();
	cout << " value: " << c3.getValue() << endl;
	c4.printCard();
	cout << " value: " << c4.getValue() << endl;


	cout << endl;
	system("pause");
	return 0;
}