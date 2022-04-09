#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Module.h"
#include "EntityManager.h"
#include "Point.h"



class Entity
{
public:

	iPoint position;
	SDL_Texture* texture = nullptr;
	int EntityHP;
	bool EntityKillable = false;
public:
	
	Entity(iPoint StartingPosition);
	virtual ~Entity();

	
	
	
	//logic of the entity
	virtual bool Update(float dt);

	//Drawing methodology
	virtual void Draw();

};

#endif 
