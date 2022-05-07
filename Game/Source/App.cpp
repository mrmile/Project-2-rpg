#include "App.h"
#include "Window.h"
#include "Input.h"
#include "GamepadInput.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "SceneMainMap.h"
#include "SceneCave.h"
#include "CreditsScreen.h"
#include "SceneBase.h"
#include "SceneMotel.h"
#include "Map.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "TitleScreen.h"
#include "Defs.h"
#include "Log.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Pathfinding.h"
#include "GuiManager.h"
#include "LogoScreen.h"
#include "PauseMenu.h"
#include "InventoryMenu.h"
#include "CombatMenu.h"
#include "DialogManager.h"
#include "GameManager.h"

#include <iostream>
#include <sstream>
#include <Optick/include/optick.h>
#include <SDL_mixer/include/SDL_mixer.h>

// Constructor
App::App(int argc, char* args[]) : argc(argc), args(args)
{
	PERF_START(ptimer);

	frames = 0;

	win = new Window(true);
	input = new Input(true);
	gamepadInput = new GamepadInput(true);
	render = new Render(true);
	tex = new Textures(true);
	audio = new Audio(true);
	logoScreen = new LogoScreen(true);
	titleScreen = new TitleScreen(false);
	creditsScreen = new CreditsScreen(false);
	sceneMainMap = new SceneMainMap(false);
	sceneCave = new SceneCave(false);
	sceneBase = new SceneBase(false);
	sceneMotel = new SceneMotel(false);
	map = new Map(false);
	physics = new ModulePhysics(true);
	fade = new ModuleFadeToBlack(true);
	player = new ModulePlayer(false);
	collisions = new ModuleCollisions(false);
	pause_menu = new PauseMenu(false);
	inventoryMenu = new InventoryMenu(true);
	combatMenu = new CombatMenu(true);
	entity_manager = new EntityManager(true);
	particles = new ModuleParticles(true);
	pathfinding = new PathFinding(false);
	fonts = new ModuleFonts(false);
	guiManager = new GuiManager(true);
	dialogManager = new DialogManager(true);
	game_manager = new GameManager(true);

	// Ordered for awake / Start / Update
	// Reverse order of CleanUp
	AddModule(win);
	AddModule(input);
	AddModule(gamepadInput);
	AddModule(tex);
	AddModule(audio);
	AddModule(physics);
	AddModule(map);
	AddModule(logoScreen);
	AddModule(titleScreen);
	AddModule(creditsScreen);
	AddModule(sceneMainMap);
	AddModule(sceneCave);
	AddModule(sceneBase);
	AddModule(sceneMotel);
	AddModule(fonts);
	AddModule(player);
	AddModule(entity_manager); 
	AddModule(particles);
	AddModule(collisions);
	AddModule(fade);
	AddModule(pathfinding);
	AddModule(pause_menu);
	AddModule(inventoryMenu);
	AddModule(combatMenu);
	AddModule(dialogManager);
	AddModule(guiManager);
	AddModule(game_manager);
	// Render last to swap buffer
	AddModule(render);

	PERF_PEEK(ptimer);
}

// Destructor
App::~App()
{
	// Release modules
	ListItem<Module*>* item = modules.end;

	while(item != NULL)
	{
		RELEASE(item->data);
		item = item->prev;
	}

	modules.clear();
}

void App::AddModule(Module* module)
{
	module->Init();
	modules.add(module);
}

// Called before render is available
bool App::Awake()
{
	PERF_START(ptimer);

	pugi::xml_document configFile;
	pugi::xml_node config;
	pugi::xml_node configApp;

	bool ret = false;

	// L01: DONE 3: Load config from XML
	config = LoadConfig(configFile);

	if (config.empty() == false)
	{
		ret = true;
		configApp = config.child("app");

		// L01: DONE 4: Read the title from the config file
		title.Create(configApp.child("title").child_value());
		organization.Create(configApp.child("organization").child_value());

		// L08: TODO 1: Read from config file your framerate cap

	}

	if (ret == true)
	{
		ListItem<Module*>* item;
		item = modules.start;

		while ((item != NULL) && (ret == true))
		{
			// L01: DONE 5: Add a new argument to the Awake method to receive a pointer to an xml node.
			// If the section with the module name exists in config.xml, fill the pointer with the valid xml_node
			// that can be used to read all variables for that module.
			// Send nullptr if the node does not exist in config.xml
			ret = item->data->Awake(config.child(item->data->name.GetString()));
			item = item->next;
		}
	}

	PERF_PEEK(ptimer);

	return ret;
}

