#include "NPCs4.h"

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
#include "SceneMainMap.h"
#include "Render.h"
#include "Textures.h"
#include "Log.h"
#include "ModulePhysics.h"
#include "ModuleParticles.h"

#include "Defs.h"

Npcs4::Npcs4(int x, int y) : Entity(x, y)
{
	EntityHP = 1;
	EntityAP = 5;
	EntityMP = 3;
	EntityKillable = false;

	counter = 0;
	//HERE WE ADD THE ANIMATIONS WITH GIMP

	//Have the Soldiers describe a path in the screen taking into account the collisions

	Idle_Enemy.PushBack({ 2,182,36,64 });
	Idle_Enemy.loop = true;
	Idle_Enemy.speed = 0.3f;



	position.x = x;
	position.y = y;

	offsetX = 0;
	offsetY = 0;

	collider = app->collisions->AddCollider({ position.x, position.y, 25, 56 }, Collider::Type::NPC4, (Module*)app->entity_manager);
	//entityBody = app->physics->CreateWalkingEnemyBox(position.x, position.y, 25, 10);
	NPC4_List.add(app->physics->CreateNPCbox(position.x, position.y, 25, 10));

}

void Npcs4::Update(float dt)
{
	if (app->player->pauseMenu == true)
	{
		iPoint NewPosition = position;
		collider->SetPos(NewPosition.x, NewPosition.y);
		NPC4_List.end->data->GetPosition(NewPosition.x, NewPosition.y);

		
	}

	if (app->player->pauseMenu == false)
	{
		NPC4_List.end->data->GetPosition(position.x, position.y);
		if (position.DistanceTo(app->player->position) < 60)
		{
			/*app->render->DrawRectangle2(quad, 0, 255, 0, 255, 0.0f, true);*/
			app->player->npc4Close = true;
		}
		else
		{
			app->player->npc4Close = false;
		}
	}

	currentAnim = &Idle_Enemy;



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

}