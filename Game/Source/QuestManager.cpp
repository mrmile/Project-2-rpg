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
#include "Audio.h"
#include "TitleScreen.h"


QuestManager::QuestManager(bool start_enabled) : Module(start_enabled)
{
	name.Create("QuestManager");

	questCompletionAnim.PushBack({ 2, 7, 149, 49 });
	questCompletionAnim.PushBack({ 2, 7, 149, 49 });
	questCompletionAnim.PushBack({ 2, 7, 149, 49 });
	questCompletionAnim.PushBack({ 162, 7, 149, 49 });
	questCompletionAnim.PushBack({ 322, 7, 149, 49 });
	questCompletionAnim.PushBack({ 482, 7, 149, 49 });
	questCompletionAnim.PushBack({ 2, 62, 149, 49 });
	questCompletionAnim.PushBack({ 162, 62, 149, 49 });
	questCompletionAnim.PushBack({ 322, 62, 149, 49 });
	questCompletionAnim.PushBack({ 482, 62, 149, 49 });
	questCompletionAnim.PushBack({ 2, 122, 149, 49 });
	questCompletionAnim.PushBack({ 2, 122, 149, 49 });
	questCompletionAnim.PushBack({ 2, 122, 149, 49 });
	questCompletionAnim.PushBack({ 2, 122, 149, 49 });
	questCompletionAnim.PushBack({ 2, 122, 149, 49 });
	questCompletionAnim.PushBack({ 2, 122, 149, 49 });
	questCompletionAnim.PushBack({ 2, 122, 149, 49 });
	questCompletionAnim.PushBack({ 2, 122, 149, 49 });
	questCompletionAnim.PushBack({ 2, 122, 149, 49 });
	questCompletionAnim.PushBack({ 2, 122, 149, 49 });
	questCompletionAnim.PushBack({ 2, 122, 149, 49 });
	questCompletionAnim.PushBack({ 2, 122, 149, 49 });
	questCompletionAnim.PushBack({ 2, 122, 149, 49 });
	questCompletionAnim.PushBack({ 2, 122, 149, 49 });
	questCompletionAnim.loop = false;
	questCompletionAnim.speed = 0.4f;

	none.PushBack({ 460, 160, 1, 1 });
	none.loop = false;
	none.speed = 0.3f;

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
	secondaryQuestSwitches = app->tex->Load("Assets/textures/GUI/Inventory/secondaryQuest_switches.png");

	questCompletionMessage = app->tex->Load("Assets/textures/GUI/questCompletedMessage.png");


	questCompleted = app->audio->LoadFx("Assets/audio/fx/UISounds/achievement_01.wav");

	questCounter = 241;
	currentAnimation = &none;

	return true;
}

bool QuestManager::Update(float dt)
{
	questCounter++;

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


	if (questCounter <= 240)
	{
		if (currentAnimation != &questCompletionAnim)
		{
			questCompletionAnim.Reset();
			currentAnimation = &questCompletionAnim;
		}
	}
	else
	{
		if (currentAnimation != &none)
		{
			none.Reset();
			currentAnimation = &none;
		}
	}

	currentAnimation->Update();
	
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
			if (app->inventoryMenu->showInventory == true && app->player->showCombatHUD == false)app->render->DrawTexture2(mainQuestDescription_1, 0, 0, NULL);
			break;
		}
		case LOOK_FOR_THE_COMPUTER_2:
		{
			if (app->inventoryMenu->showInventory == true && app->player->showCombatHUD == false && secondaryQuestID != ACTIVATE_SWITCHES)app->render->DrawTexture2(mainQuestDescription_2, 0, 0, NULL);
			break;
		}
		case KILL_THE_PATIENT_ZERO_3:
		{
			if (app->inventoryMenu->showInventory == true && app->player->showCombatHUD == false)app->render->DrawTexture2(mainQuestDescription_3, 0, 0, NULL);
			break;
		}
	}
	
	switch (secondaryQuestID)
	{
		case S_NONE:
		{
			
			break;
		}
		case ACTIVATE_SWITCHES:
		{
			if (app->inventoryMenu->showInventory == true && app->player->showCombatHUD == false)app->render->DrawTexture2(secondaryQuestSwitches, 0, 0, NULL);
			break;
		}
	}


	SDL_Rect questAnimRect = app->questManager->currentAnimation->GetCurrentFrame();
	app->render->DrawTexture2(questCompletionMessage, 480, 10, &questAnimRect);

	return true;
}

void QuestManager::SwitchMainQuest(int questID)
{
	mainQuestID = questID;
	app->audio->PlayFx(questCompleted);
	questCounter = 0;
}

void QuestManager::SwitchSecondaryQuest(int questID)
{
	secondaryQuestID = questID;
	app->audio->PlayFx(questCompleted);
	questCounter = 0;
}

bool QuestManager::CleanUp()
{
	LOG("Freeing QuestManager");

	app->tex->UnLoad(mainQuestDescription_1);
	app->tex->UnLoad(mainQuestDescription_2);
	app->tex->UnLoad(mainQuestDescription_3);
	app->tex->UnLoad(secondaryQuestSwitches);
	app->tex->UnLoad(questCompletionMessage);

	return true;
}


bool QuestManager::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node MainQuest = data.append_child("MainQuest");
	MainQuest.append_attribute("id") = mainQuestID;

	return true;
}
bool QuestManager::LoadState(pugi::xml_node& data)
{
	pugi::xml_node MainQuest = data.child("MainQuest");

	mainQuestID = data.attribute("id").as_int();

	return true;
}