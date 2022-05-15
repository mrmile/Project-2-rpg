#ifndef __NPCS4_H__
#define __NPCS4_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class Npcs4 : public Entity
{
public:

	Npcs4(int x, int y);


	void Update(float dt) override;



private:

	Animation Idle_Enemy;


	int counter;
};

#endif 