#include "App.h"
#include "EntityManager.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Window.h"
#include "ModuleCollisions.h"
#include "Collider.h"
#include "GameManager.h"
#include "Entity.h"
#include "ModulePlayer.h"


#include "Zombie_Standart.h"
#include "NPCs.h"

#define SPAWN_MARGIN 500

EntityManager::EntityManager(bool start_enabled) : Module(start_enabled)
{
	name.Create("entities");
	for (uint i = 0; i < MAX_ENTITIES; i++)
	{
		entities[i] = nullptr;

	}
}
EntityManager::~EntityManager()
{

}

bool EntityManager::Start()
{
	texture_enemies = app->tex->Load("Assets/textures/Enemies/zombie_farmer.png"); 
	
	return true;
}

bool EntityManager::PreUpdate()
{
	
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr && entities[i]->pendingToDelete)
		{
			delete entities[i];
			entities[i] = nullptr;
		}
	}
	
	return true;
}
bool EntityManager::Update(float dt)
{
	HandleEntitiesSpawn();

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
			entities[i]->Update(dt);
	}

	HandleEntitiesDespawn();
	return true;
}

bool EntityManager::PostUpdate()
{
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
			entities[i]->Draw();
	}

	return true;
}
bool EntityManager::CleanUp()
{
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			delete entities[i];
			entities[i] = nullptr;
		}
	}

	return true;
}
bool EntityManager::AddEntity(EntityType type,int x,int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (spawnQueue[i].type == EntityType::NONE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void EntityManager::HandleEntitiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (spawnQueue[i].type != EntityType::NONE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if ((spawnQueue[i].x * 1 < app->render->camera.x + (app->render->camera.w * 1) + SPAWN_MARGIN) || (spawnQueue[i].x * 1 > app->render->camera.x - (app->render->camera.w * 1) - SPAWN_MARGIN) || (spawnQueue[i].y * 1 < app->render->camera.y - (app->render->camera.h * 1) - SPAWN_MARGIN))
			{
				SpawnEntity(spawnQueue[i]);
				spawnQueue[i].type = EntityType::NONE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void EntityManager::HandleEntitiesDespawn()
{
	
}

void EntityManager::SpawnEntity(const EntitySpawnPoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{

		if (entities[i] == nullptr)
		{
			switch (info.type)
			{
			case EntityType::PLAYER:
				//entities[i]->texture = texture_player;
				break;
			case EntityType::NPC:
				entities[i] = new Npcs(info.x, info.y);
				entities[i]->id = i;
				entities[i]->type = info.type;
				//entities[i]->texture = texture_npc;
				break;
			case EntityType::OBJECTS:
				//entities[i]->texture = texture_objects;
				break;
			case EntityType::ZOMBIE_STANDART:
				entities[i] = new Zombie_Standart(info.x,info.y);
				entities[i]->id = i;
				entities[i]->type = info.type;
				entities[i]->texture = texture_enemies;
				
				break;
			}
			
			
			break;
		}
	}
}

void EntityManager::RegisterEntitesInCombat(int id)
{

	if (entities[id]->entityState == GameState::OutOfCombat)
	{

		ListInCombat.add(entities[id]);
		ListInCombat.At(x)->data->entityTurn = TurnState::NONE; x++;
	
	}

}

void EntityManager::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr && entities[i]->GetColldier() == c1)
		{
			entities[i]->OnCollision(c2); //Notify the entity of a collision
			break;
		}
	}

}
