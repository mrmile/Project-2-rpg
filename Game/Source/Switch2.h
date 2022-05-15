#ifndef __SWITCH2_H__
#define __SWITCH2_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class Switch2 : public Entity
{
public:

	Switch2(int x, int y);


	void Update(float dt) override;



private:

	Animation Red_Switch;
	Animation Green_Switch;


	int counter;

	int isActivated = false;
};

#endif 