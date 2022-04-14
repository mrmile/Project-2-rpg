#ifndef __ZOMBIE_SPITTER_H__
#define __ZOMBIE_SPITTER_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class Zombie_Spitter : public Entity
{
public:
	
	Zombie_Spitter(int x,int y);

	
	bool Update(float dt) override;

	
	

private:

	Animation Idle_Enemy;
	
	
	int counter;
};

#endif 