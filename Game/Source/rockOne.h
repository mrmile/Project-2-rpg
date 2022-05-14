#ifndef __ROCK_ONE_H__
#define __ROCK_ONE_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class RockOne : public Entity
{
public:

	RockOne(int x, int y);


	bool Update(float dt) override;



private:

	Animation Red_Switch;
	Animation Green_Switch;


	int counter;
};

#endif 