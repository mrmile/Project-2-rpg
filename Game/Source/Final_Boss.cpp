#include "Final_Boss.h"

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
#include "QuestManager.h"
#include "InventoryMenu.h"

#include "Defs.h"

Final_Boss::Final_Boss(int x, int y) : Entity(x, y)
{
	EntityHP = 1;
	EntityAP = 5;
	EntityMP = 3;
	EntityKillable = false;

	counter = 0;
	//HERE WE ADD THE ANIMATIONS WITH GIMP

	//Have the Soldiers describe a path in the screen taking into account the collisions

	fenceOne.PushBack({ 180, 1263, 180, 180 });

	position.x = x;
	position.y = y;

	offsetX = 0;
	offsetY = 0;

	collider = app->collisions->AddCollider({ position.x, position.y, 25, 56 }, Collider::Type::FENCE_ONE, (Module*)app->entity_manager);
	//entityBody = app->physics->CreateWalkingEnemyBox(position.x, position.y, 25, 10);
	FinalBoss_List.add(app->physics->CreateColliderRectangle(position.x, position.y, 60, 104));

}

void Final_Boss::Update(float dt)
{
	if (app->player->pauseMenu == true)
	{
		iPoint NewPosition = position;
		collider->SetPos(NewPosition.x, NewPosition.y);
		FinalBoss_List.end->data->GetPosition(NewPosition.x, NewPosition.y);

	}

	if (app->player->pauseMenu == false)
	{
		FinalBoss_List.end->data->GetPosition(position.x, position.y);
	}


	currentAnim = &fenceOne;
}
