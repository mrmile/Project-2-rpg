#include "CombatMenu.h"
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
#include "Entity.h"
#include "Defs.h"
#include "Log.h"
#include <SDL_mixer/include/SDL_mixer.h>

#include <iostream>
using namespace std;

CombatMenu::CombatMenu(bool start_enabled) : Module(start_enabled)
{
	name.Create("PauseMenu");
}

// Destructor
CombatMenu::~CombatMenu()
{}

// Called before render is available
bool CombatMenu::Awake()
{
	LOG("Loading Combat Menu");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool CombatMenu::Start()
{
	combatHUD = app->tex->Load("Assets/textures/GUI/CombatUI/combatHud3.png");
	enemyTurn = app->tex->Load("Assets/textures/GUI/CombatUI/enemyTurn.png");
	enemyTurn1 = app->tex->Load("Assets/textures/GUI/CombatUI/enemyTurn1.png");
	enemyTurn2 = app->tex->Load("Assets/textures/GUI/CombatUI/enemyTurn2.png");
	enemyTurn3 = app->tex->Load("Assets/textures/GUI/CombatUI/enemyTurn3.png");
	combatShoot = app->tex->Load("Assets/textures/GUI/CombatUI/combatShoot.png");
	combatMelee = app->tex->Load("Assets/textures/GUI/CombatUI/combatMelee.png");
	combatItems = app->tex->Load("Assets/textures/GUI/CombatUI/combatItems.png");
	combatEscape = app->tex->Load("Assets/textures/GUI/CombatUI/combatEscape.png");

	buttonClickedFx = app->audio->LoadFx("Assets/audio/fx/UISounds/buttonClickedFX.wav");
	
	combatShootGUI = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 25, "Shoot Button", { 30,332,108,35 }, this, combatShoot, NULL, {});
	combatMeleeGUI = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 26, "Melee Button", { 175,332,108,35 }, this, combatMelee, NULL, {});
	combatItemsGUI = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 27, "Items Button", { 320,332,108,35 }, this, combatItems, NULL, {});
	combatEscapeGUI = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 28,"Escape Button",{ 465,331,108,35 }, this, combatEscape, NULL, {});

	return true;
}

// Called each loop iteration
bool CombatMenu::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool CombatMenu::Update(float dt)
{
	if (app->player->showCombatHUD == true)
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
	}

	return true;
}

// Called each loop iteration
bool CombatMenu::PostUpdate()
{
	bool ret = true;

	if (app->player->showCombatHUD == true && app->player->pauseMenu == false && app->titleScreen->active == false)
	{
		if (app->player->entityTurnPlayer == TurnState::WaitTurn)
		{
			delay++;

			app->render->DrawTexture2(enemyTurn, 0, 0, NULL);

			if (delay > 10)
			{
				delay2++;
			}
			if (delay2 > 20)
			{
				delay3++;
			}

			if ((delay / 60) % 2 == 0) app->render->DrawTexture2(enemyTurn1, 0, 0, NULL);
			if ((delay2 / 60) % 2 == 0) app->render->DrawTexture2(enemyTurn2, 0, 0, NULL);
			if ((delay3 / 60) % 2 == 0) app->render->DrawTexture2(enemyTurn3, 0, 0, NULL);
		}
		app->render->DrawTexture2(combatHUD, 0, 0, NULL);

		if (combatShootGUI->state == GuiControlState::NORMAL && combatShootGUI->canClick == true) combatShootGUI->SetTexture(combatShoot);
		combatShootGUI->Draw(app->render);

		if (combatMeleeGUI->state == GuiControlState::NORMAL && combatMeleeGUI->canClick == true) combatMeleeGUI->SetTexture(combatMelee);
		combatMeleeGUI->Draw(app->render);

		if (combatItemsGUI->state == GuiControlState::NORMAL && combatItemsGUI->canClick == true) combatItemsGUI->SetTexture(combatItems);
		combatItemsGUI->Draw(app->render);

		if (combatEscapeGUI->state == GuiControlState::NORMAL && combatEscapeGUI->canClick == true) combatEscapeGUI->SetTexture(combatEscape);
		combatEscapeGUI->Draw(app->render);
	}
	
	return true;
}

// Called before quitting
bool CombatMenu::CleanUp()
{
	app->tex->UnLoad(combatHUD);
	app->tex->UnLoad(enemyTurn);
	app->tex->UnLoad(enemyTurn1);
	app->tex->UnLoad(enemyTurn2);
	app->tex->UnLoad(enemyTurn3);
	app->tex->UnLoad(combatShoot);
	app->tex->UnLoad(combatMelee);
	app->tex->UnLoad(combatItems);
	app->tex->UnLoad(combatEscape);
	app->guiManager->DestroyGuiControl(25);
	app->guiManager->DestroyGuiControl(26);
	app->guiManager->DestroyGuiControl(27);
	app->guiManager->DestroyGuiControl(28);

	return true;
}

bool CombatMenu::OnGuiMouseClickEvent(GuiControl* control) 
{
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		//Checks the GUI element ID
		if (control->id == 25 && combatShootGUI->canClick == true)
		{
			//RESUME BUTTON
			app->audio->PlayFx(buttonClickedFx, 0);
		}
		if (control->id == 26 && combatMeleeGUI->canClick == true)
		{
			//RESUME BUTTON
			app->audio->PlayFx(buttonClickedFx, 0);
			app->player->MeleeAttack();
		}
		if (control->id == 27 && combatItemsGUI->canClick == true)
		{
			//RESUME BUTTON
			app->audio->PlayFx(buttonClickedFx, 0);
		}
		if (control->id == 28 && combatEscapeGUI->canClick == true)
			//escape from combat = true
			//startturnmanagement =false
		{
			//RESUME BUTTON
			app->audio->PlayFx(buttonClickedFx, 0);
			//Escape Combat
			/*app->player->escapeCombat = true;*/
		}
	}
	}

	return true;
}
