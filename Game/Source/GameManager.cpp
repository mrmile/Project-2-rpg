#include "App.h"
#include "GameManager.h"
#include "EntityManager.h"
#include "Defs.h"
#include "Log.h"


GameManager::GameManager(bool start_enabled) : Module(start_enabled)
{
	name.Create("GameManager");
}

// Destructor
GameManager::~GameManager()
{}

// Called before render is available
bool GameManager::Awake(pugi::xml_node& config)
{
	
	return true;
}

bool GameManager::Update(float dt)
{
	/*
	if (Check if player is not on combat)
	{
		state = GameState::OutOfCombat;
		
		when a combat is finished reset the list so it can be filled again with enemies
	}
	if (Check if the combat is ongoing ) -Player still alive -Enemies involved in combat still alive -Player has not escaped from combat -Combat ongoing
	{
		
		state = GameState::InCombat;
		
		here we should fill the EntitesInCombat list with all the entites that are in combat in that moment, ordering them in order of speed atribute they have "maybe" (talk with game designer)
		In the if statements below we check which entity type we have and after the turn is finished go to the next entity type in the list

		
		if (check if enemies turn has ended and if player has enough AP(action points) to continue, if not pass turn to enemies if combat is still going)
		{
			turn == TurnState::PlayerTurn
		}
		if (check the list of enemies and see if their turn is up, if they have enough AP continue with the turn and if not they will have to pass turn to next or if next is == to player pass turn to the player)
		{
			turn == TurnState::EnemyTurn
		}
	}
	*/
	return true;
}
