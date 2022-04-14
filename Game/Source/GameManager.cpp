#include "App.h"
#include "GameManager.h"
#include "EntityManager.h"
#include "Entity.h"
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
	if (StartTurnManagement == true)
	{
		if (app->entity_manager->ListInCombat.At(counter)->data->entityTurn == TurnState::NONE)
		{
			app->entity_manager->ListInCombat.At(counter)->data->entityTurn = TurnState::StartOfTurn;
		}
		if (app->entity_manager->ListInCombat.At(counter)->data->entityTurn == TurnState::WaitTurn)
		{
			if (counter < app->entity_manager->ListInCombat.count() - 1)
			{
				counter++;
			}
		}

		return true;
	}
	if (StartTurnManagement == false) return true;
	
	
}

void GameManager::NextTurn()
{
	counter = 0;

	for (uint i = 0; i < app->entity_manager->ListInCombat.count(); i++)
	{
		app->entity_manager->ListInCombat.At(i)->data->entityTurn = TurnState::StartOfTurn;
	}
}
