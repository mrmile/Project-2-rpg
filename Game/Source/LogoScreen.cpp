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
	logoAnimationP1 = app->tex->Load("Assets/textures/Scenes/LogoAnimationFrames/logo_animation_p1.png");
	logoAnimationP2 = app->tex->Load("Assets/textures/Scenes/LogoAnimationFrames/logo_animation_p2.png");
	logoAnimationP3 = app->tex->Load("Assets/textures/Scenes/LogoAnimationFrames/logo_animation_p3.png");
	logoAnimationP4 = app->tex->Load("Assets/textures/Scenes/LogoAnimationFrames/logo_animation_p4.png");
	logoAnimationP5 = app->tex->Load("Assets/textures/Scenes/LogoAnimationFrames/logo_animation_p5.png");
	logoAnimationP6 = app->tex->Load("Assets/textures/Scenes/LogoAnimationFrames/logo_animation_p6.png");
	logoAnimationP7 = app->tex->Load("Assets/textures/Scenes/LogoAnimationFrames/logo_animation_p7.png");
	logoAnimationP8 = app->tex->Load("Assets/textures/Scenes/LogoAnimationFrames/logo_animation_p8.png");


	app->audio->ChangeMusic(LOGO_INTRO, 0, 0);

	delay = 0;
	animationPositionY = 0;
	logoPart = 1;

	return true;
}

bool LogoScreen::PreUpdate()
{

	return true;
}

bool LogoScreen::Update(float dt)
{
	delay++;

	if (delay > 360 || app->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN)
	{
		app->titleScreen->Enable();

		app->entity_manager->Disable();
		app->logoScreen->Disable();
	}

	if (logoPart < 9)
	{
		if (delay % 2 == 0)animationPositionY = animationPositionY - 360;
		if (animationPositionY <= -3240)
		{
			if (logoPart < 9)animationPositionY = 0;
			logoPart++;
		}
	}

	return true;
}

bool LogoScreen::PostUpdate()
{
	//bool ret = true;

		
	if (logoPart == 1) app->render->DrawTexture2(logoAnimationP1, 0, animationPositionY, NULL);
	if (logoPart == 2) app->render->DrawTexture2(logoAnimationP2, 0, animationPositionY, NULL);
	if (logoPart == 3) app->render->DrawTexture2(logoAnimationP3, 0, animationPositionY, NULL);
	if (logoPart == 4) app->render->DrawTexture2(logoAnimationP4, 0, animationPositionY, NULL);
	if (logoPart == 5) app->render->DrawTexture2(logoAnimationP5, 0, animationPositionY, NULL);
	if (logoPart == 6) app->render->DrawTexture2(logoAnimationP6, 0, animationPositionY, NULL);
	if (logoPart == 7) app->render->DrawTexture2(logoAnimationP7, 0, animationPositionY, NULL);
	if (logoPart == 8) app->render->DrawTexture2(logoAnimationP8, 0, animationPositionY, NULL);
	if (logoPart == 9) app->render->DrawTexture2(logoAnimationP8, 0, -2880, NULL);


	//return ret;
	
	return true;
}

bool LogoScreen::CleanUp()
{
	app->tex->UnLoad(logoAnimationP1);
	app->tex->UnLoad(logoAnimationP2);
	app->tex->UnLoad(logoAnimationP3);
	app->tex->UnLoad(logoAnimationP4);
	app->tex->UnLoad(logoAnimationP5);
	app->tex->UnLoad(logoAnimationP6);
	app->tex->UnLoad(logoAnimationP7);
	app->tex->UnLoad(logoAnimationP8);

	return true;
}

