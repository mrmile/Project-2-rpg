
#ifndef __OBJECT_DEFAULTGUN_H__
#define __OBJECT_DEFAULTGUN_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class Object_DefaultGun : public Entity
{
public:
	
	Object_DefaultGun(int x,int y);

	
	bool Update(float dt) override;

	

private:

	Animation Idle_item;
};

#endif 
