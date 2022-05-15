#ifndef __SWITCH3_H__
#define __SWITCH3_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class Switch3 : public Entity
{
public:

	Switch3(int x, int y);


	void Update(float dt) override;



private:

	Animation Red_Switch;
	Animation Green_Switch;


	int counter;

	int isActivated = false;
};

#endif 