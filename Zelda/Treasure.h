#pragma once

#include "Item.h"

class Treasure : public Item
{
private:
	int worth;

public:

	Treasure();
	~Treasure();
	Treasure(char const*, int);

	inline int	getWorth();

};