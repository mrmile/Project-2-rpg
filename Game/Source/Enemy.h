#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Module.h"
#include "Point.h"
#include "Animation.h"
#include "List.h"

struct SDL_Texture;
struct Collider;

class Enemy
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	//Enemy(bool startEnabled) {};
	Enemy(int x, int y);
	//Enemy();
	// Destructor
	virtual ~Enemy();

	// Returns the enemy's collider
	const Collider* GetCollider() const;

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update(float dt);

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Collision response
	virtual void OnCollision(Collider* c2);

	//Collision for the boss
	//virtual void OnCollisionOther(Collider*c1,Collider* c2);

	// Sets flag for deletion and for the collider aswell
	virtual void SetToDelete();

public:
	// The current position in the world
	iPoint  position;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

	//speedEnemy
	int EnemySpeedX;
	int EnemySpeedY;
	//EnemyHits
	int EnemyHP;
	//BossHits

	//LIST OF ENEMY BODIES
	List<PhysBody*> Flying_Enemy_List;
	List<PhysBody*> Flying_Enemy_2_List;
	List<PhysBody*> Walking_Enemy_List;
	bool enemyHit = false;
	int EnemyCounter = 0;

	int FlyingTimer = 0;
	
	iPoint startingKoopaPosition;
	// A flag for the enemy removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;

	// Enemy sink effect (in water)
	

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	// The enemy's collider
	Collider* collider = nullptr;

	
	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
};

#endif //__ENEMY_H__
