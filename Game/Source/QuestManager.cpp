#include "App.h"
#include "QuestManager.h"
#include "EntityManager.h"
#include "Entity.h"
#include "ModulePlayer.h"
#include "InventoryMenu.h"
#include "Textures.h"
#include "Defs.h"
#include "Log.h"
#include "List.h"


QuestManager::QuestManager(bool start_enabled) : Module(start_enabled)
{
	name.Create("QuestManager");
}

// Destructor
QuestManager::~QuestManager()
{}

// Called before render is available
bool QuestManager::Awake(pugi::xml_node& config)
{

	return true;
}

bool QuestManager::Start()
{
	mainQuestDescription_1 = app->tex->Load("Assets/textures/GUI/Inventory/mainQuest_1.png");
	mainQuestDescription_2 = app->tex->Load("Assets/textures/GUI/Inventory/mainQuest_2.png");
	mainQuestDescription_3 = app->tex->Load("Assets/textures/GUI/Inventory/mainQuest_3.png");

	return true;
}

bool QuestManager::Update(float dt)
{
	switch(mainQuestID)
	{
		case M_NONE:
		{

			break;
		}
		case FIND_THE_DOCTOR_1:
		{
			
			break;
		}
		case LOOK_FOR_THE_COMPUTER_2:
		{
			
			break;
		}
		case KILL_THE_PATIENT_ZERO_3:
		{
			
			break;
		}
	}

	switch (secondaryQuestID)
	{
		case S_NONE:
		{
			
			break;
		}
	}
	
	return true;
	
}

bool QuestManager::PostUpdate()
{
	switch (mainQuestID)
	{
		case M_NONE:
		{
			
			break;
		}
		case FIND_THE_DOCTOR_1:
		{
			if (app->inventoryMenu->showInventory == true)app->render->DrawTexture(mainQuestDescription_1, 0, 0, NULL);
			break;
		}
		case LOOK_FOR_THE_COMPUTER_2:
		{
			if (app->inventoryMenu->showInventory == true)app->render->DrawTexture(mainQuestDescription_2, 0, 0, NULL);
			break;
		}
		case KILL_THE_PATIENT_ZERO_3:
		{
			if (app->inventoryMenu->showInventory == true)app->render->DrawTexture(mainQuestDescription_3, 0, 0, NULL);
			break;
		}
	}

	switch (secondaryQuestID)
	{
		case S_NONE:
		{
			
			break;
		}
	}

	return true;
}

void QuestManager::SwitchMainQuest(int questID)
{
	mainQuestID = questID;
}

void QuestManager::SwitchSecondaryQuest(int questID)
{
	secondaryQuestID = questID;
}

bool QuestManager::CleanUp()
{
	LOG("Freeing QuestManager");

	app->tex->UnLoad(mainQuestDescription_1);
	app->tex->UnLoad(mainQuestDescription_2);
	app->tex->UnLoad(mainQuestDescription_3);

	return true;
}
