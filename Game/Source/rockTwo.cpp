#include "rockTwo.h"
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

RockTwo::RockTwo(int x, int y) : Entity(x, y)
{
	EntityHP = 1;
	EntityAP = 5;
	EntityMP = 3;
	EntityKillable = false;

	counter = 0;
	//HERE WE ADD THE ANIMATIONS WITH GIMP

	//Have the Soldiers describe a path in the screen taking into account the collisions

	rockTwo.PushBack({ 0,26,74,90 });

	position.x = x;
	position.y = y;

	collider = app->collisions->AddCollider({ position.x, position.y, 25, 56 }, Collider::Type::ROCK_TWO, (Module*)app->entity_manager);
	//entityBody = app->physics->CreateWalkingEnemyBox(position.x, position.y, 25, 10);
	RockTwo_List.add(app->physics->CreateColliderRectangle(position.x, position.y, 74, 90));

}

void RockTwo::Update(float dt)
{
	if (app->player->pauseMenu == true)
	{
		iPoint NewPosition = position;
		collider->SetPos(NewPosition.x, NewPosition.y);
		RockTwo_List.end->data->GetPosition(NewPosition.x, NewPosition.y);

	}

	if (app->player->pauseMenu == false)
	{
		RockTwo_List.end->data->GetPosition(position.x, position.y);
	}


	currentAnim = &rockTwo;

	if (app->player->rock2Removed == true)
	{
		//RockTwo_List.end->data->body->DestroyFixture(RockTwo_List.end->data->body->GetFixtureList());
		RockTwo_List.end->data->body->SetTransform({ 0,0 }, 0);
		SetToDelete();
	}


}