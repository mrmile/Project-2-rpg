#include "App.h"
#include "GameManager.h"
#include "EntityManager.h"
#include "Entity.h"
#include "ModulePlayer.h"
#include "Defs.h"
#include "Log.h"
#include "List.h"


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

		if(CheckList() == true) StartTurnManagement = false;
		

		if (app->entity_manager->ListInCombat.start->data != NULL)
		{
			if (app->entity_manager->ListInCombat.start->data->entityTurn == TurnState::StartOfTurn)
			{
				app->player->entityStatePlayer = GameState::InCombat;
			}
		
			if (app->entity_manager->ListInCombat.end->data->entityTurn == TurnState::WaitTurn)
			{
				if (counter < app->entity_manager->ListInCombat.count() - 1)
				{
					counter++;
				}
				if (counter >= app->entity_manager->ListInCombat.count() - 1)
				{
					SetAlllistToNone();
					app->player->entityTurnPlayer = TurnState::StartOfTurn;

				}
			}

			if (app->player->entityTurnPlayer == TurnState::WaitTurn)
			{
				if (counter < app->entity_manager->ListInCombat.count())counter++;
				if (counter >= app->entity_manager->ListInCombat.count())
				{
					counter = 0;
				}

				app->entity_manager->ListInCombat.At(counter)->data->entityTurn = TurnState::StartOfTurn;
				app->player->entityTurnPlayer == TurnState::NONE;
			}

			if (app->entity_manager->ListInCombat.At(counter)->data->EntityHP <= 0)
			{
				app->entity_manager->ListInCombat.At(counter)->data->entityTurn = TurnState::NONE;
			}
		}

	}
	if (StartTurnManagement == false)
	{
		app->player->entityStatePlayer = GameState::OutOfCombat;
		app->player->entityTurnPlayer = TurnState::NONE;
		ClearList();
	}
	
	return true;
	
}

bool GameManager::PostUpdate()
{
	return true;
}

void GameManager::ClearList()
{

	app->entity_manager->ListInCombat.clear();
	app->entity_manager->x = 0;
	
}

bool GameManager::CheckList()
{
	int CounterForTurnManagement = 0;

	for (int i = 0; i < app->entity_manager->ListInCombat.count(); i++)
	{
		if (app->entity_manager->ListInCombat.At(i)->data->EntityHP <= 0)
		{
			CounterForTurnManagement++;
		}
	}
	if (CounterForTurnManagement >= app->entity_manager->ListInCombat.count())
	{
		return true;
	}
	if (CounterForTurnManagement < app->entity_manager->ListInCombat.count())
	{
		return false;
	}

}

void GameManager::SetAlllistToNone()
{
	for (int i = 0; i < app->entity_manager->ListInCombat.count(); i++)
	{
		app->entity_manager->ListInCombat.At(i)->data->entityTurn = TurnState::NONE;
	}
}
