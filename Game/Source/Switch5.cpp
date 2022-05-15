#include "Switch5.h"

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
#include "InventoryMenu.h"

#include "Defs.h"

Switch5::Switch5(int x, int y) : Entity(x, y)
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

	isActivated = false;

	counter = 0;

	position.x = x;
	position.y = y;

	collider = app->collisions->AddCollider({ position.x, position.y, 25, 56 }, Collider::Type::SWITCH_KEY, (Module*)app->entity_manager);
	//entityBody = app->physics->CreateWalkingEnemyBox(position.x, position.y, 25, 10);
	Switch_List5.add(app->physics->CreateColliderRectangle(position.x, position.y, 20, 50));

}

void Switch5::Update(float dt)
{
	counter++;

	if (app->player->pauseMenu == true)
	{
		iPoint NewPosition = position;
		collider->SetPos(NewPosition.x, NewPosition.y);
		Switch_List5.end->data->GetPosition(NewPosition.x, NewPosition.y);

	}

	if (app->player->pauseMenu == false && app->inventoryMenu->showInventory == false)
	{
		Switch_List5.end->data->GetPosition(position.x, position.y);
		if (position.DistanceTo(app->player->position) < 65)
		{
			if (app->input->keys[SDL_SCANCODE_X] == KeyState::KEY_DOWN && app->player->baseUnlock == true && isActivated == false)
			{
				app->player->switchesPressed++;
				app->audio->PlayFx(app->player->switchOkFx);
				isActivated = true;
				app->player->switch5Ok = true;
			}
		}

		if (isActivated == false)
		{
			currentAnim = &Red_Switch;
		}
		if (isActivated == true)
		{
			currentAnim = &Green_Switch;
		}
	}

	

}