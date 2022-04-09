#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Module.h"
#include "EntityManager.h"
#include "Point.h"

class EntityManager;

class Entity : public EntityManager 
{
public:
	/*
	Entity();
	virtual ~Entity();

	EntityType type;
	iPoint position;
	
	*/
	//logic of the entity
	virtual bool Update(float dt);

	//Drawing methodology
	virtual void Draw();

	//For entities that will be handed by inputs (such as the player)
	virtual void HandleInput();
};

#endif 
