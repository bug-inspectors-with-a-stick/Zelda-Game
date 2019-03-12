#pragma once

#include "Room.h"

class Castle
{
private:
	static int const numRooms = 9;
	Room rooms[numRooms];

public:
	inline Room* getRoom(int);

	void LinkRoomsWithOtherThings(Item**, Monster**, Princess*);
	void HiddenRoomsUnlocker(char const*, Monster**);
	void LinkRoom5and8();
	void LinkRoom6and9();

	inline void setDescriptionOfRooms();
	inline void setNumbersofRooms();
};