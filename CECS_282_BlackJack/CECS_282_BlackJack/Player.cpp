#include "Player.h"

int Player::memberID = 1; //to intialize once

Player::Player()
{
	name = "Name not set";
	id = 0;
}

Player::Player(string n)
{
	name = n;
	id = Player::memberID++;
}

string Player::getName()
{
	return name;
}


Player::~Player()
{
}
