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

#include "Defs.h"
#include "Log.h"
#include <SDL_mixer/include/SDL_mixer.h>

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

	godMode = false;
	playerRestart = false;
	destroyScene = false;
	sceneCave = true;
	app->sceneMainMap->sceneMainMap = false;
	enableSceneMainMap = false;

	app->render->camera.x = app->map->MapToWorld(0, 0).x;
	app->render->camera.y = app->map->MapToWorld(0, 0).y;

	sceneTimer = 0;

	

	

	return true;
}

// Called each loop iteration
bool SceneCave::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool SceneCave::Update(float dt)
{
	sceneTimer++;
	
	//app->render->camera.x = -(app->player->Player->body->GetPosition().x * 100) + 640;
	//app->render->camera.x = -(app->player->Player->body->GetPosition().x * 100) + 160; //<-- Este es el que se aplica al final

	//F9 --> See colliders

	if ((app->input->keys[SDL_SCANCODE_F3] == KEY_DOWN || app->input->keys[SDL_SCANCODE_F1] == KEY_DOWN && app->player->destroyed == false && app->player->playerWin == false))
	{
		app->player->checkPointReached = false;
		playerRestart = true;
	}


	if (app->input->keys[SDL_SCANCODE_F10] == KEY_DOWN && app->player->destroyed == false && app->player->playerWin == false)
		godMode = !godMode;

	// L02: DONE 3: Request Load / Save when pressing L/S
	if (app->input->keys[SDL_SCANCODE_F6] == KEY_DOWN && app->player->destroyed == false && app->player->playerWin == false)
		app->LoadGameRequest();

	if (app->input->keys[SDL_SCANCODE_F5] == KEY_DOWN && app->player->destroyed == false && app->player->playerWin == false)
		app->SaveGameRequest();

	//if(app->input->keys[SDL_SCANCODE_S) == KEY_REPEAT)
		//app->render->camera.y -= 5;

	//if(app->input->keys[SDL_SCANCODE_W) == KEY_REPEAT)
		//app->render->camera.y += 5;

	//if(app->input->keys[SDL_SCANCODE_D) == KEY_REPEAT)
		//app->render->camera.x -= 5;

	//if(app->input->keys[SDL_SCANCODE_A) == KEY_REPEAT)
		//app->render->camera.x += 5;

	//if(sceneTimer <= 1) app->map->LoadCollidersSensors();

	//app->render->DrawTexture(img, 380, 100); // Placeholder not needed any more

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

	// L03: DONE 7: Set the window title with map/tileset info
	/*
	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
				   app->map->mapData.width, app->map->mapData.height,
				   app->map->mapData.tileWidth, app->map->mapData.tileHeight,
				   app->map->mapData.tilesets.count());
	*/

	//app->win->SetTitle(title.GetString());

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

		if (app->player->entranceID == 1) enableSceneMainMap = true;


		//app->fade->FadeToBlack(app->sceneMainMap, app->sceneCave, 60.0f);
	}

	return ret;
}

// Called before quitting
bool SceneCave::CleanUp()
{
	LOG("Freeing scene");

	//app->sceneCave_game->holeSensor3->body->DestroyFixture(app->sceneCave_game->holeSensor3->body->GetFixtureList());
	//app->collisions->RemoveCollider(app->collisions->AddCollider({ app->map->MapToWorldSingle(0), app->map->MapToWorldSingle(0), app->map->MapToWorldSingle(1200), app->map->MapToWorldSingle(100) }, Collider::Type::NULL_COLLIDER));
	//app->collisions->RemoveCollider(app->collisions->AddCollider({ app->map->MapToWorldSingle(0), app->map->MapToWorldSingle(16), app->map->MapToWorldSingle(19), app->map->MapToWorldSingle(7) }, Collider::Type::EXIT_2));
	//app->collisions->RemoveCollider(app->collisions->AddCollider({ app->map->MapToWorldSingle(118), app->map->MapToWorldSingle(13), app->map->MapToWorldSingle(10), app->map->MapToWorldSingle(10) }, Collider::Type::EXIT_2));

	//app->collisions->RemoveCollider(app->collisions->AddCollider({ app->map->MapToWorldSingle(0), app->map->MapToWorldSingle(0), app->map->MapToWorldSingle(1200), app->map->MapToWorldSingle(100) }, Collider::Type::NULL_COLLIDER));

	//app->map->DeleteCollidersSensors();
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