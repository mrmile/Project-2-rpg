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
		
		if (app->entity_manager->ListInCombat.At(counter)->data->EntityHP <= 0)
		{
			//app->entity_manager->ListInCombat.At(counter)->data = nullptr;
			//app->entity_manager->ListInCombat.At(counter)->~ListItem();
			StartTurnManagement = false;
		}

		if (app->entity_manager->ListInCombat.start->data != NULL)
		{
			if (app->entity_manager->ListInCombat.At(counter)->data->entityTurn == TurnState::StartOfTurn)
			{
				app->player->entityStatePlayer = GameState::InCombat;
			}
			/*
			if (app->entity_manager->ListInCombat.At(counter)->data->entityTurn == TurnState::WaitTurn)
			{
				

				
			}
			*/
			if (app->entity_manager->ListInCombat.At(counter)->data->entityTurn == TurnState::WaitTurn)
			{
				if (counter < app->entity_manager->ListInCombat.count() - 1)
				{
					counter++;

				}
				if (counter >= app->entity_manager->ListInCombat.count() - 1)
				{
					app->entity_manager->ListInCombat.At(counter)->data->entityTurn = TurnState::NONE;
					app->player->entityTurnPlayer = TurnState::StartOfTurn;

				}
			}

			if (app->player->entityTurnPlayer == TurnState::WaitTurn)
			{
				counter = 0;
				app->entity_manager->ListInCombat.At(counter)->data->entityTurn = TurnState::StartOfTurn;
				app->player->entityTurnPlayer == TurnState::NONE;


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
