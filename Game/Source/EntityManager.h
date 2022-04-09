#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include "Module.h"
#include "Entity.h"	
#include "List.h"
#include "Point.h"

#define MAX_ENTITIES 5000

class Entity;
class SDL_Texture;

enum class EntityType
{
	PLAYER,
	NPC,
	ZOMBIE_RUNNER,
	ZOMBIE_SPITTER,
	ZOMBIE_STANDART,
	OBJECTS,
	NONE,
};

class EntityManager : public Module
{
public:


	EntityManager(bool start_enabled = false);

	// Destructor
	virtual ~EntityManager();

	// Called before render is available
	bool Start();

	//Called before each loop iteration
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called after each loop iteration(where we draw)
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	//Function to create entites depending on the type
	bool AddEntity(EntityType type,iPoint position);

	//Function to destroy an entity
	void DestroyEntity(Entity* entity);

private:

	Entity* entities[MAX_ENTITIES] = { nullptr };

	SDL_Texture* texture;

};

#endif
