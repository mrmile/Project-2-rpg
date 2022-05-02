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
#include "GuiManager.h"
#include "CreditsScreen.h"
#include "Entity.h"
#include "Defs.h"
#include "Log.h"

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
	object_food = app->tex->Load("Assets/textures/GUI/Inventory/food_item_test.png");
	//Still need button textures the position does not matter right now as we are gonna update it 
	DeleteItem = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 29, "Delete item Button", { 25,160,108,35 }, this, NULL, NULL, {});
	EquipItem = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 30, "Equip item Button", { 25,160,108,35 }, this, NULL, NULL, {});
	UseItem = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 31, "Use item Button", { 25,160,108,35 }, this, NULL, NULL, {});

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
	SDL_GetMouseState(&mousePos.x, &mousePos.y);

	if (app->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KeyState::KEY_DOWN)
	{
		if (SDL_PointInRect(&mousePos, &itemList->itemRect) == SDL_TRUE)
		{
			CheckIfItemHasBeenClicked();
		}
		
	}
	

	
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
		DrawAllInventoryItems();

	}
	if (showEquipableOptions == true)
	{
		//show Equipable buttons
	}
	if (showUsableOptions == true)
	{
		//show Usable Options
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

bool InventoryMenu::AddItemToInventory(EntityType type,bool usable,bool equipable)
{
	bool ret;
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		if (itemList[i].type != EntityType::NONE && itemList[i].type == type)
		{
			ret = true;
			itemList[i].amount++;

			return ret;
		}
		if (itemList[i].type == EntityType::NONE)
		{
			ret = true;

			itemList[i].amount = 1;
			itemList[i].usable = usable;
			itemList[i].equipable = equipable;
			itemList[i].type = type;

			return ret;
		}
	
	}

}

bool InventoryMenu::CheckIfItemHasBeenClicked()
{
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		if (itemList[i].equipable == true)
		{
			//show equipable buttons
			showUsableOptions = false;
			showEquipableOptions = true;

			//Also need to change the buttons positions in order to not create too much buttons

			//Id used for the EquipItem function
			idForUsability = i;
			return true;
		}
		if (itemList[i].usable == true)
		{
			//show usable buttons
			showEquipableOptions = false;
			showUsableOptions = true;
			//Also need to change the buttons positions in order to not create too much buttons

			//Id used for the UseItem function
			idForUsability = i;
			return true;
		}
	
	}
}

void InventoryMenu::DrawAllInventoryItems()
{
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		if (itemList[i].type != EntityType::NONE)
		{
			if (itemList[i].type == EntityType::OBJECT_FOOD)
			{
				//app->render->DrawRectangle2(itemList[i].itemRect, 255, 0, 0, 255);
				app->render->DrawTexture2(object_food, itemList[i].itemRect.x, itemList[i].itemRect.y); 
			}
			//Need to add the rest of the items 
		}
	}
}
//bool Inventory::OnGuiMouseClickEvent(GuiControl* control)
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