// Called before the first frame
bool App::Start()
{
	PERF_START(ptimer);

	startupTime.Start();
	lastSecFrameTime.Start();

	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;

	while(item != NULL && ret == true)
	{
		if (item->data->IsEnabled() == true)
			ret = item->data->Start();
		item = item->next;
	}

	PERF_PEEK(ptimer);

	return ret;
}

// Called each loop iteration
bool App::Update()
{
	OPTICK_EVENT();

	ListItem<Module*>* item = modules.start;

	bool ret = true;
	PrepareUpdate();

	if(input->GetWindowEvent(WE_QUIT) == true)
		ret = false;

	if (input->GetWindowEvent(WE_QUIT) == true)
		ret = false;

	if (ret == true)
		ret = PreUpdate();

	if (ret == true)
		ret = DoUpdate();

	if (ret == true)
		ret = PostUpdate();

	FinishUpdate();
	return ret;
}

// Load config from XML file
// NOTE: Function has been redesigned to avoid storing additional variables on the class
pugi::xml_node App::LoadConfig(pugi::xml_document& configFile) const
{
	pugi::xml_node ret;

	pugi::xml_parse_result result = configFile.load_file(CONFIG_FILENAME);

	if (result == NULL) LOG("Could not load xml file: %s. pugi error: %s", CONFIG_FILENAME, result.description());
	else ret = configFile.child("config");

	return ret;
}

// ---------------------------------------------
void App::PrepareUpdate()
{
	frameCount++;
	lastSecFrameCount++;

	AppTitleScreenFull = app->titleScreen->FullScreen;
	//AppTitleScreenFull = app->pause_menu->FullScreen;
	// L08: TODO 4: Calculate the dt: differential time since last frame

}

