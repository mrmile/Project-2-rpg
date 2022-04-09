#include "App.h"
#include "Entity.h"
#include "EntityManager.h"


#include "Defs.h"
#include "Log.h"


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
	return true;
}

bool EntityManager::PreUpdate()
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
bool EntityManager::Update(float dt)
{
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
			entities[i]->Update(dt);
	}
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
bool EntityManager::AddEntity(EntityType type,iPoint position)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (spawnQueue[i].type == EntityType::NONE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].startingPosition = position;
			ret = true;
			break;
		}
	}

	return ret;
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
				break;
			case EntityType::NPC:
				break;
			case EntityType::OBJECTS:
				break;
			case EntityType::ZOMBIE_STANDART:
				break;
			default:
				break;
			}
			entities[i]->texture = texture;
			
			break;
		}
	}
}