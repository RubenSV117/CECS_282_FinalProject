#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "Player.h"
#include <iostream>
#include <iomanip>

using namespace std;

class Account
{
private:
	int id;
	double balance;
	Player owner;

public:
	Account();
	Account(Player p, int accountNum);
	static int accountId;
	int getId();
	int getBalance();
	void withdraw(double amount);
	void deposit(double amount);
	double getInitialBal();
	~Account();
};
#endif

