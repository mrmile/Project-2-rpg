#ifndef __NPCS3_H__
#define __NPCS3_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class Npcs3 : public Entity
{
public:

	Npcs3(int x, int y);


	void Update(float dt) override;



private:

	Animation Idle_Enemy;


	int counter;
};

#endif 