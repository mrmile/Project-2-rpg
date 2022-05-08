#include "App.h"
#include "QuestManager.h"
#include "EntityManager.h"
#include "Entity.h"
#include "ModulePlayer.h"
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

	return true;
}
