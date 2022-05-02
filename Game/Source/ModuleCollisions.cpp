#include "ModuleCollisions.h"
#include "SceneCave.h"
#include "SceneMainMap.h"

#include "app.h"

#include "Render.h"
#include "Input.h"
#include "Log.h"

#include "SDL/include/SDL_Scancode.h"

//ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
ModuleCollisions::ModuleCollisions(bool start_enabled) : Module(start_enabled)
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::LAYER_ZERO][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::COIN] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::GOAL_POINT] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::PLAYER_RANGED_ATTACK] = false;

	matrix[Collider::Type::ITEM_FOOD][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::PLAYER_FEET] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::COIN] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::GOAL_POINT] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::PLAYER_RANGED_ATTACK] = false;

	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::PLAYER_FEET] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::COIN] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::GOAL_POINT] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::PLAYER_RANGED_ATTACK] = false;

	matrix[Collider::Type::PLAYER][Collider::Type::LAYER_ZERO] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_ATTACK] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::INSTANT_DEATH] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::EXIT_1] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::EXIT_2] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::EXIT_3] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::SWITCH] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::NULL_COLLIDER] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_FEET] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::RECOVER_LIFE_POWER_UP] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::COIN] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::CHECKPOINT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_ATTACK] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_RANGED_ATTACK] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::RANGED_ENEMY] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ITEM_FOOD] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ITEM_HEALTH_PACK] = true;

	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::LAYER_ZERO] = true;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::NULL_COLLIDER] = true;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::PLAYER_FEET] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::COIN] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::ENEMY_RANGED_ATTACK] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::RANGED_ENEMY] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::PLAYER_RANGED_ATTACK] = false;

	matrix[Collider::Type::ENEMY][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_FEET] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::COIN] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::GOAL_POINT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_ATTACK] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_RANGED_ATTACK] = true;


	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::PLAYER_FEET] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::COIN] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::GOAL_POINT] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::PLAYER_ATTACK] = true;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::PLAYER_RANGED_ATTACK] = true;

	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::PLAYER_FEET] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::COIN] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::GOAL_POINT] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::PLAYER_RANGED_ATTACK] = false;

	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::PLAYER_FEET] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::COIN] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::GOAL_POINT] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::PLAYER_RANGED_ATTACK] = false;

	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::LAYER_ZERO] = true;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::COIN] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::GOAL_POINT] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::PLAYER_RANGED_ATTACK] = false;

	matrix[Collider::Type::EXIT_1][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::EXIT_1][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::EXIT_1][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::COIN] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::GOAL_POINT] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::PLAYER_RANGED_ATTACK] = false;

	matrix[Collider::Type::EXIT_2][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::EXIT_2][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::EXIT_2][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::COIN] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::GOAL_POINT] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::PLAYER_RANGED_ATTACK] = false;

	matrix[Collider::Type::EXIT_3][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::EXIT_3][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::INSTANT_DEATH] = true;
	matrix[Collider::Type::EXIT_3][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::EXIT_3][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::COIN] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::GOAL_POINT] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::PLAYER_RANGED_ATTACK] = false;

	matrix[Collider::Type::SWITCH][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::SWITCH][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::SWITCH][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::SWITCH][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::COIN] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::GOAL_POINT] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::PLAYER_RANGED_ATTACK] = false;

	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::COIN] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::GOAL_POINT] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::PLAYER_RANGED_ATTACK] = false;

	matrix[Collider::Type::PLAYER_FEET][Collider::Type::LAYER_ZERO] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::INSTANT_DEATH] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::EXIT_1] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::EXIT_2] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::EXIT_3] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::SWITCH] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::NULL_COLLIDER] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::PLAYER_FEET] = false;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::RECOVER_LIFE_POWER_UP] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::COIN] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::CHECKPOINT] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::GOAL_POINT] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::PLAYER_RANGED_ATTACK] = false;

	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::COIN] = false;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::GOAL_POINT] = false;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::PLAYER_RANGED_ATTACK] = false;


	matrix[Collider::Type::COIN][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::COIN][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::COIN][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::COIN][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::COIN][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::COIN][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::COIN][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::COIN][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::COIN][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::COIN][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::COIN][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::COIN][Collider::Type::COIN] = false;
	matrix[Collider::Type::COIN][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::COIN][Collider::Type::GOAL_POINT] = false;
	matrix[Collider::Type::COIN][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::COIN][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::COIN][Collider::Type::PLAYER_RANGED_ATTACK] = false;

	matrix[Collider::Type::CHECKPOINT][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::COIN] = false;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::GOAL_POINT] = false;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::PLAYER_RANGED_ATTACK] = false;

	matrix[Collider::Type::GOAL_POINT][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::COIN] = false;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::GOAL_POINT] = false;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::PLAYER_RANGED_ATTACK] = false;

}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

