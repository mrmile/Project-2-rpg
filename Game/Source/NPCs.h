#ifndef __NPCS_H__
#define __NPCS_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class Npcs : public Entity
{
public:
	
	Npcs(int x,int y);

	
	bool Update(float dt) override;

	

private:

	Animation Idle_Enemy;
	
	
	int counter;
};

#endif 