// ---------------------------------------------
void App::FinishUpdate()
{
	// L02: DONE 1: This is a good place to call Load / Save methods
	if (loadGameRequested == true) LoadGame();
	if (saveGameRequested == true) SaveGame();
	if (checkGameRequested == true) CheckGame();
	
	if (app->player->deletePlayer == true) // Usar solo esto menos en el Load/Save Game
	{
		app->player->Player->body->DestroyFixture(app->player->Player->body->GetFixtureList());

		//if(app->sceneCave->playerRestart == true || app->sceneMainMap->playerRestart == true) app->player->Player = app->physics->CreatePlayerBox(app->player->position.x, app->player->position.y, 28, 33);

		app->player->deletePlayer = false;
	}

	if (app->sceneMainMap->destroyScene == true) // Tiene que borrar todos los chains del box2D y los sensores de colisiones del método antiguo que están en el nivel
	{
		// Borra los chains
		for (int i = 0; i < app->map->mapChainsCounter; i++)
		{
			app->map->mapChains[i]->body->DestroyFixture(app->map->mapChains[i]->body->GetFixtureList());
		}

		// Borra los sensores
		app->map->DeleteCollidersSensors();

		app->sceneMainMap->destroyScene = false;
	}

	if (app->sceneCave->destroyScene == true) // Tiene que borrar todos los chains del box2D y los sensores de colisiones del método antiguo que están en el nivel
	{
		// Borra los chains
		for (int i = 0; i < app->map->mapChainsCounter; i++)
		{
			app->map->mapChains[i]->body->DestroyFixture(app->map->mapChains[i]->body->GetFixtureList());
		}

		// Borra los sensores
		app->map->DeleteCollidersSensors();

		app->sceneCave->destroyScene = false;
	}

	if (app->sceneBase->destroyScene == true) // Tiene que borrar todos los chains del box2D y los sensores de colisiones del método antiguo que están en el nivel
	{
		// Borra los chains
		for (int i = 0; i < app->map->mapChainsCounter; i++)
		{
			app->map->mapChains[i]->body->DestroyFixture(app->map->mapChains[i]->body->GetFixtureList());
		}

		// Borra los sensores
		app->map->DeleteCollidersSensors();

		app->sceneBase->destroyScene = false;
	}

	if (app->sceneMotel->destroyScene == true) // Tiene que borrar todos los chains del box2D y los sensores de colisiones del método antiguo que están en el nivel
	{
		// Borra los chains
		for (int i = 0; i < app->map->mapChainsCounter; i++)
		{
			app->map->mapChains[i]->body->DestroyFixture(app->map->mapChains[i]->body->GetFixtureList());
		}

		// Borra los sensores
		app->map->DeleteCollidersSensors();

		app->sceneMotel->destroyScene = false;
	}

	if (app->sceneCave->enableSceneMainMap == true || app->sceneBase->enableSceneMainMap == true)
	{
		app->sceneBase->Disable();
		app->sceneCave->Disable();
		app->collisions->Enable();
		app->map->Enable();
		app->particles->Enable();
		app->sceneMainMap->Enable();
		app->player->Enable();
		app->entity_manager->Enable();
		app->fonts->Enable();
		app->pause_menu->Enable();

		app->sceneCave->enableSceneMainMap = false;
		app->sceneBase->enableSceneMainMap = false;
	}

	if (app->sceneCave->enableSceneMotel == true)
	{
		//app->sceneBase->Disable();
		app->sceneCave->Disable();
		app->collisions->Enable();
		app->map->Enable();
		app->particles->Enable();
		app->sceneMotel->Enable();
		app->player->Enable();
		app->entity_manager->Enable();
		app->fonts->Enable();
		app->pause_menu->Enable();

		app->sceneCave->enableSceneMotel = false;
	}

	if (app->sceneMainMap->enableSceneCave == true)
	{
		//app->sceneBase->Disable();
		app->sceneMainMap->Disable();
		app->collisions->Enable();
		app->map->Enable();
		app->sceneCave->Enable();
		app->particles->Enable();
		app->player->Enable();
		app->entity_manager->Enable();
		app->fonts->Enable();
		app->pause_menu->Enable();

		app->sceneMainMap->enableSceneCave = false;
	}

	if (app->sceneMainMap->enableSceneBase == true)
	{
		app->sceneMainMap->Disable();
		//app->sceneCave->Disable();
		app->collisions->Enable();
		app->map->Enable();
		app->sceneBase->Enable();
		app->particles->Enable();
		app->player->Enable();
		app->entity_manager->Enable();
		app->fonts->Enable();
		app->pause_menu->Enable();

		app->sceneMainMap->enableSceneBase = false;
	}

	// L07: DONE 4: Now calculate:
   // Amount of frames since startup
   // Amount of time since game start (use a low resolution timer)
   // Average FPS for the whole game life
   // Amount of ms took the last update
   // Amount of frames during the last second
	float secondsSinceStartup = startupTime.ReadSec();

	if (lastSecFrameTime.Read() > 1000) {
		lastSecFrameTime.Start();
		framesPerSecond = lastSecFrameCount;
		lastSecFrameCount = 0;
		averageFps = (averageFps + framesPerSecond) / 2;
	}

	static char title[256];
	sprintf_s(title, 256, "Av.FPS: %.2f Last sec frames: %i Last dt: %.3f Time since startup: %.3f Frame Count: %I64u ",
		averageFps, framesPerSecond, dt, secondsSinceStartup, frameCount);

	// L08: TODO 2: Use SDL_Delay to make sure you get your capped framerate

	// L08: TODO 3: Measure accurately the amount of time SDL_Delay() actually waits compared to what was expected

	app->win->SetTitle(title);
}

// Call modules before each loop iteration
bool App::PreUpdate()
{
	bool ret = true;

	ListItem<Module*>* item;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->PreUpdate();
	}

	return ret;
}

// Call modules on each loop iteration
bool App::DoUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		// L08: TODO 5: Send dt as an argument to all updates (DONE?)
		ret = item->data->Update(dt);
	}

	return ret;
}

