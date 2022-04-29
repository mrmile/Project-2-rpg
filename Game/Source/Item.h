#ifndef __ITEM_H__
#define __ITEM_H__

#include "Entity.h"
#include "Point.h"

enum class ObjectType
{
	NONE,
	WEAPON,
	ITEM,
};
enum class ItemType
{
	NONE,
	FOOD,
	HEALTH_PACK,

};

class Item : public Entity
{
public:
	Item(int x, int y,ObjectType object_type,ItemType item_type);

	bool Update(float dt) override;

	ObjectType objectType;
	ItemType itemType;

};

#endif //__COLLIDER_H__

