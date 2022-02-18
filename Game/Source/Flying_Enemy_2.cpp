#include "Flying_Enemy_2.h"

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

Flying_Enemy_2::Flying_Enemy_2(int x, int y) : Enemy(x, y)
{
	Enemy::EnemyHP = 1; 
	//HERE WE ADD THE ANIMATIONS WITH GIMP
	Flying_Enemy_2_Left.PushBack({ 1122,99,16,27 });
	Flying_Enemy_2_Left.PushBack({ 1102,99,16,27 });
	Flying_Enemy_2_Left.PushBack({ 1082,99,16,27 });
	Flying_Enemy_2_Left.PushBack({ 1062,99,16,27 });
	Flying_Enemy_2_Left.loop = true;
	Flying_Enemy_2_Left.speed = 0.2f;

	Flying_Enemy_2_Right.PushBack({ 126,99,16,27 });
	Flying_Enemy_2_Right.PushBack({ 146,99,16,27 });
	Flying_Enemy_2_Right.PushBack({ 166,99,16,27 });
	Flying_Enemy_2_Right.PushBack({ 186,99,16,27 });
	Flying_Enemy_2_Right.loop = true;
	Flying_Enemy_2_Right.speed = 0.2f;



	collider = app->collisions->AddCollider({ position.x, position.y, 16, 27 }, Collider::Type::ENEMY, (Module*)app->enemies);
	//ALSO NEED TO ADD THE BOX2D PHYSICS
	
	Flying_Enemy_2_List.add(app->physics->CreateFlyingEnemyBox(position.x, position.y, 16, 27));
	
	
	
}

void Flying_Enemy_2::Update(float dt)
{
	//ADD THE PATHFINDING LOGIC FOR MOVEMENT
	
	if (app->player->pauseMenu == true)
	{
		iPoint NewPosition = position;
		collider->SetPos(NewPosition.x, NewPosition.y);
		Flying_Enemy_2_List.end->data->GetPosition(NewPosition.x, NewPosition.y);
		if (position.x < app->player->position.x) currentAnim = &Flying_Enemy_2_Right;
		if (position.x > app->player->position.x) currentAnim = &Flying_Enemy_2_Left;
		currentAnim->loop = false;
		Enemy::Update(dt);
	}
	if (app->player->pauseMenu == false)
	{
		collider->SetPos(position.x, position.y);
		Flying_Enemy_2_List.end->data->GetPosition(position.x, position.y);
		if (position.DistanceTo(app->player->position) < 200)
		{
			if (position.x < app->player->position.x)
			{
				currentAnim = &Flying_Enemy_2_Right;
				currentAnim->loop = true;
				Flying_Enemy_2_List.end->data->body->SetLinearVelocity({ 0.7f,0.0f });

			}
			if (position.x > app->player->position.x)
			{
				currentAnim = &Flying_Enemy_2_Left;
				currentAnim->loop = true;
				Flying_Enemy_2_List.end->data->body->SetLinearVelocity({ -0.7f,0.0f });

			}
			if (position.y > app->player->position.y)
			{
				Flying_Enemy_2_List.end->data->body->SetLinearVelocity({ 0.0f,-0.5f });
			}
			if (position.y < app->player->position.y)
			{
				Flying_Enemy_2_List.end->data->body->SetLinearVelocity({ 0.0f,0.5f });
			}
			if (position.x < app->player->position.x && position.y > app->player->position.y)
			{
				currentAnim = &Flying_Enemy_2_Right;
				currentAnim->loop = true;
				Flying_Enemy_2_List.end->data->body->SetLinearVelocity({ 0.7f,-0.5f });

			}
			if (position.x > app->player->position.x && position.y > app->player->position.y)
			{
				currentAnim = &Flying_Enemy_2_Left;
				currentAnim->loop = true;
				Flying_Enemy_2_List.end->data->body->SetLinearVelocity({ -0.7f,-0.5f });

			}
			if (position.x < app->player->position.x && position.y < app->player->position.y)
			{
				currentAnim = &Flying_Enemy_2_Right;
				currentAnim->loop = true;
				Flying_Enemy_2_List.end->data->body->SetLinearVelocity({ 0.7f,0.5f });

			}
			if (position.x > app->player->position.x && position.y < app->player->position.y)
			{
				currentAnim = &Flying_Enemy_2_Left;
				currentAnim->loop = true;
				Flying_Enemy_2_List.end->data->body->SetLinearVelocity({ -0.7f,0.5f });

			}
		}




		if ((EnemyHP == 0) || (app->enemies->active == false))
		{
			app->player->score += 10;
			Flying_Enemy_2_List.end->data->body->DestroyFixture(Flying_Enemy_2_List.end->data->body->GetFixtureList());
			SetToDelete();
		}
		if (app->enemies->KoopaLoading == true)
		{
			Flying_Enemy_2_List.end->data->body->DestroyFixture(Flying_Enemy_2_List.end->data->body->GetFixtureList());
		}


		// Call to the base class. It must be called at the end
		// It will update the collider depending on the position
		Enemy::Update(dt);
	}

}