bool ModuleCollisions::Awake()
{
	return true;
}

bool ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (matrix[c1->type][c2->type] && c1->Intersects(c2->rect))
			{
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c1->listeners[i] != nullptr) c1->listeners[i]->OnCollision(c1, c2);

				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c2->listeners[i] != nullptr) c2->listeners[i]->OnCollision(c2, c1);
			}
		}
	}

	return true;
}

bool ModuleCollisions::Update(float dt)
{
	if (app->input->keys[SDL_SCANCODE_F9] == KEY_DOWN)
		debug = !debug;

	return true;
}

bool ModuleCollisions::PostUpdate()
{
	if (debug)
		DebugDraw();

	return true;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		
		if (app->sceneCave->godMode == false && app->sceneMainMap->godMode == false)
		{
			switch (colliders[i]->type)
			{
			case Collider::Type::NONE: // white
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::ITEM_FOOD:
				app->render->DrawRectangle(colliders[i]->rect, 0, 38, 90, alpha);
				break;
			case Collider::Type::ITEM_HEALTH_PACK:
				app->render->DrawRectangle(colliders[i]->rect, 255, 0, 0, alpha);
				break;
			case Collider::Type::LAYER_ZERO: // blue
				app->render->DrawRectangle(colliders[i]->rect, 0, 0, 255, alpha);
				break;
			case Collider::Type::PLAYER: // green
				app->render->DrawRectangle(colliders[i]->rect, 0, 255, 0, alpha);
				break;
			case Collider::Type::PLAYER_FEET: //orange
				app->render->DrawRectangle(colliders[i]->rect, 255, 100, 0, alpha);
				break;
			case Collider::Type::ENEMY: // yellow
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 0, alpha);
				break;
			case Collider::Type::ENEMY_ATTACK: // red
				app->render->DrawRectangle(colliders[i]->rect, 170, 255, 0, alpha);
				break;
			case Collider::Type::ENEMY_RANGED_ATTACK: // red
				app->render->DrawRectangle(colliders[i]->rect, 170, 255, 0, alpha);
				break;
			case Collider::Type::PLAYER_ATTACK: // red
				app->render->DrawRectangle(colliders[i]->rect, 170, 255, 0, alpha);
				break;
			case Collider::Type::PLAYER_RANGED_ATTACK: // red
				app->render->DrawRectangle(colliders[i]->rect, 170, 255, 0, alpha);
				break;
			case Collider::Type::INSTANT_DEATH: // red
				app->render->DrawRectangle(colliders[i]->rect, 170, 255, 0, alpha);
				break;
			case Collider::Type::EXIT_1: // magenta
				app->render->DrawRectangle(colliders[i]->rect, 0, 255, 255, alpha);
				break;
			case Collider::Type::EXIT_2: // orange
				app->render->DrawRectangle(colliders[i]->rect, 255, 155, 0, alpha);
				break;
			case Collider::Type::EXIT_3: // light blue
				app->render->DrawRectangle(colliders[i]->rect, 0, 240, 255, alpha);
				break;
			case Collider::Type::SWITCH: // red
				app->render->DrawRectangle(colliders[i]->rect, 170, 255, 0, alpha);
				break;
			case Collider::Type::NULL_COLLIDER: // black
				app->render->DrawRectangle(colliders[i]->rect, 0, 0, 0, alpha);
				break;
			case Collider::Type::RECOVER_LIFE_POWER_UP: // purple
				app->render->DrawRectangle(colliders[i]->rect, 128, 0, 255, alpha);
				break;
			case Collider::Type::COIN: // light yellow
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 172, alpha);
				break;
			case Collider::Type::CHECKPOINT: // light green
				app->render->DrawRectangle(colliders[i]->rect, 172, 255, 200, alpha);
				break;
			case Collider::Type::GOAL_POINT: // light green
				app->render->DrawRectangle(colliders[i]->rect, 172, 255, 200, alpha);
				break;
			}
		}
		if (app->sceneCave->godMode == true || app->sceneMainMap->godMode == true)
		{
			switch (colliders[i]->type)
			{
			case Collider::Type::NONE: // white
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::LAYER_ZERO: // blue
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::PLAYER: // green
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::PLAYER_FEET: //orange
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::ENEMY: // red
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::INSTANT_DEATH: // yellow
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::EXIT_1: // magenta
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::EXIT_2: // orange
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::EXIT_3: // light blue
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::SWITCH: // light green
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::NULL_COLLIDER: // black
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::RECOVER_LIFE_POWER_UP: // purple
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::COIN: // light yellow
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::CHECKPOINT: // light green
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::GOAL_POINT: // light green
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			}
		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			//LOG("Added ColliderSensor");
			break;
		}
	}

	return ret;
}

void ModuleCollisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
			//LOG("Removed ColliderSensor");
		}
	}
}