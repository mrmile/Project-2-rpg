#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include "Module.h"
#include "List.h"
#include "Point.h"

#define MAX_ENTITIES 5000

class Entity;
struct SDL_Texture;

class Item;

enum class EntityType
{
	NONE,
	PLAYER,
	NPC,
	NPC2,
	NPC3,
	NPC4,
	ZOMBIE_RUNNER,
	ZOMBIE_SPITTER,
	ZOMBIE_STANDART,
	OBJECT_FOOD,
	OBJECT_HEALTH_PACK,
};

struct EntitySpawnPoint
{
	EntityType type = EntityType::NONE;
	int x, y;
};
struct EntityHelper //ADD ANYTHING NEEDED FOR THE ENTITIES TO WORK used in the Load function as we want to cleanup the entities list any time we use it
{
	EntityType type;
	iPoint position;
	int hp;
};
class EntityManager : public Module
{
public:


	EntityManager(bool start_enabled = true);

	// Destructor
	~EntityManager();

	// Called before render is available
	bool Start();

	//Called before each loop iteration
	bool PreUpdate() override;

	// Called each loop iteration
	bool Update(float dt) override;

	// Called after each loop iteration(where we draw)
	bool PostUpdate() override;

	// Called before quitting
	bool CleanUp() override;

	// Iterates the queue and checks for camera position
	void HandleEntitiesSpawn();

	// Destroys any enemies that have moved outside the camera limits
	void HandleEntitiesDespawn();


	//Function to create entites depending on the type
	bool AddEntity(EntityType type,int x, int y);


	//Check which entites are in combat
	void RegisterEntitesInCombat(Entity* entity);

	
	//List that will be used for turn system
	List<Entity*> ListInCombat; 

	//Collision management
	void OnCollision(Collider* c1, Collider* c2);

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;
public:

	int idForCombat;

	int x = 0;

private:

	void SpawnEntity(const EntitySpawnPoint& info);


	// A queue with all spawn points information
	EntitySpawnPoint spawnQueue[MAX_ENTITIES];
	Entity* entities[MAX_ENTITIES] = { nullptr };
	SDL_Texture* texture_enemies = nullptr;
	SDL_Texture* texture_npcs = nullptr;

	EntityHelper HelperQueue[MAX_ENTITIES];

	//SDL_Texture* texture_player = nullptr;
	//SDL_Texture* texture_npc = nullptr;
	//SDL_Texture* texture_objects = nullptr;

};

#endif
