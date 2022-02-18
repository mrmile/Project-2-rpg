#include "Flying_Enemy.h"

#include "App.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "Enemies.h"
//#include "ModuleParticles.h"
#include "Audio.h"
#include "Point.h"
#include "Input.h"
#include "Map.h"
#include "Pathfinding.h"
#include "ModulePhysics.h"
#include "SceneForest.h"

Flying_Enemy::Flying_Enemy(int x, int y) : Enemy(x, y)
{
	Enemy::EnemyHP = 1;
	//HERE WE ADD THE ANIMATIONS WITH GIMP
	Flying_Enemy_Left.PushBack({890,248,38,35});
	Flying_Enemy_Left.PushBack({841,248,38,35});
	Flying_Enemy_Left.PushBack({791,248,38,35});
	Flying_Enemy_Left.PushBack({741,248,38,35});
	Flying_Enemy_Left.PushBack({700,248,38,35});
	Flying_Enemy_Left.loop = true;
	Flying_Enemy_Left.speed = 0.2f;

	Flying_Enemy_Right.PushBack({334,248,38,35});
	Flying_Enemy_Right.PushBack({381,248,38,35});
	Flying_Enemy_Right.PushBack({431,248,38,35});
	Flying_Enemy_Right.PushBack({482,248,38,43});
	Flying_Enemy_Right.PushBack({522,248,38,35});
	Flying_Enemy_Right.loop = true;
	Flying_Enemy_Right.speed = 0.2f;

	
	spawnPos.x = position.x;
	spawnPos.y = position.y;

	collider = app->collisions->AddCollider({ position.x, position.y, 38, 35 }, Collider::Type::ENEMY, (Module*)app->enemies);
	
	Flying_Enemy_List.add(app->physics->CreateFlyingEnemyBox(position.x, position.y, 38, 35));
	
	startingKoopaPosition = spawnPos;

	
}

void Flying_Enemy::Update(float dt)
{
	//ADD THE PATHFINDING LOGIC FOR MOVEMENT
	
	
	if (app->player->pauseMenu == true)
	{
		iPoint NewPosition = position;
		collider->SetPos(NewPosition.x, NewPosition.y);
		Flying_Enemy_List.end->data->GetPosition(NewPosition.x, NewPosition.y);
		if (position.x < app->player->position.x) currentAnim = &Flying_Enemy_Right;
		if (position.x > app->player->position.x) currentAnim = &Flying_Enemy_Left;
		currentAnim->loop = false;
		Enemy::Update(dt);
	}
	if (app->player->pauseMenu == false)
	{
		FlyingTimer++;
		Flying_Enemy_List.end->data->GetPosition(position.x, position.y);

		collider->SetPos(position.x, position.y);
		if (position.x < app->player->position.x)
		{
			currentAnim = &Flying_Enemy_Right;
			currentAnim->loop = true;

		}
		if (position.x > app->player->position.x)
		{
			currentAnim = &Flying_Enemy_Left;
			currentAnim->loop = true;

		}
		if (FlyingTimer >= 0 && FlyingTimer < 120)
		{
			Flying_Enemy_List.end->data->body->SetLinearVelocity({ 0.0f,-1.0f });
		}
		if (FlyingTimer >= 120 && FlyingTimer < 240)
		{
			Flying_Enemy_List.end->data->body->SetLinearVelocity({ 0.0f,1.0f });
		}

		if (FlyingTimer == 240)
		{
			FlyingTimer = 0;
		}




		if ((EnemyHP == 0) || (app->enemies->active == false))
		{
			app->player->score += 10;
			Flying_Enemy_List.end->data->body->DestroyFixture(Flying_Enemy_List.end->data->body->GetFixtureList());
			SetToDelete();
		}
		if (app->enemies->KoopaLoading == true)
		{
			Flying_Enemy_List.end->data->body->DestroyFixture(Flying_Enemy_List.end->data->body->GetFixtureList());
		}

		// Call to the base class. It must be called at the end
		// It will update the collider depending on the position
		Enemy::Update(dt);
	}
}
