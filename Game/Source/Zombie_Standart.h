#ifndef __ZOMBIE_STANDART_H__
#define __ZOMBIE_STANDART_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class Zombie_Standart : public Entity
{
public:
	
	Zombie_Standart(int x,int y);

	
	bool Update(float dt) override;

	void PathfindingTo(iPoint destination);
	

private:

	Animation Idle_Enemy;
	
	
	int counter;
};

#endif 