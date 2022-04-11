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


Zombie_Standart::Zombie_Standart(int x,int y) : Entity(x,y)
{	
	EntityHP = 1;
	EntityAP = 5;
	EntityMP = 3;
	//HERE WE ADD THE ANIMATIONS WITH GIMP
	
	//Have the Soldiers describe a path in the screen taking into account the collisions
	
	Idle_Enemy.PushBack({24,45,25,56});
	Idle_Enemy.loop = true;
	Idle_Enemy.speed = 0.3f;

	

	spawnPos.x = position.x;
	spawnPos.y = position.y;

	collider = app->collisions->AddCollider({ position.x, position.y, 25, 56 }, Collider::Type::ENEMY, (Module*)app->enemies);

	
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
		collider->SetPos(position.x, position.y);
		currentAnim = &Idle_Enemy;
		currentAnim->loop = true;
		//code the actual system for enemy turn implementation
		app->pathfinding->CreatePath(position, app->player->GetLastPosition());
		
		const DynArray<iPoint>* path = app->pathfinding->GetLastPath();
		for (uint i = 0; i < path->Count(); ++i)
		{
			iPoint pos = { path->At(i)->x, path->At(i)->y };
			//app->render->DrawRectangle({ pos.x,pos.y,10,10 }, 255, 0, 0, 255);
		}
		/*
		for (uint i = 0; i < EntityMP;)
		{
			iPoint NextPos = { path->At(i)->x,path->At(i)->y };

			if (position.x > NextPos.x) position.x++;
			if (position.x < NextPos.x) position.x--;
			if (position.y > NextPos.x) position.y--;
			if (position.y < NextPos.x) position.y++;

			if (NextPos == position) i++;

		}
		*/
		/*
		if (entityState == GameState::OutOfCombat)
		{
			//move normally
			collider->SetPos(position.x, position.y);
			currentAnim = &Idle_Enemy;
			currentAnim->loop = true;
		}
		if (entityState == GameState::InCombat)
		{
			if (entityTurn == TurnState::PlayerTurn)
			{
				iPoint NewPosition = position;
				collider->SetPos(NewPosition.x, NewPosition.y);
				currentAnim = &Idle_Enemy;
				currentAnim->loop = false;
				return true;
			}
			if (entityTurn == TurnState::EnemyTurn)
			{
				
				
				//code the actual system for enemy turn implementation
				app->pathfinding->CreatePath(position, app->player->position);
				const DynArray<iPoint>* path = app->pathfinding->GetLastPath();

				for (uint i = 0; i < EntityMP;)
				{
					iPoint NextPos = { path->At(i)->x,path->At(i)->y };
					
					if (position.x > NextPos.x) position.x++;
					if (position.x < NextPos.x) position.x--;
					if (position.y > NextPos.x) position.y--;
					if (position.y < NextPos.x) position.y++;

					if (NextPos == position) i++;

				}
				

			}
		}
		*/
		
		
		return true;
	}
	
}
