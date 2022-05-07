#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneCave.h"
#include "SceneMainMap.h"
#include "SceneMotel.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include "TitleScreen.h"
#include "EntityManager.h"
#include "Entity.h"
#include "ModuleParticles.h"
#include "ModuleFonts.h"
#include "PauseMenu.h"
#include "Pathfinding.h"
#include "ModuleFadeToBlack.h"
#include "SceneBase.h"
#include "GameManager.h"

#include "Defs.h"
#include "Log.h"
#include <SDL_mixer/include/SDL_mixer.h>

SceneMotel::SceneMotel(bool start_enabled) : Module(start_enabled)
{
	name.Create("SceneMotel");
}

// Destructor
SceneMotel::~SceneMotel()
{}

// Called before render is available
bool SceneMotel::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool SceneMotel::Start()
{

	app->map->Load("motel.tmx");

	app->tex->Load("Assets/textures/GUI/PauseMenuFrame.png");
	sceneTimer = 0;
	
	//b2Filter filter;

	//filter.categoryBits = 1;

	//filter.categoryBits = 0x0001;
	//filter.maskBits = 0x0001;

	//h_CB1 = app->physics->CreateRectangleSensor(app->map->MapToWorldSingle(0) + app->map->MapToWorldSingle(15) / 2, app->map->MapToWorldSingle(16) + app->map->MapToWorldSingle(7) / 2, app->map->MapToWorldSingle(15), app->map->MapToWorldSingle(7));
	//h_CB1->listener = this;
	//h_CB1->body->GetFixtureList()->SetFilterData(filter);

	//h_CB2 = app->physics->CreateRectangleSensor(app->map->MapToWorldSingle(118) + app->map->MapToWorldSingle(10) / 2, app->map->MapToWorldSingle(13) + app->map->MapToWorldSingle(10) / 2, app->map->MapToWorldSingle(10), app->map->MapToWorldSingle(10));
	//h_CB2->listener = this;
	//h_CB2->body->GetFixtureList()->SetFilterData(filter);

	app->render->camera.x = app->map->MapToWorld(0, 0).x;
	app->render->camera.y = app->map->MapToWorld(0, 0).y;

	godMode = false;
	playerRestart = false;
	destroyScene = false;
	sceneMotel = true;
	
	app->sceneCave->sceneCave = false;
	app->sceneBase->sceneBase = false;
	app->sceneMainMap->sceneMainMap = false;
	enableSceneCave = false;

	// app->titleScreen->transition = false;
	// app->titleScreen->continueTransition = false;

	app->input->GetMousePosition(app->input->arrowPointerPosition.x, app->input->arrowPointerPosition.y);

	//app->entity_manager->AddEntity(EntityType::ZOMBIE_STANDART, app->player->position.x + 100, app->player->position.y);

	//app->entity_manager->AddEntity(EntityType::ZOMBIE_STANDART, app->player->position.x - 200, app->player->position.y);

	/*
	if (app->map->Load("main.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;

		if (app->map->CreateWalkabilityMap(w, h, &data)) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}
	*/

	//app->SaveGameRequest();

	return true;
}

// Called each loop iteration
bool SceneMotel::PreUpdate()
{
	/*
	if (sceneTimer <= 2)
	{
		app->map->Load("main.tmx");

		// Load music
		app->audio->ChangeMusic(MAIN_MAP, 0.5f, 0.5f);
	}
	*/

	if (app->titleScreen->GameHasContinued == true)
	{
		app->LoadGameRequest();
		app->titleScreen->GameHasContinued = false;
	}

	return true;
}

