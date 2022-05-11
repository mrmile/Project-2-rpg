#ifndef __OBJECT_KNIFE_H__
#define __OBJECT_KNIFE_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class Object_Knife : public Entity
{
public:

	Object_Knife(int x, int y);


	bool Update(float dt) override;



private:

	Animation Idle_item;
};

#endif 