#include "MapMenu.h"
#include "PauseMenu.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneMainMap.h"
#include "SceneCave.h"
#include "TitleScreen.h"
#include "ModulePlayer.h"
#include "GuiManager.h"
#include "ModuleFonts.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "Map.h"
#include "EntityManager.h"
#include "GameManager.h"
#include "CreditsScreen.h"
#include "InventoryMenu.h"
#include "Entity.h"
#include "Defs.h"
#include "Render.h"
#include "Log.h"
#include "QuestManager.h"
#include "Transitions.h"

#include <SDL_mixer/include/SDL_mixer.h>

#include <iostream>
using namespace std;

MapMenu::MapMenu(bool start_enabled) : Module(start_enabled)
{
	name.Create("MapMenu");
}

// Destructor
MapMenu::~MapMenu()
{}

// Called before render is available
bool MapMenu::Awake()
{
	LOG("Loading Map Menu");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool MapMenu::Start()
{
	miniMap = app->tex->Load("Assets/textures/GUI/miniMap.png");
	/*enemyTurn = app->tex->Load("Assets/textures/GUI/CombatUI/enemyTurn.png");
	enemyTurn1 = app->tex->Load("Assets/textures/GUI/CombatUI/enemyTurn1.png");
	enemyTurn2 = app->tex->Load("Assets/textures/GUI/CombatUI/enemyTurn2.png");
	enemyTurn3 = app->tex->Load("Assets/textures/GUI/CombatUI/enemyTurn3.png");

	buttonClickedFx = app->audio->LoadFx("Assets/audio/fx/UISounds/buttonClickedFX.wav");
	buttonClickedMelee = app->audio->LoadFx("Assets/audio/fx/ZPlayer/PlayerActions/Neck.wav");

	combatShootGUI = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 25, "Shoot Button", { 30,332,108,35 }, this, combatShoot, NULL, {});
	combatMeleeGUI = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 26, "Melee Button", { 175,332,108,35 }, this, combatMelee, NULL, {});
	combatItemsGUI = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 27, "Items Button", { 320,332,108,35 }, this, combatItems, NULL, {});
	combatEscapeGUI = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 28, "Escape Button", { 465,331,108,35 }, this, combatEscape, NULL, {});*/

	return true;
}

// Called each loop iteration
bool MapMenu::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool MapMenu::Update(float dt)
{
	/*if (app->player->entityStatePlayer == GameState::InCombat)
	{
		if (transitionStarting == true)
		{
			app->transition_manager->SelectTransition(1, 0, 25);
			transitionStarting = false;
		}
	}

	if (app->player->showCombatHUD == true && app->player->pauseMenu == false && app->titleScreen->active == false && app->creditsScreen->active == false)
	{
		combatShootGUI->canClick = true;
		combatMeleeGUI->canClick = true;
		combatItemsGUI->canClick = true;
		combatEscapeGUI->canClick = true;
	}

	if (app->player->showCombatHUD == false)
	{
		combatShootGUI->canClick = false;
		combatMeleeGUI->canClick = false;
		combatItemsGUI->canClick = false;
		combatEscapeGUI->canClick = false;
	}*/

	return true;
}

// Called each loop iteration
bool MapMenu::PostUpdate()
{
	/*bool ret = true;*/

	//if (app->player->showCombatHUD == true && app->player->pauseMenu == false && app->titleScreen->active == false && app->creditsScreen->active == false)
	//{
	//	/*app->render->DrawTexture(app->guiManager->arrowPointer, app->guiManager->mouseX, app->guiManager->mouseY, NULL);*/
	//	if (app->inventoryMenu->showInventory == false) DrawEntitiesHP();
	//	if (app->player->entityTurnPlayer == TurnState::WaitTurn)
	//	{
	//		delay++;

	//		app->render->DrawTexture2(enemyTurn, 0, 0, NULL);

	//		if (delay > 10)
	//		{
	//			delay2++;
	//		}
	//		if (delay2 > 20)
	//		{
	//			delay3++;
	//		}

	//		if ((delay / 60) % 2 == 0) app->render->DrawTexture2(enemyTurn1, 0, 0, NULL);
	//		if ((delay2 / 60) % 2 == 0) app->render->DrawTexture2(enemyTurn2, 0, 0, NULL);
	//		if ((delay3 / 60) % 2 == 0) app->render->DrawTexture2(enemyTurn3, 0, 0, NULL);
	//	}
	//	app->render->DrawTexture2(combatHUD, 0, 0, NULL);

	//	if (combatShootGUI->state == GuiControlState::NORMAL && combatShootGUI->canClick == true) combatShootGUI->SetTexture(combatShoot);
	//	combatShootGUI->Draw(app->render);

	//	if (combatMeleeGUI->state == GuiControlState::NORMAL && combatMeleeGUI->canClick == true) combatMeleeGUI->SetTexture(combatMelee);
	//	combatMeleeGUI->Draw(app->render);

	//	if (combatItemsGUI->state == GuiControlState::NORMAL && combatItemsGUI->canClick == true) combatItemsGUI->SetTexture(combatItems);
	//	combatItemsGUI->Draw(app->render);

	//	if (combatEscapeGUI->state == GuiControlState::NORMAL && combatEscapeGUI->canClick == true) combatEscapeGUI->SetTexture(combatEscape);
	//	combatEscapeGUI->Draw(app->render);

	//}

	if (showMapMenu == true)
	{
		app->render->DrawTexture2(miniMap, 0, 0, NULL);
	}

	return true;
}

// Called before quitting
bool MapMenu::CleanUp()
{
	app->tex->UnLoad(miniMap);
	/*app->tex->UnLoad(enemyTurn);
	app->tex->UnLoad(enemyTurn1);
	app->tex->UnLoad(enemyTurn2);
	app->tex->UnLoad(enemyTurn3);
	app->tex->UnLoad(combatShoot);
	app->tex->UnLoad(combatMelee);
	app->tex->UnLoad(combatItems);
	app->tex->UnLoad(combatEscape);
	app->tex->UnLoad(entitiesHP100);
	app->tex->UnLoad(entitiesHP90);
	app->tex->UnLoad(entitiesHP80);
	app->tex->UnLoad(entitiesHP70);
	app->tex->UnLoad(entitiesHP60);
	app->tex->UnLoad(entitiesHP50);
	app->tex->UnLoad(entitiesHP40);
	app->tex->UnLoad(entitiesHP30);
	app->tex->UnLoad(entitiesHP20);
	app->tex->UnLoad(entitiesHP10);
	app->guiManager->DestroyGuiControl(25);
	app->guiManager->DestroyGuiControl(26);
	app->guiManager->DestroyGuiControl(27);
	app->guiManager->DestroyGuiControl(28);*/

	return true;
}

bool MapMenu::OnGuiMouseClickEvent(GuiControl* control)
{
	//switch (control->type)
	//{
	//case GuiControlType::BUTTON:
	//{
	//	//Checks the GUI element ID
	//	if (control->id == 25 && combatShootGUI->canClick == true)
	//	{
	//		//RESUME BUTTON
	//		app->audio->PlayFx(buttonClickedFx, 0);
	//		app->player->RangedAttack();
	//	}
	//	if (control->id == 26 && combatMeleeGUI->canClick == true && app->player->entityTurnPlayer == TurnState::FinishTurn)
	//	{
	//		//RESUME BUTTON
	//		app->audio->PlayFx(buttonClickedMelee, 0);
	//		app->player->MeleeAttack();

	//	}
	//	if (control->id == 27 && combatItemsGUI->canClick == true)
	//	{
	//		//RESUME BUTTON
	//		app->audio->PlayFx(buttonClickedFx, 0);

	//		app->inventoryMenu->showInventory = !app->inventoryMenu->showInventory;

	//	}
	//	if (control->id == 28 && combatEscapeGUI->canClick == true)
	//		//escape from combat = true
	//		//startturnmanagement =false
	//	{
	//		//RESUME BUTTON
	//		app->audio->PlayFx(buttonClickedFx, 0);
	//		//Escape Combat
	//		app->player->escapeCombat = true;
	//		app->game_manager->ClearList();
	//		app->game_manager->StartTurnManagement = false;
	//	}
	//}
	//}

	return true;
}




