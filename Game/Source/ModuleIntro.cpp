#include "ModuleIntro.h"
#include "TitleScreen.h"
#include "ModuleIntro.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneMainMap.h"
#include "SceneCave.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleFonts.h"
#include "GuiManager.h"
#include "GuiButton.h"
#include "PauseMenu.h"
#include "CreditsScreen.h"
#include "EntityManager.h"
#include "Entity.h"
#include "SceneBase.h"
#include "QuestManager.h"
#include "InventoryMenu.h"

#include "Defs.h"
#include "Log.h"

#include <SDL_mixer/include/SDL_mixer.h>
#include <iostream>
using namespace std;

ModuleIntro::ModuleIntro(bool start_enabled) : Module(start_enabled)
{
	name.Create("IntroScreen");
}

ModuleIntro::~ModuleIntro()
{
}

bool ModuleIntro::Awake()
{
	LOG("IntroScreen Scene");
	bool ret = true;

	return ret;

	return true;
}

bool ModuleIntro::Start()
{
	intro = app->tex->Load("Assets/textures/Scenes/Intro/intro.png");

	app->audio->ChangeMusic(STORY_INTRO, 0, 0);

	delay = 0;
	backwardsImage = 0;
	
	return true;
}

bool ModuleIntro::PreUpdate()
{

	return true;
}

bool ModuleIntro::Update(float dt)
{
	delay++;

	if ((delay % 2) == 0)
	{
		backwardsImage--;
	}

	if (delay >= 3155 || (app->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN))
	{
		//app->physics->Enable();
		app->collisions->Enable();
		app->map->Enable();
		app->particles->Enable();
		app->sceneMainMap->Enable();
		app->player->Enable();
		app->entity_manager->Enable();
		app->fonts->Enable();
		app->tex->Enable();
		app->pause_menu->Enable();

		app->player->score = 0;
		//app->player->lives = 3;
		app->titleScreen->SavedGame = false;

		app->player->entranceID = 0;
		app->player->harborUnlock = false;
		app->player->baseUnlock = false;
		app->player->rock1Removed = false;
		app->player->rock2Removed = false;
		app->player->switchesPressed = 0;
		app->player->switch1Ok = false;
		app->player->switch2Ok = false;
		app->player->switch3Ok = false;
		app->player->switch4Ok = false;
		app->player->switch5Ok = false;
		app->player->boss1Dead = false;
		app->player->boss2Dead = false;
		app->player->boss3Dead = false;
		app->player->finalBossDead = false;
		app->questManager->mainQuestID = FIND_THE_DOCTOR_1;

		app->moduleIntro->Disable();
		//app->fade->FadeToBlack(app->titleScreen, app->sceneCave, 60);
	}

	return true;
}

bool ModuleIntro::PostUpdate()
{
	//bool ret = true;


	app->render->DrawTexture2(intro, 0, backwardsImage, NULL);

	//return ret;

	return true;
}

bool ModuleIntro::CleanUp()
{
	app->tex->UnLoad(intro);

	return true;
}


