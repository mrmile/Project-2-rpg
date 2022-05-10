#include "Object_Grenade.h"

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

Object_Grenade::Object_Grenade(int x, int y) : Entity(x, y)
{
	EntityHP = 1;
	EntityAP = 5;
	EntityMP = 3;
	EntityKillable = false;


	Idle_item.PushBack({ 24,45,25,56 });
	Idle_item.loop = false;
	Idle_item.speed = 0.3f;



	position.x = x;
	position.y = y;

	collider = app->collisions->AddCollider({ position.x, position.y, 25, 56 }, Collider::Type::ITEM_GRENADE, (Module*)app->entity_manager);

}

bool Object_Grenade::Update(float dt)
{
	if (app->player->pauseMenu == true)
	{
		iPoint NewPosition = position;
		collider->SetPos(NewPosition.x, NewPosition.y);
		currentAnim = &Idle_item;

	}

	if (app->player->pauseMenu == false)
	{
		collider->SetPos(position.x, position.y);
		currentAnim = &Idle_item;


		if (EntityHP == 0)
		{
			SetToDelete();
		}


	}

	return true;

}