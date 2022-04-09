#include "TitleScreen.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "ModuleParticles.h"
#include "ModuleFonts.h"
#include "LogoScreen.h"

#include "Defs.h"
#include "Log.h"

#include <SDL_mixer/include/SDL_mixer.h>
#include <iostream>
using namespace std;

LogoScreen::LogoScreen(bool start_enabled) : Module(start_enabled)
{
	name.Create("LogoScreen");
}

LogoScreen::~LogoScreen()
{
}

bool LogoScreen::Awake()
{
	LOG("LogoScreen Scene");
	bool ret = true;

	return ret;

	return true;
}

bool LogoScreen::Start()
{
	logoScreen = app->tex->Load("Assets/textures/Scenes/logoScreen.png");

	app->audio->PlayMusic("Assets/audio/music/logoMusic.ogg");

	delay = 0;

	return true;
}

bool LogoScreen::PreUpdate()
{

	return true;
}

bool LogoScreen::Update(float dt)
{
	delay++;

	if (delay > 360 || app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		app->titleScreen->Enable();

		app->logoScreen->Disable();
	}

	return true;
}

bool LogoScreen::PostUpdate()
{
	bool ret = true;

	app->render->DrawTexture2(logoScreen, 0, 0, NULL);

	return ret;
	
	//return true;
}

bool LogoScreen::CleanUp()
{
	
	return true;
}

