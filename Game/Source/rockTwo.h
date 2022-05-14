#ifndef __ROCK_TWO_H__
#define __ROCK_TWO__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class RockTwo : public Entity
{
public:

	RockTwo(int x, int y);


	bool Update(float dt) override;



private:

	Animation Red_Switch;
	Animation Green_Switch;


	int counter;
};

#endif 