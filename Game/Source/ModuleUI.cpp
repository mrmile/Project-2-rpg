#include "ModuleUI.h"
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
#include "MapMenu.h"

#include <SDL_mixer/include/SDL_mixer.h>

#include <iostream>
using namespace std;

ModuleUI::ModuleUI(bool start_enabled) : Module(start_enabled)
{
	name.Create("ModuleUI");
}

// Destructor
ModuleUI::~ModuleUI()
{}

// Called before render is available
bool ModuleUI::Awake()
{
	LOG("Loading Map Menu");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool ModuleUI::Start()
{
	characterHealth100 = app->tex->Load("Assets/textures/GUI/Inventory/barLife100.png");
	characterHealth80 = app->tex->Load("Assets/textures/GUI/Inventory/barLife80.png");
	characterHealth60 = app->tex->Load("Assets/textures/GUI/Inventory/barLife60.png");
	characterHealth40 = app->tex->Load("Assets/textures/GUI/Inventory/barLife40.png");
	characterHealth20 = app->tex->Load("Assets/textures/GUI/Inventory/barLife20.png");
	characterHealth20Grey = app->tex->Load("Assets/textures/GUI/Inventory/barLife20Grey.png");
	characterHealth0 = app->tex->Load("Assets/textures/GUI/Inventory/barLife00.png");
	lowHealthBlood = app->tex->Load("Assets/textures/GUI/lowHealth1.png");
	lowHealthGreyBg = app->tex->Load("Assets/textures/GUI/lowHealth2.png");
	inventoryMapIcons = app->tex->Load("Assets/textures/GUI/inventoryAndMapIcons.png");

	QTE_keys_KB = app->tex->Load("Assets/textures/extras/QTE_keys_kb.png");
	QTE_keys_XB = app->tex->Load("Assets/textures/extras/QTE_keys_xb.png");
	QTE_keys_PS = app->tex->Load("Assets/textures/extras/QTE_keys_ps.png");
	QTE_keys_pointer = app->tex->Load("Assets/textures/extras/QTE_keys_pointer.png");


	return true;
}

// Called each loop iteration
bool ModuleUI::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool ModuleUI::Update(float dt)
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
bool ModuleUI::PostUpdate()
{
	if (app->player->IsEnabled() == true)
	{
		if (app->inventoryMenu->showInventory == false && app->player->pauseMenu == false && app->mapMenu->showMapMenu == false)
		{
			app->render->DrawTexture2(inventoryMapIcons, 0, 0, NULL);

			if (app->player->playerHP >= app->player->PlayerMaxHP)
			{
				app->render->DrawTexture2(characterHealth100, -60, -7, NULL);
				lowHPdelay = 0;
			}
			if (app->player->playerHP > app->player->PlayerMaxHP / 1.25f && app->player->playerHP < app->player->PlayerMaxHP)
			{
				app->render->DrawTexture2(characterHealth80, -60, -7, NULL);
				lowHPdelay = 0;
			}
			if (app->player->playerHP > app->player->PlayerMaxHP / 1.66f && app->player->playerHP <= app->player->PlayerMaxHP / 1.25f)
			{
				app->render->DrawTexture2(characterHealth60, -60, -7, NULL);
				lowHPdelay = 0;
			}
			if (app->player->playerHP > app->player->PlayerMaxHP / 2.5f && app->player->playerHP <= app->player->PlayerMaxHP / 1.66f)
			{
				app->render->DrawTexture2(characterHealth40, -60, -7, NULL);
				lowHPdelay = 0;
			}
			if (app->player->playerHP > app->player->PlayerMaxHP / 5 && app->player->playerHP <= app->player->PlayerMaxHP / 2.5f)
			{
				lowHPdelay++;

				if (lowHPdelay < 20) app->render->DrawTexture2(lowHealthBlood, 0, 0, NULL);
				if (lowHPdelay >= 20) app->render->DrawTexture2(lowHealthGreyBg, 0, 0, NULL);

				app->render->DrawTexture2(characterHealth20, -60, -7, NULL);
				if ((lowHPdelay / 60) % 2 == 0) app->render->DrawTexture2(characterHealth20Grey, -60, -7, NULL);
			}
			if (app->player->playerHP <= 0)
			{
				app->render->DrawTexture2(characterHealth0, -60, -7, NULL);
			}
		}

		if(app->titleScreen->toTitleScreen == true) app->render->DrawTexture2(app->player->gameOverScreen, 0, 0, NULL, 0.0f);

	}

	return true;
}

// Called before quitting
bool ModuleUI::CleanUp()
{
	app->tex->UnLoad(characterHealth100);
	app->tex->UnLoad(characterHealth80);
	app->tex->UnLoad(characterHealth60);
	app->tex->UnLoad(characterHealth40);
	app->tex->UnLoad(characterHealth20);
	app->tex->UnLoad(characterHealth20Grey);
	app->tex->UnLoad(characterHealth0);
	app->tex->UnLoad(lowHealthBlood);
	app->tex->UnLoad(lowHealthGreyBg);
	app->tex->UnLoad(inventoryMapIcons);

	app->tex->UnLoad(QTE_keys_KB);
	app->tex->UnLoad(QTE_keys_XB);
	app->tex->UnLoad(QTE_keys_PS);
	app->tex->UnLoad(QTE_keys_pointer);

	return true;
}



