#ifndef __SWITCH5_H__
#define __SWITCH5_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class Switch5 : public Entity
{
public:

	Switch5(int x, int y);


	void Update(float dt) override;



private:

	Animation Red_Switch;
	Animation Green_Switch;


	int counter;

	int isActivated = false;
};

#endif 