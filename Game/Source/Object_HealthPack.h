#ifndef __OBJECT_HEALTH_PACK_H__
#define __OBJECT_HEALTH_PACK_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class Object_HealthPack : public Entity
{
public:
	
	Object_HealthPack(int x,int y);

	
	bool Update(float dt) override;

	

private:

	Animation Idle_item;
};

#endif 