#ifndef __SWITCH_H__
#define __SWITCH_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class Switch : public Entity
{
public:

	Switch(int x, int y);


	bool Update(float dt) override;



private:

	Animation Red_Switch;
	Animation Green_Switch;


	int counter;
};

#endif 