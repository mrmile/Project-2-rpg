#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneCastle.h"
#include "SceneMainMap.h"
#include "DrawInOrder.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include "TitleScreen.h"
#include "EntityManager.h"
#include "Entity.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "PauseMenu.h"
#include "Pathfinding.h"

#include "Defs.h"
#include "Log.h"
#include <SDL_mixer/include/SDL_mixer.h>

DrawInOrder::DrawInOrder(bool start_enabled) : Module(start_enabled)
{
	name.Create("SceneMainMap");
}

// Destructor
DrawInOrder::~DrawInOrder()
{}

// Called before render is available
bool DrawInOrder::Awake()
{
	LOG("Drawing in order start");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool DrawInOrder::Start()
{
	

	return true;
}

// Called each loop iteration
bool DrawInOrder::PreUpdate()
{
	

	return true;
}

// Called each loop iteration
bool DrawInOrder::Update(float dt)
{

	

	return true;
}

// Called each loop iteration
bool DrawInOrder::PostUpdate()
{

	
	return true;
}

// Called before quitting
bool DrawInOrder::CleanUp()
{
	LOG("Freeing DrawInOrder memory (don't really know)");


	return true;
}
