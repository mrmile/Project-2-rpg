#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"

#define MAX_LISTENERS 5

class Module;

struct Collider
{
	enum Type
	{
		NONE = -1,
		NULL_COLLIDER,
		LAYER_ZERO,
		PLAYER,
		PLAYER_FEET,
		ENEMY,
		RANGED_ENEMY,
		INSTANT_DEATH,
		B_CB,
		H_CB,
		V_CB,
		LAVA,
		COIN,
		RECOVER_LIFE_POWER_UP,
		CHECKPOINT,
		GOAL_POINT,
		ENEMY_ATTACK,
		ENEMY_RANGED_ATTACK,

		MAX
	};

	//Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);

	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;

	void AddListener(Module* listener);

	//Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Module* listeners[MAX_LISTENERS] = { nullptr };
};


#endif //__COLLIDER_H__

