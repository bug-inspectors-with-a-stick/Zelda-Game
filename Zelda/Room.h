#pragma once

#include "Item.h"
#include "Monster.h"
#include "Princess.h"

class Room
{
private:
	static int const numPaths = 4;
	static int const numItems = 5;

	Room* 		paths[numPaths];
	Item* 		items_Present[numItems];
	Monster*    monster_Present;
	Princess*   princess_Present;

	char*		description;
	int 		roomNumber;


public:
	Room();
	~Room();

	inline Room** 		getPaths();
	inline Item**		getItemsPresent();
	inline Monster*		getMonsterPresent();
	inline Princess*	getPrincessPresent();
	inline char*		getDescription();
	inline int 			getRoomNumber();

	bool				isRoomFull();


	int					directionIndex(char const*);
	char const* 		directionName(int);

	inline void			setEast(Room*);
	inline void			setWest(Room*);
	inline void			setSouth(Room*);
	inline void			setNorth(Room*);

	inline void			setMonsterPresent(Monster*);
	inline void			setItemsPresent(int, Item*);
	inline void			setPrincessPresent(Princess*);
	inline void			setDesription(char const*);
	inline void			setRoomNumber(int);


};