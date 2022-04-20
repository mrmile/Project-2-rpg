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
	LOG("Loading PauseMenu");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool CombatMenu::Start()
{
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
	return true;
}

// Called each loop iteration
bool CombatMenu::PostUpdate()
{
	bool ret = true;
	
	return true;
}

// Called before quitting
bool CombatMenu::CleanUp()
{
	return true;
}

bool CombatMenu::OnGuiMouseClickEvent(GuiControl* control) 
{
	return true;
}
