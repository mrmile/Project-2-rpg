#ifndef __SWITCH4_H__
#define __SWITCH4_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class Switch4 : public Entity
{
public:

	Switch4(int x, int y);


	void Update(float dt) override;



private:

	Animation Red_Switch;
	Animation Green_Switch;


	int counter;

	int isActivated = false;
};

#endif 