#include "InventoryMenu.h"
#include "PauseMenu.h"
#include "TitleScreen.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneMainMap.h"
#include "SceneCave.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "Map.h"
#include "EntityManager.h"
#include "GameManager.h"
#include "CreditsScreen.h"
#include "Entity.h"
#include "Defs.h"
#include "Log.h"


#include <SDL_mixer/include/SDL_mixer.h>

#include <iostream>
using namespace std;

InventoryMenu::InventoryMenu(bool start_enabled) : Module(start_enabled)
{
	name.Create("InventoryMenu");
}

// Destructor
InventoryMenu::~InventoryMenu()
{}

// Called before render is available
bool InventoryMenu::Awake()
{
	LOG("Loading Inventory Menu");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool InventoryMenu::Start()
{
	combatHUD = app->tex->Load("Assets/textures/GUI/Inventory/InventoryHud.png"); // Just for testing
	characterName1 = app->tex->Load("Assets/textures/GUI/Inventory/chararcterName1.png"); // Just for testing
	int counter = 0;

	for (int j = 0; j < MAX_ITEMS / 4; j++)
	{
		for (int i = 0; i < MAX_ITEMS / 7; i++)
		{
			itemList[counter].itemRect = { 253 + (i * 46),65 + (j * 36),26,25 };
			counter++;
		}
		
	}
	

	return true;
}

// Called each loop iteration
bool InventoryMenu::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool InventoryMenu::Update(float dt)
{
	return true;
}

// Called each loop iteration
bool InventoryMenu::PostUpdate()
{
	bool ret = true;

	if (app->player->pauseMenu == false && app->titleScreen->active == false && app->creditsScreen->active == false && showInventory == true)
	{
		app->render->DrawTexture2(combatHUD, 0, 0, NULL); // Just for testing
		app->render->DrawTexture2(characterName1, 0, 0, NULL); // Just for testing
	}

	return true;
}

// Called before quitting
bool InventoryMenu::CleanUp()
{
	app->tex->UnLoad(combatHUD);
	app->tex->UnLoad(characterName1);

	return true;
}

void InventoryMenu::AddItemToInventory(EntityType type,bool usable,bool equipable)
{
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		if (itemList[i].type != EntityType::NONE)
		{
			if (itemList[i].type == type)
			{
				itemList[i].amount++;
			}
		}
		if (itemList[i].type == EntityType::NONE)
		{
			itemList[i].type = type;
			itemList[i].amount = 1;
			itemList[i].usable = usable;
			itemList[i].equipable = equipable;
		}
	
	}

}
//bool CombatMenu::OnGuiMouseClickEvent(GuiControl* control)
//{
//	switch (control->type)
//	{
//	case GuiControlType::BUTTON:
//	{
//		//Checks the GUI element ID
//		if (control->id == 25 && combatShootGUI->canClick == true)
//		{
//			//RESUME BUTTON
//			app->audio->PlayFx(buttonClickedFx, 0);
//		}
//		if (control->id == 26 && combatMeleeGUI->canClick == true && app->player->entityTurnPlayer == TurnState::FinishTurn)
//		{
//			//RESUME BUTTON
//			app->audio->PlayFx(buttonClickedMelee, 0);
//			app->player->MeleeAttack();
//			app->player->entityTurnPlayer = TurnState::WaitTurn;
//		}
//		if (control->id == 27 && combatItemsGUI->canClick == true)
//		{
//			//RESUME BUTTON
//			app->audio->PlayFx(buttonClickedFx, 0);
//		}
//		if (control->id == 28 && combatEscapeGUI->canClick == true)
//			//escape from combat = true
//			//startturnmanagement =false
//		{
//			//RESUME BUTTON
//			app->audio->PlayFx(buttonClickedFx, 0);
//			//Escape Combat
//			app->player->escapeCombat = true;
//			app->game_manager->StartTurnManagement = false;
//		}
//	}
//	}
//
//	return true;
//}
