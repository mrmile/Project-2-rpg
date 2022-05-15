#ifndef __NPCS2_H__
#define __NPCS2_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class Npcs2 : public Entity
{
public:

	Npcs2(int x, int y);


	void Update(float dt) override;



private:

	Animation Idle_Enemy;


	int counter;
};

#endif 