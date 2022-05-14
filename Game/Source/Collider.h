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
		EXIT_1,
		EXIT_2,
		EXIT_3,
		SWITCH,
		DOOR_KEY_READER,
		TNT_SWITCH,
		TNT_SWITCH2,
		ENABLE_FINAL_BATTLE,
		ENEMY_ATTACK,
		ENEMY_RANGED_ATTACK,
		PLAYER_ATTACK,
		PLAYER_RANGED_ATTACK,
		NPC,
		NPC2,
		NPC3,
		NPC4,
		ITEM_FOOD,
		ITEM_HEALTH_PACK,
		ITEM_GRENADE,
		ITEM_RADIO,
		ITEM_LONG_RANGE_GUN,
		ITEM_SHORT_RANGE_GUN,
		ITEM_DEFAULT_GUN,
		ITEM_CARD,
		ITEM_SUIT,
		ITEM_KNIFE,
		DOCTOR_NOTE_MESSAGE,
		BASE_COMPUTER,
		ACTIVE_RADIO,
		PLAYER_PICKUP_RADIUS,
		SWITCH_KEY,

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

