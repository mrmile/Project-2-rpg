#include "Zombie_Standart.h"

#include "App.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "EntityManager.h"
//#include "ModuleParticles.h"
#include "Audio.h"
#include "Point.h"
#include "Input.h"
#include "Map.h"
#include "Pathfinding.h"
#include "SceneMainMap.h"
#include "Log.h"


Zombie_Standart::Zombie_Standart(int x,int y) : Entity(x,y)
{	
	EntityHP = 1;
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
		LOG("ESTA FUNCIONANDO");
		return true;
	}
	if (app->player->pauseMenu == false)
	{
		collider->SetPos(position.x, position.y);
		LOG("ESTA FUNCIONANDO");
		currentAnim = &Idle_Enemy;
		currentAnim->loop = true;
		
		return true;
	}
	
}
