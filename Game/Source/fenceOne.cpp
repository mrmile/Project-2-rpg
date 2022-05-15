#include "fenceOne.h"

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
#include "QuestManager.h"

#include "Defs.h"

FenceOne::FenceOne(int x, int y) : Entity(x, y)
{
	EntityHP = 1;
	EntityAP = 5;
	EntityMP = 3;
	EntityKillable = false;

	counter = 0;
	//HERE WE ADD THE ANIMATIONS WITH GIMP

	//Have the Soldiers describe a path in the screen taking into account the collisions

	fenceOne.PushBack({ 0,18,59,86 });

	position.x = x;
	position.y = y;

	collider = app->collisions->AddCollider({ position.x, position.y, 25, 56 }, Collider::Type::FENCE_ONE, (Module*)app->entity_manager);
	//entityBody = app->physics->CreateWalkingEnemyBox(position.x, position.y, 25, 10);
	FenceOne_List.add(app->physics->CreateColliderRectangle(position.x, position.y, 60, 104));

}

void FenceOne::Update(float dt)
{
	if (app->player->pauseMenu == true)
	{
		iPoint NewPosition = position;
		collider->SetPos(NewPosition.x, NewPosition.y);
		FenceOne_List.end->data->GetPosition(NewPosition.x, NewPosition.y);

	}

	if (app->player->pauseMenu == false)
	{
		FenceOne_List.end->data->GetPosition(position.x, position.y);
	}


	currentAnim = &fenceOne;

	if (app->player->baseUnlock == true && app->player->switchesPressed >= 5)
	{
		EntityHP = 0;
		if(app->questManager->mainQuestID == LOOK_FOR_THE_COMPUTER_2) app->questManager->SwitchSecondaryQuest(S_NONE);
		app->audio->ChangeMusic(MAIN_MAP_AT_NIGHT, 0.0f, 0.0f);
	}
	

}