// Called each loop iteration
bool SceneMotel::Update(float dt)
{
	sceneTimer++;
	//F9 --> See colliders

	

	if (app->input->keys[SDL_SCANCODE_F10] == KEY_DOWN && app->player->destroyed == false && app->player->playerWin == false)
		godMode = !godMode;

    
	// L02: DONE 3: Request Load / Save when pressing L/S
	if (app->input->keys[SDL_SCANCODE_F6] == KEY_DOWN && app->player->destroyed == false && app->player->playerWin == false)
	{
		app->LoadGameRequest();
	}
		

	if (app->input->keys[SDL_SCANCODE_F5] == KEY_DOWN && app->player->destroyed == false && app->player->playerWin == false)
	{
		app->titleScreen->SavedGame = true;
		app->SaveGameRequest();
	}
	
		

	//if(app->input->keys[SDL_SCANCODE_S) == KEY_REPEAT)
		//app->render->camera.y -= 5;

	//if(app->input->keys[SDL_SCANCODE_W) == KEY_REPEAT)
		//app->render->camera.y += 5;

	//if(app->input->keys[SDL_SCANCODE_D) == KEY_REPEAT)
		//app->render->camera.x -= 5;

	//if(app->input->keys[SDL_SCANCODE_A) == KEY_REPEAT)
		//app->render->camera.x += 5;

	// Draw map
	app->map->Draw();

	if (app->player->destroyed == true && app->player->destroyedDelay < 1)
	{
		Mix_PauseMusic();
		//app->audio->PlayFx(dead, 0);
	}

	if (app->player->playerWin == true && app->player->winDelay < 1)
	{
		Mix_PauseMusic();
		//app->audio->PlayFx(levelClear, 0);
	}

	

	return true;
}

// Called each loop iteration
bool SceneMotel::PostUpdate()
{
	bool ret = true;
	if (sceneTimer <= 2)
	{
		app->audio->ChangeMusic(MOTEL_ZONE, 0.5f, 0.5f);
	}
	
	//if (app->player->horizontalCB == false && app->player->bidimensionalCB == false && sceneTimer > 1) app->render->camera.x = (-(app->player->Player->body->GetPosition().x * 150) + 630);
	if (app->player->entityStatePlayer == GameState::OutOfCombat)
	{
		app->render->camera.x = (-(app->player->Player->body->GetPosition().x * 100) + 630);
		app->render->camera.y = (-(app->player->Player->body->GetPosition().y * 100) + 360);
	}

	if (app->render->camera.y < -app->map->levelAreaLowerBound * 2 + 720) app->render->camera.y = -app->map->levelAreaLowerBound * 2 + 720; //720 * 3
	if (app->render->camera.y > -app->map->levelAreaUpperBound * 2) app->render->camera.y = -app->map->levelAreaUpperBound * 2;

	if (app->render->camera.x < -app->map->levelAreaRightBound * 2 + 1280) app->render->camera.x = -app->map->levelAreaRightBound * 2 + 1280;
	if (app->render->camera.x > -app->map->levelAreaLeftBound * 2) app->render->camera.x = -app->map->levelAreaLeftBound * 2;
	

	if (app->player->destroyedDelay > 210 && app->player->destroyedDelay <= 211)
	{
		//Mix_ResumeMusic();
		//Mix_SetMusicPosition(0);
		// Load music
		//app->audio->PlayMusic("Assets/audio/music/jungle.ogg");

		if(app->player->lives != 0) playerRestart = true;
		if (app->player->lives == 0) app->titleScreen->toTitleScreen = true;
	}

	if (app->player->winDelay > 300 && app->player->winDelay <= 301)
	{
		app->titleScreen->Enable();

		app->player->Disable();
		app->sceneMainMap->Disable();
		app->collisions->Disable();
		app->map->Disable();
		app->entity_manager->Disable();
		app->particles->Disable();
		app->fonts->Disable();
		//app->physics->Disable();

		//playerRestart = true;
	}

	if (app->player->exitActivated == true)
	{
		app->player->exitActivated = false;

		app->player->Disable();
		//app->sceneMotel->Disable();
		app->collisions->Disable();
		app->map->Disable();
		app->entity_manager->Disable();
		app->particles->Disable();
		app->fonts->Disable();
		app->pause_menu->Disable();
		app->sceneMotel->Disable();

		if (app->player->entranceID == 2)
		{
			app->sceneCave->enableSceneMotel = false;

			enableSceneCave = true;
		}


		//app->fade->FadeToBlack(app->sceneMainMap, app->sceneCave, 60.0f);
	}
	
	return ret;
}

// Called before quitting
bool SceneMotel::CleanUp()
{
	LOG("Freeing scene");
	destroyScene = true;
	sceneMotel = false;

	return true;
}
