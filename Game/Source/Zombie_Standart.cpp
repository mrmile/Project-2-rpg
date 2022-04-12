#include "Zombie_Standart.h"

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

#include <iostream>

using namespace std;

Zombie_Standart::Zombie_Standart(int x,int y) : Entity(x,y)
{	
	EntityHP = 1;
	EntityAP = 5;
	EntityMP = 3;
	entityState = GameState::InCombat;
	//HERE WE ADD THE ANIMATIONS WITH GIMP
	
	//Have the Soldiers describe a path in the screen taking into account the collisions
	
	Idle_Enemy.PushBack({24,45,25,56});
	Idle_Enemy.loop = true;
	Idle_Enemy.speed = 0.3f;

	

	spawnPos.x = position.x;
	spawnPos.y = position.y;

	collider = app->collisions->AddCollider({ position.x, position.y, 25, 56 }, Collider::Type::ENEMY, (Module*)app->enemies);
	entityBody = app->physics->CreateWalkingEnemyBox(position.x, position.y, 25, 10);
	
}

bool Zombie_Standart::Update(float dt)
{
	//ADD THE PATHFINDING LOGIC FOR MOVEMENT
	
	if (app->player->pauseMenu == true)
	{
		iPoint NewPosition = position;
		collider->SetPos(NewPosition.x, NewPosition.y);
		currentAnim = &Idle_Enemy;
		currentAnim->loop = false;
		return true;
	}
	if (app->player->pauseMenu == false)
	{
		const DynArray<iPoint>* path;

		if (entityState == GameState::OutOfCombat)
		{
			//move normally
			collider->SetPos(position.x, position.y);
			entityBody->GetPosition(position.x, position.y);
			currentAnim = &Idle_Enemy;
			currentAnim->loop = true;

			if (position.x > app->player->position.x) entityBody->body->SetLinearVelocity({ -0.5f, 0.0f });
			if (position.x < app->player->position.x) entityBody->body->SetLinearVelocity({ 0.5f, 0.0f });
			if (position.y > app->player->position.y) entityBody->body->SetLinearVelocity({ 0.0f, -0.5f });
			if (position.y < app->player->position.y) entityBody->body->SetLinearVelocity({ 0.0f, 0.5f });

		}
		
		if (entityState == GameState::InCombat)
		{
			
			if (EntityHP > 0)
			{
				if (entityTurn == TurnState::StartOfTurn)
				{
					iPoint NewPosition = position;
					collider->SetPos(NewPosition.x, NewPosition.y);
					currentAnim = &Idle_Enemy;
					currentAnim->loop = false;
					app->pathfinding->CreatePath(app->map->WorldToMap(position.x,position.y),app->map->WorldToMap(app->player->position.x,app->player->position.y));
					entityTurn = TurnState::MidOfTurn;

				}
				if (entityTurn == TurnState::MidOfTurn)
				{
					path = app->pathfinding->GetLastPath();
					
					for (int i = 0; i < path->Count(); i++)
					{
						collider->SetPos(position.x, position.y);
						entityBody->GetPosition(position.x, position.y);
						currentAnim = &Idle_Enemy;
						currentAnim->loop = true;

						iPoint NextPos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
						app->render->DrawRectangle({ NextPos.x,NextPos.y,10,10 }, 255, 0, 0, 255);

						if (NextPos.x > position.x) entityBody->body->SetLinearVelocity({ -0.5f, 0.0f });
						if (NextPos.x < position.x) entityBody->body->SetLinearVelocity({ 0.5f, 0.0f });
						if (NextPos.y > position.y) entityBody->body->SetLinearVelocity({ 0.0f, -0.5f });
						if (NextPos.y < position.y) entityBody->body->SetLinearVelocity({ 0.0f, 0.5f });

						if (NextPos == position) counter++;

						if (counter == EntityMP) entityTurn = TurnState::FinishTurn;

					}

				}
				if (entityTurn == TurnState::FinishTurn)
				{
					//Change turn from enemy to player turn still have to develop a way to do it correctly
					collider->SetPos(position.x, position.y);
					entityBody->GetPosition(position.x, position.y);
					currentAnim = &Idle_Enemy;
					currentAnim->loop = true;

				}

				
			}
				

			if (EntityHP == 0)
			{
				SetToDelete();
			}
			
		}
		
		
		
		return true;
	}
	
}
