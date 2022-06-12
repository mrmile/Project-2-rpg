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
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::PLAYER_PICKUP_RADIUS] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::ENABLE_BOSS_3] = false;

	matrix[Collider::Type::ITEM_FOOD][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::PLAYER_FEET] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::PLAYER_PICKUP_RADIUS] = true;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::ITEM_FOOD][Collider::Type::ENABLE_BOSS_3] = false;

	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::PLAYER_FEET] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::PLAYER_PICKUP_RADIUS] = true;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::ITEM_HEALTH_PACK][Collider::Type::ENABLE_BOSS_3] = false;

	matrix[Collider::Type::PLAYER][Collider::Type::LAYER_ZERO] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::INSTANT_DEATH] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::EXIT_1] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::EXIT_2] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::EXIT_3] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::SWITCH] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::NULL_COLLIDER] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_FEET] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::DOCTOR_NOTE_MESSAGE] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::DOOR_KEY_READER] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::TNT_SWITCH] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_ATTACK] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_RANGED_ATTACK] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::RANGED_ENEMY] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ITEM_FOOD] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ITEM_HEALTH_PACK] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ITEM_DEFAULT_GUN] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ITEM_SUIT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ITEM_KNIFE] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::BASE_COMPUTER] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ITEM_CARD] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_PICKUP_RADIUS] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::TNT_SWITCH2] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ENABLE_BOSS_1] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ENABLE_BOSS_2] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ENABLE_BOSS_3] = true;

	matrix[Collider::Type::ITEM_CARD][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::PLAYER_FEET] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::ENEMY_RANGED_ATTACK] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::RANGED_ENEMY] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::ENEMY_RANGED_ATTACK] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::ITEM_FOOD] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::ITEM_HEALTH_PACK] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::ITEM_SUIT] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::ITEM_KNIFE] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::ITEM_DEFAULT_GUN] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::ITEM_CARD] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::PLAYER_PICKUP_RADIUS] = true;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::ITEM_CARD][Collider::Type::ENABLE_BOSS_3] = false;

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
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::ENEMY_RANGED_ATTACK] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::RANGED_ENEMY] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::PLAYER_PICKUP_RADIUS] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::ENABLE_BOSS_3] = false;

	matrix[Collider::Type::ENEMY][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_FEET] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_ATTACK] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_RANGED_ATTACK] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_PICKUP_RADIUS] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::ENABLE_BOSS_3] = false;

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
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::PLAYER_ATTACK] = true;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::PLAYER_RANGED_ATTACK] = true;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::PLAYER_PICKUP_RADIUS] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::RANGED_ENEMY][Collider::Type::ENABLE_BOSS_3] = false;

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
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::PLAYER_PICKUP_RADIUS] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::ENEMY_ATTACK][Collider::Type::ENABLE_BOSS_3] = false;

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
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::PLAYER_PICKUP_RADIUS] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::ENEMY_RANGED_ATTACK][Collider::Type::ENABLE_BOSS_3] = false;

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
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::PLAYER_PICKUP_RADIUS] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::ENABLE_BOSS_3] = false;

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
	matrix[Collider::Type::EXIT_1][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::PLAYER_PICKUP_RADIUS] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::EXIT_1][Collider::Type::ENABLE_BOSS_3] = false;

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
	matrix[Collider::Type::EXIT_2][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::PLAYER_PICKUP_RADIUS] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::EXIT_2][Collider::Type::ENABLE_BOSS_3] = false;

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
	matrix[Collider::Type::EXIT_3][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::PLAYER_PICKUP_RADIUS] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::EXIT_3][Collider::Type::ENABLE_BOSS_3] = false;

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
	matrix[Collider::Type::SWITCH][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::PLAYER_PICKUP_RADIUS] = true;
	matrix[Collider::Type::SWITCH][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::SWITCH][Collider::Type::ENABLE_BOSS_3] = false;

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
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::PLAYER_PICKUP_RADIUS] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::ENABLE_BOSS_3] = false;

	matrix[Collider::Type::PLAYER_FEET][Collider::Type::LAYER_ZERO] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::INSTANT_DEATH] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::EXIT_1] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::EXIT_2] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::EXIT_3] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::SWITCH] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::NULL_COLLIDER] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::PLAYER_FEET] = false;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::DOCTOR_NOTE_MESSAGE] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::DOOR_KEY_READER] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::TNT_SWITCH] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::ENABLE_FINAL_BATTLE] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::PLAYER_PICKUP_RADIUS] = false;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::ENABLE_BOSS_3] = false;

	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::PLAYER_PICKUP_RADIUS] = true;
	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::DOCTOR_NOTE_MESSAGE][Collider::Type::ENABLE_BOSS_3] = false;

	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::PLAYER_PICKUP_RADIUS] = true;
	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::DOOR_KEY_READER][Collider::Type::ENABLE_BOSS_3] = false;

	matrix[Collider::Type::TNT_SWITCH][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::TNT_SWITCH][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::TNT_SWITCH][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::TNT_SWITCH][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::TNT_SWITCH][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::TNT_SWITCH][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::TNT_SWITCH][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::TNT_SWITCH][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::TNT_SWITCH][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::TNT_SWITCH][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::TNT_SWITCH][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::TNT_SWITCH][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::TNT_SWITCH][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::TNT_SWITCH][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::TNT_SWITCH][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::TNT_SWITCH][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::TNT_SWITCH][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::TNT_SWITCH][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::TNT_SWITCH][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::TNT_SWITCH][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::TNT_SWITCH][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::TNT_SWITCH][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::TNT_SWITCH][Collider::Type::PLAYER_PICKUP_RADIUS] = true;
	matrix[Collider::Type::TNT_SWITCH][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::TNT_SWITCH][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::TNT_SWITCH][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::TNT_SWITCH][Collider::Type::ENABLE_BOSS_3] = false;

	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::PLAYER_PICKUP_RADIUS] = false;
	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::ENABLE_FINAL_BATTLE][Collider::Type::ENABLE_BOSS_3] = false;

	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::PLAYER_FEET] = false;
	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::PLAYER_PICKUP_RADIUS] = true;
	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::ITEM_GRENADE][Collider::Type::ENABLE_BOSS_3] = false;

	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::PLAYER_FEET] = false;
	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::PLAYER_PICKUP_RADIUS] = true;
	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::ITEM_LONG_RANGE_GUN][Collider::Type::ENABLE_BOSS_3] = false;

	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::PLAYER_FEET] = false;
	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::PLAYER_PICKUP_RADIUS] = true;
	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::ITEM_SHORT_RANGE_GUN][Collider::Type::ENABLE_BOSS_3] = false;

	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::PLAYER_FEET] = false;
	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::PLAYER_PICKUP_RADIUS] = true;
	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::ITEM_DEFAULT_GUN][Collider::Type::ENABLE_BOSS_3] = false;

	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::PLAYER_FEET] = false;
	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::PLAYER_PICKUP_RADIUS] = true;
	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::ITEM_KNIFE][Collider::Type::ENABLE_BOSS_3] = false;

	matrix[Collider::Type::ITEM_SUIT][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::ITEM_SUIT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ITEM_SUIT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ITEM_SUIT][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::ITEM_SUIT][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::ITEM_SUIT][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::ITEM_SUIT][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::ITEM_SUIT][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::ITEM_SUIT][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::ITEM_SUIT][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::ITEM_SUIT][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::ITEM_SUIT][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::ITEM_SUIT][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::ITEM_SUIT][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::ITEM_SUIT][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::ITEM_SUIT][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::ITEM_SUIT][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::ITEM_SUIT][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::ITEM_SUIT][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::ITEM_SUIT][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::ITEM_SUIT][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::ITEM_SUIT][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::ITEM_SUIT][Collider::Type::PLAYER_PICKUP_RADIUS] = true;
	matrix[Collider::Type::ITEM_SUIT][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::ITEM_SUIT][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::ITEM_SUIT][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::ITEM_SUIT][Collider::Type::ENABLE_BOSS_3] = false;

	matrix[Collider::Type::ITEM_RADIO][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::ITEM_RADIO][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ITEM_RADIO][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ITEM_RADIO][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::ITEM_RADIO][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::ITEM_RADIO][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::ITEM_RADIO][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::ITEM_RADIO][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::ITEM_RADIO][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::ITEM_RADIO][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::ITEM_RADIO][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::ITEM_RADIO][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::ITEM_RADIO][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::ITEM_RADIO][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::ITEM_RADIO][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::ITEM_RADIO][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::ITEM_RADIO][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::ITEM_RADIO][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::ITEM_RADIO][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::ITEM_RADIO][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::ITEM_RADIO][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::ITEM_RADIO][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::ITEM_RADIO][Collider::Type::PLAYER_PICKUP_RADIUS] = true;
	matrix[Collider::Type::ITEM_RADIO][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::ITEM_RADIO][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::ITEM_RADIO][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::ITEM_RADIO][Collider::Type::ENABLE_BOSS_3] = false;

	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::PLAYER_PICKUP_RADIUS] = true;
	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::BASE_COMPUTER][Collider::Type::ENABLE_BOSS_3] = false;

	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::DOOR_KEY_READER] = true;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::ITEM_GRENADE] = true;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::ITEM_LONG_RANGE_GUN] = true;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::ITEM_SHORT_RANGE_GUN] = true;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::PLAYER_PICKUP_RADIUS] = false;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::ITEM_RADIO] = true;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::ITEM_CARD] = true;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::ITEM_HEALTH_PACK] = true;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::ITEM_FOOD] = true;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::ITEM_DEFAULT_GUN] = true;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::ITEM_SUIT] = true;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::ITEM_KNIFE] = true;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::PLAYER_PICKUP_RADIUS] = false;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::PLAYER_PICKUP_RADIUS][Collider::Type::ENABLE_BOSS_3] = false;

	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::PLAYER_PICKUP_RADIUS] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::ITEM_CARD] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::ITEM_HEALTH_PACK] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::ITEM_FOOD] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::ITEM_DEFAULT_GUN] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::ITEM_SUIT] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::ITEM_KNIFE] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::PLAYER_PICKUP_RADIUS] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::PLAYER_RANGED_ATTACK][Collider::Type::ENABLE_BOSS_3] = false;

	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::PLAYER_FEET] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::PLAYER_PICKUP_RADIUS] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::ITEM_CARD] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::ITEM_HEALTH_PACK] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::ITEM_FOOD] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::ITEM_DEFAULT_GUN] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::ITEM_SUIT] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::ITEM_KNIFE] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::PLAYER_PICKUP_RADIUS] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::TNT_SWITCH2][Collider::Type::ENABLE_BOSS_3] = false;

	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::PLAYER_FEET] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::PLAYER_PICKUP_RADIUS] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::ITEM_CARD] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::ITEM_HEALTH_PACK] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::ITEM_FOOD] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::ITEM_DEFAULT_GUN] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::ITEM_SUIT] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::ITEM_KNIFE] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::PLAYER_PICKUP_RADIUS] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::ENABLE_BOSS_1][Collider::Type::ENABLE_BOSS_3] = false;

	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::PLAYER_FEET] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::PLAYER_PICKUP_RADIUS] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::ITEM_CARD] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::ITEM_HEALTH_PACK] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::ITEM_FOOD] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::ITEM_DEFAULT_GUN] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::ITEM_SUIT] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::ITEM_KNIFE] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::PLAYER_PICKUP_RADIUS] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::ENABLE_BOSS_2][Collider::Type::ENABLE_BOSS_3] = false;

	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::EXIT_1] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::EXIT_2] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::EXIT_3] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::SWITCH] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::PLAYER_FEET] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::DOCTOR_NOTE_MESSAGE] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::DOOR_KEY_READER] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::TNT_SWITCH] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::ENABLE_FINAL_BATTLE] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::ENEMY_ATTACK] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::PLAYER_RANGED_ATTACK] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::ITEM_GRENADE] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::ITEM_LONG_RANGE_GUN] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::ITEM_SHORT_RANGE_GUN] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::PLAYER_PICKUP_RADIUS] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::ITEM_RADIO] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::ITEM_CARD] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::ITEM_HEALTH_PACK] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::ITEM_FOOD] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::ITEM_DEFAULT_GUN] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::ITEM_SUIT] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::ITEM_KNIFE] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::PLAYER_PICKUP_RADIUS] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::BASE_COMPUTER] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::TNT_SWITCH2] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::ENABLE_BOSS_1] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::ENABLE_BOSS_2] = false;
	matrix[Collider::Type::ENABLE_BOSS_3][Collider::Type::ENABLE_BOSS_3] = false;

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
			case Collider::Type::ITEM_RADIO:
				app->render->DrawRectangle(colliders[i]->rect, 255, 0, 0, alpha);
				break;
			case Collider::Type::ACTIVE_RADIO:
				app->render->DrawRectangle(colliders[i]->rect, 255, 0, 0, alpha);
				break;
			case Collider::Type::ITEM_DEFAULT_GUN:
				app->render->DrawRectangle(colliders[i]->rect, 225, 29, 130, alpha);
				break;
			case Collider::Type::ITEM_KNIFE:
				app->render->DrawRectangle(colliders[i]->rect, 225, 29, 130, alpha);
				break;
			case Collider::Type::ITEM_SUIT:
				app->render->DrawRectangle(colliders[i]->rect, 225, 29, 130, alpha);
				break;
			case Collider::Type::ITEM_SHORT_RANGE_GUN:
				app->render->DrawRectangle(colliders[i]->rect, 42, 170, 186, alpha);
				break;
			case Collider::Type::ITEM_LONG_RANGE_GUN:
				app->render->DrawRectangle(colliders[i]->rect, 255, 114, 0, alpha);
				break;
			case Collider::Type::ITEM_CARD:
				app->render->DrawRectangle(colliders[i]->rect, 255, 114, 90, alpha);
				break;
			case Collider::Type::ITEM_GRENADE:
				app->render->DrawRectangle(colliders[i]->rect, 255, 114, 90, alpha);
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
			case Collider::Type::DOCTOR_NOTE_MESSAGE: // purple
				app->render->DrawRectangle(colliders[i]->rect, 128, 0, 255, alpha);
				break;
			case Collider::Type::BASE_COMPUTER: // purple
				app->render->DrawRectangle(colliders[i]->rect, 128, 0, 255, alpha);
				break;
			case Collider::Type::DOOR_KEY_READER: // light yellow
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 172, alpha);
				break;
			case Collider::Type::TNT_SWITCH: // light green
				app->render->DrawRectangle(colliders[i]->rect, 172, 255, 200, alpha);
				break;
			case Collider::Type::TNT_SWITCH2: // light green
				app->render->DrawRectangle(colliders[i]->rect, 172, 255, 200, alpha);
				break;
			case Collider::Type::ENABLE_FINAL_BATTLE: // light green
				app->render->DrawRectangle(colliders[i]->rect, 172, 255, 200, alpha);
				break;
			case Collider::Type::PLAYER_PICKUP_RADIUS: 
				app->render->DrawRectangle(colliders[i]->rect, 172, 200, 200, alpha);
				break;
			case Collider::Type::ENABLE_BOSS_1: // light green
				app->render->DrawRectangle(colliders[i]->rect, 172, 255, 200, alpha);
				break;
			case Collider::Type::ENABLE_BOSS_2: // light green
				app->render->DrawRectangle(colliders[i]->rect, 172, 255, 200, alpha);
				break;
			case Collider::Type::ENABLE_BOSS_3:
				app->render->DrawRectangle(colliders[i]->rect, 172, 200, 200, alpha);
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
			case Collider::Type::DOCTOR_NOTE_MESSAGE: // purple
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::DOOR_KEY_READER: // light yellow
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::TNT_SWITCH: // light green
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::ENABLE_FINAL_BATTLE: // light green
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::PLAYER_PICKUP_RADIUS:
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::ENABLE_BOSS_1: // light green
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::ENABLE_BOSS_2: // light green
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::ENABLE_BOSS_3:
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