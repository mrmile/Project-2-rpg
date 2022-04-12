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
	StartOfTurn,  // Create path from enemies to player
	MidOfTurn,   // Move enemies towards player x tiles
	FinishTurn,  // if the distance is correct from enemy to player attack if not end turn
	WaitTurn, //Wait for the player to do it's turn
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