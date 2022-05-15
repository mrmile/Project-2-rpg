#ifndef __ROCK_ONE_H__
#define __ROCK_ONE_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class RockOne : public Entity
{
public:

	RockOne(int x, int y);


	void Update(float dt) override;



private:

	Animation rockOne;
	
	int counter;
};

#endif 