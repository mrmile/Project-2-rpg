/*
#include "Item.h"

#include "App.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "EntityManager.h"
//#include "ModuleParticles.h"
#include "Audio.h"
#include "Point.h"
#include "DynArray.h"
#include "Input.h"
#include "Map.h"
#include "Pathfinding.h"
#include "SceneMainMap.h"
#include "Render.h"
#include "Textures.h"
#include "Log.h"
#include "ModulePhysics.h"
#include "ModuleParticles.h"

#include "Defs.h"

Item::Item(int x, int y,ObjectType object_type,ItemType item_type) : Entity(x, y)
{
	EntityHP = 1;

	position.x = x;
	position.y = y;

	objectType = object_type;
	itemType = item_type;
	//collider = app->collisions->AddCollider({ position.x, position.y - 56, 25, 56 }, Collider::Type::ITEM, (Module*)app->entity_manager);

}

bool Item::Update(float dt)
{
	switch (objectType)
	{
	case ObjectType::NONE:
		//NO ANIM PUSHBACK FOR DRAWING
		break;
	case ObjectType::WEAPON:
		break;
	case ObjectType::ITEM:
		switch (itemType)
		{
		case ItemType::NONE:
			break;
		case ItemType::FOOD:
			//FOOD ANIM
			break;
		case ItemType::HEALTH_PACK:
			//HEALTH PACK ANIM
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
*/