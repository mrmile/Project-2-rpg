#include "Walking_Enemy.h"

#include "App.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "Enemies.h"
//#include "ModuleParticles.h"
#include "Audio.h"
#include "Point.h"
#include "Input.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "Pathfinding.h"
#include "SceneForest.h"

Walking_Enemy::Walking_Enemy(int x, int y) : Enemy(x, y)
{	
	Enemy::EnemyHP = 1;
	//HERE WE ADD THE ANIMATIONS WITH GIMP
	
	//Have the Soldiers describe a path in the screen taking into account the collisions
	Walking_Enemy_Right.PushBack({64,449,16,18});
	Walking_Enemy_Right.PushBack({93,447,17,20});
	Walking_Enemy_Right.PushBack({123,449,18,18});
	Walking_Enemy_Right.PushBack({151,449,20,18});
	Walking_Enemy_Right.PushBack({181,449,20,19});
	Walking_Enemy_Right.PushBack({213,449,17,19});
	Walking_Enemy_Right.loop = true;
	Walking_Enemy_Right.speed = 0.3f;

	Walking_Enemy_Left.PushBack({1179,448,17,19});
	Walking_Enemy_Left.PushBack({1150,448,17,19});
	Walking_Enemy_Left.PushBack({1119,448,18,19});
	Walking_Enemy_Left.PushBack({1089,448,20,19});
	Walking_Enemy_Left.PushBack({1060,448,18,20});
	Walking_Enemy_Left.PushBack({1030,448,17,20});
	Walking_Enemy_Left.loop = true;
	Walking_Enemy_Left.speed = 0.3f;

	collider = app->collisions->AddCollider({ position.x, position.y, 20, 20 }, Collider::Type::ENEMY, (Module*)app->enemies);
	//ALSO NEED TO ADD THE BOX2D PHYSICS

	Walking_Enemy_List.add(app->physics->CreateWalkingEnemyBox(position.x, position.y, 20, 20));
	//Walking_Enemy_List.end->data->listener = this;

;
	
}

void Walking_Enemy::Update(float dt)
{
	//ADD THE PATHFINDING LOGIC FOR MOVEMENT
	
	if (app->player->pauseMenu == true)
	{
		iPoint NewPosition = position;
		collider->SetPos(NewPosition.x, NewPosition.y);
		Walking_Enemy_List.end->data->GetPosition(NewPosition.x, NewPosition.y);
		if (position.x < app->player->position.x) currentAnim = &Walking_Enemy_Right;
		if (position.x > app->player->position.x) currentAnim = &Walking_Enemy_Left;
		currentAnim->loop = false;
		Enemy::Update(dt);
	}
	if (app->player->pauseMenu == false)
	{
		collider->SetPos(position.x, position.y);
		Walking_Enemy_List.end->data->GetPosition(position.x, position.y);


		if (position.DistanceTo(app->player->position) < 500)
		{
			if (position.x < app->player->position.x)
			{
				currentAnim = &Walking_Enemy_Right;
				currentAnim->loop = true;
				Walking_Enemy_List.end->data->body->SetLinearVelocity({ 1.5f,0.0f });

			}
			if (position.x > app->player->position.x)
			{
				currentAnim = &Walking_Enemy_Left;
				currentAnim->loop = true;
				Walking_Enemy_List.end->data->body->SetLinearVelocity({ -1.5f,0.0f });

			}
		}
		if ((EnemyHP == 0) || (app->enemies->active == false))
		{
			app->player->score += 10;
			Walking_Enemy_List.end->data->body->DestroyFixture(Walking_Enemy_List.end->data->body->GetFixtureList());
			SetToDelete();
		}
		if (app->enemies->GoombaLoading == true)
		{
			Walking_Enemy_List.end->data->body->DestroyFixture(Walking_Enemy_List.end->data->body->GetFixtureList());
		}
		Enemy::Update(dt);
	}
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
}
