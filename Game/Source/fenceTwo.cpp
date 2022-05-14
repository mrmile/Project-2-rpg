#include "fenceTwo.h"

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

FenceTwo::FenceTwo(int x, int y) : Entity(x, y)
{
	EntityHP = 1;
	EntityAP = 5;
	EntityMP = 3;
	EntityKillable = false;

	counter = 0;
	//HERE WE ADD THE ANIMATIONS WITH GIMP

	//Have the Soldiers describe a path in the screen taking into account the collisions

	Red_Switch.PushBack({ 0,0,32,60 });
	Red_Switch.loop = true;
	Red_Switch.speed = 0.3f;

	Green_Switch.PushBack({ 89,0,32,60 });
	Green_Switch.loop = true;
	Green_Switch.speed = 0.3f;



	position.x = x;
	position.y = y;

	collider = app->collisions->AddCollider({ position.x, position.y, 25, 56 }, Collider::Type::FENCE_TWO, (Module*)app->entity_manager);
	//entityBody = app->physics->CreateWalkingEnemyBox(position.x, position.y, 25, 10);
	FenceTwo_List.add(app->physics->CreateColliderRectangle(position.x, position.y, 20, 50));

}

bool FenceTwo::Update(float dt)
{
	if (app->player->pauseMenu == true)
	{
		iPoint NewPosition = position;
		collider->SetPos(NewPosition.x, NewPosition.y);
		FenceTwo_List.end->data->GetPosition(NewPosition.x, NewPosition.y);

		return true;
	}

	if (app->player->pauseMenu == false)
	{
		FenceTwo_List.end->data->GetPosition(position.x, position.y);
	}


	currentAnim = &Green_Switch;


	//ADD THE PATHFINDING LOGIC FOR MOVEMENT
	/*
	if (app->player->pauseMenu == true)
	{
		iPoint NewPosition = position;
		collider->SetPos(NewPosition.x, NewPosition.y);
		entityBody->GetPosition(NewPosition.x, NewPosition.y);
		currentAnim = &Idle_Enemy;
		currentAnim->loop = false;

		return true;
	}
	if (app->player->pauseMenu == false)
	{
		collider->SetPos(position.x, position.y);
		entityBody->GetPosition(position.x, position.y);
		currentAnim = &Idle_Enemy;
		currentAnim->loop = false;

	}
	*/
	return true;

}