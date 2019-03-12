#pragma once

#include "Item.h"
#include "Princess.h"
#include "Room.h"

class Player
{

private:
	char* 		name;
	Princess* 	princess_Pointer;
	Item* 		bag[10];
	Room* 		current_Room;

	bool is_Alive;
	int  cash;

	//Utility Functions

	bool isBagEmpty();
	bool isBagFull();

public:

	Player();
	~Player();
	Player(char const*, Room*);

	inline bool 	getCurrentState();
	inline void 	setCurrentState(bool);

	inline Princess* getPrincess_Pointer();

	void 			CashUpdater();
	inline int  	getCash();
	inline char*	getPlayerName();

	bool			Move(char const*, bool&);
	void			Pick(char const*);
	void			Drop(char const*);
	void			Look();
	bool			Attack(char const*);
	void			Exit();


};