#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Module.h"
#include "EntityManager.h"
#include "Point.h"

class SDL_Texture;

class Entity : public Module
{
public:

	EntityType type;
	iPoint position;
	SDL_Texture* texture;

private:

	virtual void Update();

	virtual void Draw();

	virtual void HandleInput();
};

#endif 
