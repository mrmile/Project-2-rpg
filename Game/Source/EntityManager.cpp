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
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			//entities[i]->type = type;
			//entities[i]->position = position;
		}
	}
	return true;
}
void EntityManager::DestroyEntity(Entity* entity)
{

}