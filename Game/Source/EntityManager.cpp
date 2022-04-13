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
#include "Zombie_Standart.h"
#include "ModulePlayer.h"


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
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			if (entities[i]->position.y * 1 > (app->render->camera.y + app->win->screenSurface->h * 1) + SPAWN_MARGIN)
			{
				entities[i]->SetToDelete();
			}

		}
	}
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
				//entities[i]->texture = texture_npc;
				break;
			case EntityType::OBJECTS:
				//entities[i]->texture = texture_objects;
				break;
			case EntityType::ZOMBIE_STANDART:
				entities[i] = new Zombie_Standart(info.x,info.y);
				entities[i]->type = info.type;
				entities[i]->texture = texture_enemies;
				
				break;
			}
			
			
			break;
		}
	}
}

void EntityManager::RegisterEntitesInCombat()
{
	for (uint i = 0; i < MAX_ENTITIES; i++)
	{
		if (entities[i] != nullptr)
		{
			// Check how to select which entites are in combat (distance may cause issues depending on the position of the player and it's movements)
			// with new entity sistem we can even add into combat objects of the environment

			if (entities[i]->type != EntityType::NPC && entities[i]->type != EntityType::OBJECTS)
			{
				if (entities[i]->entityState == GameState::OutOfCombat)
				{
					ListInCombat.add(entities[i]);
					ListInCombat.At(i)->data->entityState = GameState::InCombat;
					ListInCombat.At(i)->data->entityTurn = TurnState::NONE;
				}

			}

		}
	}
	TurnManagement();
}

void EntityManager::TurnManagement()
{
	
	for (uint i = 0; i < ListInCombat.count();)
	{
		if (ListInCombat.At(i)->data->EntityHP > 0)
		{
			ListInCombat.At(i)->data->entityTurn = TurnState::StartOfTurn;
			if (ListInCombat.At(i)->data->entityTurn == TurnState::WaitTurn) i++;
			if (ListInCombat.At(i)->next == nullptr) TurnManagement();
		}
		else if(ListInCombat.At(i)->data->EntityHP <= 0)
		{
			i++;
		}
		
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