// Call modules after each loop iteration
bool App::PostUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	Module* pModule = NULL;

	int test = 0;
	//LOG("POST UPDATING GENERAL");
	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		//LOG("POST UPDATING MODULE NUMBER: %i", test);
		test++;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->PostUpdate();

		
	}

	return ret;
}

// Called before quitting
bool App::CleanUp()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.end;

	while(item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}

	return ret;
}

// ---------------------------------------
int App::GetArgc() const
{
	return argc;
}

// ---------------------------------------
const char* App::GetArgv(int index) const
{
	if(index < argc)
		return args[index];
	else
		return NULL;
}

// ---------------------------------------
const char* App::GetTitle() const
{
	return title.GetString();
}

// ---------------------------------------
const char* App::GetOrganization() const
{
	return organization.GetString();
}

// Load / Save
void App::LoadGameRequest()
{
	// NOTE: We should check if SAVE_STATE_FILENAME actually exist
	loadGameRequested = true;
}
// ---------------------------------------
void App::SaveGameRequest() const
{
	// NOTE: We should check if SAVE_STATE_FILENAME actually exist and... should we overwriten
	saveGameRequested = true;
	app->titleScreen->SavedGame = true;
}


//TRY FOR CHECKING SAVE
void App::CheckGameRequest() 
{
	// NOTE: We should check if SAVE_STATE_FILENAME actually exist and... should we overwriten
	checkGameRequested = true;
}
void::App::SaveGameAudio()
{
	saveGameAudioRequested = true;
}

// ---------------------------------------
// L02: DONE 5: Create a method to actually load an xml file
// then call all the modules to load themselves
bool App::LoadGame()
{
	bool ret = true;

	pugi::xml_document gameStateFile;
	pugi::xml_parse_result result = gameStateFile.load_file("save_game.xml");

	if (result == NULL)
	{
		LOG("Could not load xml file save_game.xml. pugi error: %s", result.description());
		ret = false;
	}
	else
	{
		ListItem<Module*>* item;
		item = modules.start;

		while (item != NULL && ret == true)
		{
			ret = item->data->LoadState(gameStateFile.child("save_state").child(item->data->name.GetString()));
			item = item->next;
		}
	}

	loadGameRequested = false;

	return ret;
}

bool App::CheckGame()
{
	bool ret = true;

	pugi::xml_document gameStateFile;
	pugi::xml_parse_result result = gameStateFile.load_file("save_game.xml");

	if (result == NULL)
	{
		LOG("Could not load xml file save_game.xml. pugi error: %s", result.description());
		ret = false;
	}
	else
	{
		ListItem<Module*>* item;
		item = modules.start;

		while (item != NULL && ret == true)
		{
			ret = item->data->CheckSave(gameStateFile.child("save_state").child(item->data->name.GetString()));
			item = item->next;
		}
	}

	checkGameRequested = false;

	return ret;
}


//------------------------------------------------------------------------------
// L02: DONE 7: Implement the xml save method for current state
bool App::SaveGame() const
{
	bool ret;

	pugi::xml_document* saveDoc = new pugi::xml_document();
	pugi::xml_node saveStateNode = saveDoc->append_child("save_state");

	ListItem<Module*>* item;
	item = modules.start;

	while (item != NULL)
	{
		ret = item->data->SaveState(saveStateNode.append_child(item->data->name.GetString()));
		item = item->next;
	}

	ret = saveDoc->save_file("save_game.xml");

	saveGameRequested = false;

	return ret;
}
bool App::SaveAudio() 
{
	bool ret = true;

	pugi::xml_document gameStateFile;
	pugi::xml_parse_result result = gameStateFile.load_file("save_game.xml");

	if (result == NULL)
	{
		LOG("Could not load xml file save_game.xml. pugi error: %s", result.description());
		ret = false;
	}
	else
	{
		ListItem<Module*>* item;
		item = modules.start;

		while (item != NULL && ret == true)
		{
			ret = item->data->CheckAudioSave(gameStateFile.child("save_state").child(item->data->name.GetString()));
			item = item->next;
		}
	}

	saveGameAudioRequested = false;

	return ret;
}




