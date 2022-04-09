#ifndef __ZOMBIE_STANDART_H__
#define __ZOMBIE_STANDART_H__

#include "Entity.h"
#include "Point.h"


class Zombie_Standart : public Entity
{
public:
	
	Zombie_Standart(iPoint position);

	
	bool Update(float dt) override;

	

private:
	
	
	
	Animation Idle_Enemy;
	

	int counter;
};

#endif 