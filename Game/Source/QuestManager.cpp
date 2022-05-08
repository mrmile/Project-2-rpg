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

bool QuestManager::Update(float dt)
{
	
	
	return true;
	
}

bool QuestManager::PostUpdate()
{
	return true;
}

void QuestManager::ClearList()
{

	
}

bool QuestManager::CleanUp()
{
	LOG("Freeing QuestManager");

	return true;
}
