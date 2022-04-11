#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "Module.h"
#include "List.h"
#include "EntityManager.h"

enum class GameState
{
	OutOfCombat,
	InCombat,
};

enum class TurnState
{
	EnemyTurn,
	PlayerTurn,
};
class GameManager : public Module
{
public:

	GameManager(bool start_enabled = true);

	// Destructor
	virtual ~GameManager();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called each loop iteration
	bool Update(float dt);

	// Called before quitting
	
};

#endif // __AUDIO_H__