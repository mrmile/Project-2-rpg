#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Module.h"
#include "EntityManager.h"
#include "Point.h"
#include "Animation.h"
#include "GameManager.h"

struct SDL_Texture;
struct Collider;

class Entity
{
public:

	iPoint position;
	SDL_Texture* texture = nullptr;
	//ENTITY LIFE POINTS
	int EntityHP;
	//ENTITY ACTION POINTS
	int EntityAP;
	//ENTITY MOVEMENT POINTS
	int EntityMP;
	bool EntityKillable = false;
	EntityType type;
	// A flag for the enemy removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;
	GameState entityState;
	TurnState entityTurn;

public:
	
	Entity(int x,int y);

	virtual ~Entity();

	const Collider* GetColldier() const;
	//logic of the entity
	virtual bool Update(float dt);

	//Drawing methodology
	virtual void Draw();

	// Sets flag for deletion and for the collider aswell
	virtual void SetToDelete();

	virtual void ReduceAP(int AP_used);

protected:
	Animation* currentAnim = nullptr;

	Collider* collider = nullptr;

	iPoint spawnPos;
};

#endif 
