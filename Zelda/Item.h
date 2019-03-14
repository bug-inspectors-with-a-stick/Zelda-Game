#pragma once

class Item
{
protected:

	char* name;

public:

	Item();
	~Item();

	char* getItemName();
	virtual int getWorth() = 0;


};