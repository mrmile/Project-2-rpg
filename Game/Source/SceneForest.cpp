#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneCastle.h"
#include "SceneForest.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include "TitleScreen.h"
#include "Enemies.h"
#include "Enemy.h"
#include "ModuleParticles.h"
#include "ModuleFonts.h"
#include "PauseMenu.h"

#include "Defs.h"
#include "Log.h"
#include <SDL_mixer/include/SDL_mixer.h>

SceneForest::SceneForest(bool start_enabled) : Module(start_enabled)
{
	name.Create("SceneForest");
}

// Destructor
SceneForest::~SceneForest()
{}

// Called before render is available
bool SceneForest::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool SceneForest::Start()
{
	// L03: DONE: Load map
	//app->map->Load("hello.tmx");
	app->map->Load("test_map.tmx");
	Mix_ResumeMusic();
	Mix_SetMusicPosition(0);
	// Load music
	app->audio->PlayMusic("Assets/audio/music/jungle.ogg");
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

	app->render->camera.x = app->map->MapToWorld(-0, -75).x;
	app->render->camera.y = app->map->MapToWorld(-0, -75).y;

	 godMode = false;
	 playerRestart = false;
	 destroyScene = false;
	 sceneForest = true;
	
	 app->sceneCastle->sceneCastle = false;

	// app->titleScreen->transition = false;
	// app->titleScreen->continueTransition = false;
	

	return true;
}

// Called each loop iteration
bool SceneForest::PreUpdate()
{
	if (app->titleScreen->GameHasContinued == true)
	{
		app->LoadGameRequest();
		app->titleScreen->GameHasContinued = false;
	}

	return true;
}

// Called each loop iteration
bool SceneForest::Update(float dt)
{
	sceneTimer++;
	//F9 --> See colliders
	

	if ((app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN && app->player->destroyed == false && app->player->playerWin == false))
	{
		app->player->checkPointReached = false;
		playerRestart = true;
	}
	

	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN && app->player->destroyed == false && app->player->playerWin == false)
		godMode = !godMode;

    // L02: DONE 3: Request Load / Save when pressing L/S
	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN && app->player->destroyed == false && app->player->playerWin == false)
	{
		app->LoadGameRequest();
	}
		

	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN && app->player->destroyed == false && app->player->playerWin == false)
	{
		app->titleScreen->SavedGame = true;
		app->SaveGameRequest();
	}
		

	//if(app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		//app->render->camera.y -= 5;

	//if(app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		//app->render->camera.y += 5;

	//if(app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		//app->render->camera.x -= 5;

	//if(app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		//app->render->camera.x += 5;

	//app->render->DrawTexture2(img, 380, 100); // Placeholder not needed any more
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
bool SceneForest::PostUpdate()
{
	bool ret = true;


	if (app->player->horizontalCB == false && app->player->bidimensionalCB == false && sceneTimer > 1) app->render->camera.x = (-(app->player->Player->body->GetPosition().x * 150) + 630);
	
	if (-app->player->position.y > app->render->camera.y / 2 + -52) app->render->camera.y += 10;
	if (-app->player->position.y < app->render->camera.y / 2 + -92) app->render->camera.y -= 10;

	

	if (app->render->camera.y < -app->map->levelAreaLowerBound * 3 + 720) app->render->camera.y = -app->map->levelAreaLowerBound * 3 + 720; //720 * 3
	if (app->render->camera.y > -app->map->levelAreaUpperBound * 3) app->render->camera.y = -app->map->levelAreaUpperBound * 3;

	if (app->render->camera.x < -app->map->levelAreaRightBound * 3 + 1280) app->render->camera.x = -app->map->levelAreaRightBound * 3 + 1280;
	if (app->render->camera.x > -app->map->levelAreaLeftBound * 3) app->render->camera.x = -app->map->levelAreaLeftBound * 3;

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
		app->sceneForest->Disable();
		app->collisions->Disable();
		app->map->Disable();
		app->enemies->Disable();
		app->particles->Disable();
		app->fonts->Disable();
		//app->physics->Disable();

		//playerRestart = true;
	}

	
	return ret;
}

// Called before quitting
bool SceneForest::CleanUp()
{
	LOG("Freeing scene");
	destroyScene = true;
	sceneForest = false;

	return true;
}
