#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Module.h"
#include "EntityManager.h"
#include "Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Entity
{
public:

	iPoint position;
	SDL_Texture* texture = nullptr;
	int EntityHP;
	bool EntityKillable = false;

public:
	
	Entity(iPoint position);

	virtual ~Entity();

	const Collider* GetColldier() const;
	//logic of the entity
	virtual bool Update(float dt);

	//Drawing methodology
	virtual void Draw();
protected:
	Animation* currentAnim = nullptr;

	Collider* collider = nullptr;
};

#endif 
