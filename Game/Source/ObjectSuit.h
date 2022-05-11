#ifndef __OBJECT_SUIT_H__
#define __OBJECT_SUIT_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class Object_Suit : public Entity
{
public:

	Object_Suit(int x, int y);


	bool Update(float dt) override;



private:

	Animation Idle_item;
};

#endif 