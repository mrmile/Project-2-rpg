#ifndef __ENEMIES_H__
#define __ENEMIES_H__

#include "Module.h"
#include "Log.h"

#define MAX_ENEMIES 1000

enum class Enemy_Type
{
	NO_TYPE,
	FLYING_KOOPA,
	GOOMBA,
	SHYGUY,

};

struct EnemySpawnpoint
{
	Enemy_Type type = Enemy_Type::NO_TYPE;
	int x, y;
};


class Enemy;
struct SDL_Texture;

class Enemies : public Module
{
public:
	// Constructor
	Enemies(bool startEnabled = false);
	// Destructor
	~Enemies();

	// Called when the module is activated
	// Loads the necessary textures for the enemies
	bool Start() override;

	// Called at the beginning of the application loop
	// Removes all enemies pending to delete
	bool PreUpdate() override;

	// Called at the middle of the application loop
	// Handles all enemies logic and spawning/despawning
	bool Update(float dt) override;

	// Called at the end of the application loop
	// Iterates all the enemies and draws them
	bool PostUpdate() override;

	// Called on application exit
	// Destroys all active enemies left in the array
	bool CleanUp() override;

	// Called when an enemi collider hits another collider
	// The enemy is destroyed and an explosion particle is fired
	void OnCollision(Collider* c1, Collider* c2) override;

	// Add an enemy into the queue to be spawned later
	bool AddEnemy(Enemy_Type type, int x, int y);

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;

	// Iterates the queue and checks for camera position
	void HandleEnemiesSpawn();

	// Destroys any enemies that have moved outside the camera limits
	void HandleEnemiesDespawn();

	bool AlreadySpawned = false;

	bool KoopaLoading = false;
	bool GoombaLoading = false;


	// The audio fx for destroying an enemy
	int enemyDestroyedFx = 0;

private:
	// Spawns a new enemy using the data from the queue
	void SpawnEnemy(const EnemySpawnpoint& info);

private:
	// A queue with all spawn points information
	EnemySpawnpoint spawnQueue[MAX_ENEMIES];

	Enemy_Type HelperQueue[MAX_ENEMIES];

	// All spawned enemies in the scene
	Enemy* enemies[MAX_ENEMIES] = { nullptr };

	// The enemies sprite sheet
	SDL_Texture* texture = nullptr;
};

#endif // __MODULE_ENEMIES_H__
