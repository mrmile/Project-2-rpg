#ifndef __OBJECT_SHORTSCOPEGUN_H__
#define __OBJECT_SHORTSCOPEGUN_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class Object_ShortScopeGun : public Entity
{
public:
	
	Object_ShortScopeGun(int x,int y);

	
	bool Update(float dt) override;

	

private:

	Animation Idle_item;
};

#endif 