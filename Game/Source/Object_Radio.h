#ifndef __OBJECT_RADIO_H__
#define __OBJECT_RADIO_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class Object_Radio : public Entity
{
public:
	
	Object_Radio(int x,int y);

	
	bool Update(float dt) override;

	

private:

	Animation Idle_item;
};

#endif 