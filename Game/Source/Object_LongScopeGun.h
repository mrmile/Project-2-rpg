#ifndef __OBJECT_LONGSCOPEGUN_H__
#define __OBJECT_LONGSCOPEGUN_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class Object_LongScopeGun : public Entity
{
public:
	
	Object_LongScopeGun(int x,int y);

	
	bool Update(float dt) override;

	

private:

	Animation Idle_item;
};

#endif 