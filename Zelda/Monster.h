#pragma once

class Monster
{
private:
	char* name;
	bool  is_Alive;
	Item* killing_weapon;


public:

	Monster();
	~Monster();
	Monster(char const*, Item*);

	inline Item* 	getKillingWeapon();
	inline void		setKillingWeapon(Item*);
	inline bool		getLivingState();
	inline void		setLivingState(bool);
	inline char*	getMonsterName();

};
