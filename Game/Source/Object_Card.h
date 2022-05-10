
#ifndef __OBJECT_CARD_H__
#define __OBJECT_CARD_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class Object_Card : public Entity
{
public:

	Object_Card(int x, int y);


	bool Update(float dt) override;



private:

	Animation Idle_item;
};

#endif 