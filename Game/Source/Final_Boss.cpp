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

	//fenceOne.PushBack({ 180, 1263, 180, 180 });

	
	fenceOne.PushBack({ 180, 4512, 180, 180 });
	fenceOne.PushBack({ 361, 4512, 180, 180 });
	fenceOne.PushBack({ 541, 4512, 180, 180 });
	fenceOne.PushBack({ 722, 4512, 180, 180 });
	fenceOne.PushBack({ 902, 4512, 180, 180 });
	fenceOne.PushBack({ 1083, 4512, 180, 180 });
	fenceOne.PushBack({ 1263, 4512, 180, 180 });
	fenceOne.PushBack({ 1444, 4512, 180, 180 });
	fenceOne.PushBack({ 1624, 4512, 180, 180 });
	fenceOne.PushBack({ 1805, 4512, 180, 180 });
	fenceOne.PushBack({ 1985, 4512, 180, 180 });
	fenceOne.PushBack({ 2166, 4512, 180, 180 });
	fenceOne.PushBack({ 2346, 4512, 180, 180 });
	fenceOne.PushBack({ 2527, 4512, 180, 180 });
	fenceOne.PushBack({ 2707, 4512, 180, 180 });
	fenceOne.PushBack({ 2888, 4512, 180, 180 });
	fenceOne.PushBack({ 3068, 4512, 180, 180 });
	fenceOne.PushBack({ 3249, 4512, 180, 180 });
	fenceOne.loop = true;
	fenceOne.speed = 0.15f;

	fenceTwo.PushBack({ 0, 6144, 180, 180 });
	fenceTwo.loop = true;
	fenceTwo.speed = 0.15f;

	fenceThree.PushBack({ 180, 1263, 180, 180 });
	fenceThree.PushBack({ 361, 1263, 180, 180 });
	fenceThree.PushBack({ 541, 1263, 180, 180 });
	fenceThree.PushBack({ 722, 1263, 180, 180 });
	fenceThree.PushBack({ 902, 1263, 180, 180 });
	fenceThree.PushBack({ 1083, 1263, 180, 180 });
	fenceThree.PushBack({ 1263, 1263, 180, 180 });
	fenceThree.PushBack({ 1444, 1263, 180, 180 });
	fenceThree.PushBack({ 1624, 1263, 180, 180 });
	fenceThree.PushBack({ 1805, 1263, 180, 180 });
	fenceThree.PushBack({ 1985, 1263, 180, 180 });
	fenceThree.PushBack({ 2166, 1263, 180, 180 });
	fenceThree.PushBack({ 2346, 1263, 180, 180 });
	fenceThree.PushBack({ 2527, 1263, 180, 180 });
	fenceThree.PushBack({ 2707, 1263, 180, 180 });
	fenceThree.PushBack({ 2888, 1263, 180, 180 });
	fenceThree.PushBack({ 3068, 1263, 180, 180 });
	fenceThree.PushBack({ 3249, 1263, 180, 180 });
	fenceThree.PushBack({ 3429, 1263, 180, 180 });
	fenceThree.PushBack({ 3610, 1263, 180, 180 });
	fenceThree.PushBack({ 3790, 1263, 180, 180 });
	fenceThree.PushBack({ 3971, 1263, 180, 180 });
	fenceThree.PushBack({ 4151, 1263, 180, 180 });
	fenceThree.PushBack({ 4332, 1263, 180, 180 });
	fenceThree.PushBack({ 4512, 1263, 180, 180 });
	fenceThree.PushBack({ 4693, 1263, 180, 180 });
	fenceThree.PushBack({ 4873, 1263, 180, 180 });
	fenceThree.PushBack({ 5053, 1263, 180, 180 });
	fenceThree.PushBack({ 5234, 1263, 180, 180 });
	fenceThree.PushBack({ 5414, 1263, 180, 180 });
	fenceThree.PushBack({ 5595, 1263, 180, 180 });
	fenceThree.loop = false;
	fenceThree.speed = 0.15f;

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

		if (currentAnim != &fenceTwo)
		{
			//idleDownAnim_Enemy1.Reset();
			currentAnim = &fenceTwo;
		}
	}

	if (app->player->pauseMenu == false)
	{
		FinalBoss_List.end->data->GetPosition(position.x, position.y);

		if (app->player->activateFinalBoss == true)
		{
			//app->player->finalBossPhaseCounter++;
			counter++;

			if (app->player->finalBossPhaseCounter <= 240)
			{
				FinalBoss_List.end->data->body->SetLinearVelocity({ -0.0f, 1.0f });

				if (currentAnim != &fenceOne)
				{
					//downWalkAnim_Enemy1.Reset();
					currentAnim = &fenceOne;
				}
			}
			if (app->player->finalBossPhaseCounter > 240)
			{
				FinalBoss_List.end->data->body->SetLinearVelocity({ 0.0f, 0.0f });

				if (currentAnim != &fenceTwo)
				{
					//idleDownAnim_Enemy1.Reset();
					currentAnim = &fenceTwo;
				}
			}

			if (app->player->finalBossPlayerStrikes < 5 && app->player->finalBossPhaseCounter >= 6186 + 180)
			{
				if (currentAnim != &fenceThree)
				{
					//downDieAnim_Enemy1.Reset();
					currentAnim = &fenceThree;
				}
			}

			currentAnim->Update();
		}
	}
	//currentAnim = &fenceOne;
}
