#pragma once

class Princess
{
private:
	bool is_Alive;
	bool along; //if princess is along with you

public:
	Princess();
	~Princess();

	inline bool	 getAlongState();
	inline void	 setAlongState(bool);
	inline bool	 getLivingState();
	inline void	 setLivingState(bool);
};