#pragma once

class Item
{
protected:

	char* name;

public:

	Item();
	~Item();

	inline char* getItemName();
	inline virtual int getWorth() = 0;


};