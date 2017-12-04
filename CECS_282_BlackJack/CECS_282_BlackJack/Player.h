#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <string>

using namespace std;

class Player
{
public:
	static int memberID; //to be incremented with each instance
	Player();
	Player(string n);
	string getName();
	~Player();

private: 
	string name;
	int id;
	
};
#endif

