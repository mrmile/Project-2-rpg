
#ifndef __OBJECT_GRENADE_H__
#define __OBJECT_GRENADE_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class Object_Grenade : public Entity
{
public:

	Object_Grenade(int x, int y);


	bool Update(float dt) override;



private:

	Animation Idle_item;
};

#endif 