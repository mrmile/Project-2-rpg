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
	logoScreen1 = app->tex->Load("Assets/textures/Scenes/logoScreen1.png");
	logoScreen10 = app->tex->Load("Assets/textures/Scenes/logoScreen10.png");
	logoScreen11 = app->tex->Load("Assets/textures/Scenes/logoScreen11.png");
	logoScreen12 = app->tex->Load("Assets/textures/Scenes/logoScreen12.png");
	logoScreen2 = app->tex->Load("Assets/textures/Scenes/logoScreen2.png");
	logoScreen3 = app->tex->Load("Assets/textures/Scenes/logoScreen3.png");

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

	if (delay < 80)
	{
		app->render->DrawTexture2(logoScreen10, 0, 0, NULL);
	}

	if (delay >= 80 && delay < 190)
	{
		app->render->DrawTexture2(logoScreen11, 0, 0, NULL);
	}

	if (delay >= 190 && delay < 230)
	{
		app->render->DrawTexture2(logoScreen12, 0, 0, NULL);
	}

	if (delay >= 230 && delay < 260)
	{
		app->render->DrawTexture2(logoScreen1, 0, 0, NULL);
	}

	if (delay >= 260 && delay < 280)
	{
		app->render->DrawTexture2(logoScreen3, 0, 0, NULL);
	}
	if (delay >= 280 && delay < 300)
	{
		app->render->DrawTexture2(logoScreen2, 0, 0, NULL);
	}
	if (delay >= 300 && delay < 320)
	{
		app->render->DrawTexture2(logoScreen3, 0, 0, NULL);
	}

	if (delay >= 320 && delay < 340)
	{
		app->render->DrawTexture2(logoScreen2, 0, 0, NULL);
	}

	if (delay >= 340 && delay <= 360)
	{
		app->render->DrawTexture2(logoScreen3, 0, 0, NULL);
	}

	return ret;
	
	//return true;
}

bool LogoScreen::CleanUp()
{
	app->tex->UnLoad(logoScreen1);
	app->tex->UnLoad(logoScreen10);
	app->tex->UnLoad(logoScreen11);
	app->tex->UnLoad(logoScreen12);
	app->tex->UnLoad(logoScreen2);
	app->tex->UnLoad(logoScreen3);

	return true;
}

