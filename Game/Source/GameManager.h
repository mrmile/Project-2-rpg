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
	WaitTurn, //Wait for entities to continue with their turn
	NONE,  //First state, just to order all entities so there is an order of action
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

	void NextTurn();
	
	int counter = 0;

	bool StartTurnManagement;

};

#endif // __AUDIO_H__