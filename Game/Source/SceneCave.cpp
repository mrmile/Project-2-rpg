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
#include "TitleScreen.h"
#include "ModuleFonts.h"
#include "PauseMenu.h"
#include "EntityManager.h"
#include "Entity.h"
#include "ModuleParticles.h"
#include "SceneBase.h"

#include "Defs.h"
#include "Log.h"
#include <SDL_mixer/include/SDL_mixer.h>

#include <Time.h>

SceneCave::SceneCave(bool start_enabled) : Module(start_enabled)
{
	name.Create("SceneCave");
}

// Destructor
SceneCave::~SceneCave()
{}

// Called before render is available
bool SceneCave::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool SceneCave::Start()
{
	app->map->Load("cave.tmx");

	spotLight = app->tex->Load("Assets/textures/Particles/spotlight.png");

	cave_bg_noise1 = app->audio->LoadFx("Assets/audio/fx/TerrorSurroundingSounds/cave/cave_bg_noise1.wav");
	cave_bg_noise2 = app->audio->LoadFx("Assets/audio/fx/TerrorSurroundingSounds/cave/cave_bg_noise2.wav");
	cave_bg_noise3 = app->audio->LoadFx("Assets/audio/fx/TerrorSurroundingSounds/cave/cave_bg_noise3.wav");
	cave_bg_noise4 = app->audio->LoadFx("Assets/audio/fx/TerrorSurroundingSounds/cave/cave_bg_noise4.wav");
	cave_bg_noise5 = app->audio->LoadFx("Assets/audio/fx/TerrorSurroundingSounds/cave/cave_bg_noise5.wav");

	godMode = false;
	playerRestart = false;
	destroyScene = false;
	sceneCave = true;
	app->sceneMainMap->sceneMainMap = false;
	enableSceneMainMap = false;

	app->render->camera.x = app->map->MapToWorld(0, 0).x;
	app->render->camera.y = app->map->MapToWorld(0, 0).y;

	sceneTimer = 0;

	sceneSoundRandomizerNumber = 0;


	/*app->render->mFogOfWar->w = 1920;
	app->render->mFogOfWar->h = 1080;

	app->render->mFogOfWarPunch->w = 300;
	app->render->mFogOfWarPunch->h = 300;*/

	//app->SaveGameRequest();

	return true;
}

// Called each loop iteration
bool SceneCave::PreUpdate()
{
	/*if (app->titleScreen->GameHasContinued == true)
	{
		app->LoadGameRequest();
		app->titleScreen->GameHasContinued = false;
	}*/

	srand(time(NULL));

	return true;
}

// Called each loop iteration
bool SceneCave::Update(float dt)
{
	sceneTimer++;
	
	//app->render->camera.x = -(app->player->Player->body->GetPosition().x * 100) + 640;
	//app->render->camera.x = -(app->player->Player->body->GetPosition().x * 100) + 160; //<-- Este es el que se aplica al final

	//F9 --> See colliders




	if (app->input->keys[SDL_SCANCODE_F10] == KEY_DOWN && app->player->destroyed == false && app->player->playerWin == false)
		godMode = !godMode;

	/*
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
   */


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

	sceneSoundRandomizerNumber = rand() % 5;

	return true;
}

// Called each loop iteration
bool SceneCave::PostUpdate()
{
	bool ret = true;

	if (sceneTimer <= 2)
	{
		app->audio->ChangeMusic(CAVE, 0.5f, 0.5f);
	}

	if (sceneTimer % 720 == 0 && sceneTimer > 5 && app->player->pauseMenu == false)
	{
		if (sceneSoundRandomizerNumber == 0) app->audio->PlayFx(cave_bg_noise1);
		if (sceneSoundRandomizerNumber == 1) app->audio->PlayFx(cave_bg_noise2);
		if (sceneSoundRandomizerNumber == 2) app->audio->PlayFx(cave_bg_noise3);
		if (sceneSoundRandomizerNumber == 3) app->audio->PlayFx(cave_bg_noise4);
		if (sceneSoundRandomizerNumber == 4) app->audio->PlayFx(cave_bg_noise5);

	}

	// L08: TODO 6: Make the camera movement independent of framerate

	//if (app->player->horizontalCB == false && sceneTimer > 1) app->render->camera.x = -(app->player->Player->body->GetPosition().x * 100) + 630;

	app->render->camera.x = (-(app->player->Player->body->GetPosition().x * 100) + 630);
	app->render->camera.y = (-(app->player->Player->body->GetPosition().y * 100) + 360);

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

		if (app->player->lives != 0) playerRestart = true;
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
		//app->physics->Disable();

		//playerRestart = true;
	}

	if (app->player->exitActivated == true)
	{
		app->player->exitActivated = false;

		app->player->Disable();
		//app->sceneMainMap->Disable();
		app->collisions->Disable();
		app->map->Disable();
		app->entity_manager->Disable();
		app->particles->Disable();
		app->fonts->Disable();
		app->pause_menu->Disable();
		app->sceneCave->Disable();

		if (app->player->entranceID == 1)
		{
			app->sceneBase->enableSceneMainMap = false;
			app->sceneMainMap->enableSceneBase = false;
			app->sceneMainMap->enableSceneCave = false;

			enableSceneMainMap = true;
		}


		//app->fade->FadeToBlack(app->sceneMainMap, app->sceneCave, 60.0f);
	}

	return ret;
}

// Called before quitting
bool SceneCave::CleanUp()
{
	LOG("Freeing scene");

	app->tex->UnLoad(spotLight);

	destroyScene = true;
	sceneCave = false;

	return true;
}

/*
void Scene::b2dOnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (bodyA != nullptr && bodyB != nullptr)
	{
		b2Filter filter;
		filter.categoryBits = 0x0001;
		filter.maskBits = 0x0001;

		if (bodyB->body == app->player->Player->body && bodyA->body == app->sceneCave->h_CB1->body)
		{

			filter.categoryBits = 0x0002;
			filter.maskBits = 0x0002 | 0x0001;

			//b2Vec2 position;
			//position.x = 688;
			//position.y = 820;

			LOG("Player Collision");
			//app->player->Player->body->GetFixtureList()->SetFilterData(filter);
			//app->player->player->body->DestroyFixture();

			if (app->player->horizontalCB == false)
			{
				app->player->horizontalCB = true;
			}
			
		}
		else if (bodyB->body == app->player->Player->body && bodyA->body != app->sceneCave->h_CB1->body)
		{
			if (app->player->horizontalCB == true)
			{
				app->player->horizontalCB = false;
			}
		}
	}
}
*/