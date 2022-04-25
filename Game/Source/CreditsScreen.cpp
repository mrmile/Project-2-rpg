#include "TitleScreen.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "ModuleParticles.h"
#include "ModuleFonts.h"
#include "CreditsScreen.h"
#include "GuiManager.h"
#include "GuiButton.h"

#include "Defs.h"
#include "Log.h"

#include <SDL_mixer/include/SDL_mixer.h>
#include <iostream>
using namespace std;

CreditsScreen::CreditsScreen(bool start_enabled) : Module(start_enabled)
{
	name.Create("CreditsScreen");

	// zombies  animations

	idleAnim.PushBack({ 322, 1, 45, 48 });
	idleAnim.PushBack({ 254, 1, 32, 48 });
	idleAnim.PushBack({ 224, 1, 32, 48 });
	idleAnim.PushBack({ 187, 1, 36, 48 });
	idleAnim.PushBack({ 144, 1, 45, 48 });
	idleAnim.PushBack({ 104, 1, 41, 48 });
	idleAnim.PushBack({ 77, 1, 33, 48 });
	idleAnim.PushBack({ 41, 1, 41, 48 });
	idleAnim.PushBack({ 1, 1, 41, 48 });
	idleAnim.loop = true;
	idleAnim.speed = 0.05f;

	idleAnim1.PushBack({ 458, 0, 35, 38 });
	idleAnim1.PushBack({ 424, 0, 34, 38 });
	idleAnim1.PushBack({ 390, 0, 30, 38 });
	idleAnim1.PushBack({ 357, 0, 33, 38 });
	idleAnim1.PushBack({ 323, 0, 35, 38 });
	idleAnim1.PushBack({ 217, 0, 34, 38 });
	idleAnim1.PushBack({ 153, 0, 35, 38 });
	idleAnim1.PushBack({ 123, 0, 30, 38 });
	idleAnim1.PushBack({ 90, 0, 33, 38 });
	idleAnim1.PushBack({ 52, 0, 33, 38 });
	idleAnim1.PushBack({ 13, 0, 30, 38 });
	idleAnim1.loop = true;
	idleAnim1.speed = 0.05f;

	/*idleAnim2.PushBack({ 513, 0, 50, 40 });
	idleAnim2.PushBack({ 463, 0, 50, 40 });*/
	idleAnim2.PushBack({ 413, 0, 40, 40 });
	idleAnim2.PushBack({ 363, 0, 50, 40 });
	idleAnim2.PushBack({ 313, 0, 50, 40 });
	idleAnim2.PushBack({ 263, 0, 50, 40 });
	idleAnim2.PushBack({ 213, 0, 50, 40 });
	idleAnim2.PushBack({ 163, 0, 50, 40 });
	idleAnim2.PushBack({ 113, 0, 50, 40 });
	idleAnim2.PushBack({ 63, 0, 50, 40 });
	idleAnim2.PushBack({ 13, 0, 50, 40 });
	idleAnim2.loop = true;
	idleAnim2.speed = 0.05f;

	idleAnim3.PushBack({ 415, 0, 46, 39 });
	idleAnim3.PushBack({ 365, 0, 50, 39 });
	idleAnim3.PushBack({ 318, 0, 47, 39 });
	idleAnim3.PushBack({ 275, 0, 43, 39 });
	idleAnim3.PushBack({ 232, 0, 43, 39 });
	idleAnim3.PushBack({ 191, 0, 41, 39 });
	idleAnim3.PushBack({ 148, 0, 43, 39 });
	idleAnim3.PushBack({ 106, 0, 42, 39 });
	idleAnim3.PushBack({ 64, 0, 42, 39 });
	idleAnim3.PushBack({ 18, 0, 46, 39 });
	idleAnim3.loop = true;
	idleAnim3.speed = 0.05f;

	//Personatge corrent
	idleAnimPlayer.PushBack({ 368, 1, 36, 95 });
	idleAnimPlayer.PushBack({ 335, 1, 36, 95 });
	idleAnimPlayer.PushBack({ 301, 1, 35, 95 });
	idleAnimPlayer.PushBack({ 267, 1, 38, 95 });
	idleAnimPlayer.PushBack({ 231, 1, 38, 95 });
	idleAnimPlayer.PushBack({ 200, 1, 34, 95 });
	/*idleAnimPlayer.PushBack({ 170, 1, 34, 95 });*/
	/*idleAnimPlayer.PushBack({ 144, 1, 31, 95 });*/
	/*idleAnimPlayer.PushBack({ 104, 1, 41, 95 });*/
	idleAnimPlayer.PushBack({ 77, 1, 33, 95 });
	idleAnimPlayer.PushBack({ 41, 1, 34, 95 });
	idleAnimPlayer.PushBack({ 1, 1, 34, 95 });
	idleAnimPlayer.loop = true;
	idleAnimPlayer.speed = 0.1f;
}

CreditsScreen::~CreditsScreen()
{
}

bool CreditsScreen::Awake()
{
	LOG("CreditsScreen Scene");
	bool ret = true;

	return ret;

	return true;
}

bool CreditsScreen::Start()
{
	/*logoAnimationP1 = app->tex->Load("Assets/textures/Scenes/LogoAnimationFrames/logo_animation_p1.png");

	app->audio->ChangeMusic(LOGO_INTRO, 0, 0);

	delay = 0;
	animationPositionY = 0;
	logoPart = 1;*/

	bgTexture = app->tex->Load("Assets/textures/Scenes/Credits/scrollBackgroundCredits.png");

	texture = app->tex->Load("Assets/textures/Scenes/Credits/finalSoldier.png");
	playerAnimation = &idleAnimPlayer;
	texture1 = app->tex->Load("Assets/textures/Scenes/Credits/survivorCredits.png");
	currentAnimation = &idleAnim;
	currentAnimation1 = &idleAnim;

	texture2 = app->tex->Load("Assets/textures/Scenes/Credits/zombie1.png");
	currentAnimation2 = &idleAnim1;

	texture3 = app->tex->Load("Assets/textures/Scenes/Credits/zombie2.png");
	currentAnimation3 = &idleAnim2;

	texture4 = app->tex->Load("Assets/textures/Scenes/Credits/zombie3.png");
	currentAnimation4 = &idleAnim3;

	returnButton1 = app->tex->Load("Assets/textures/GUI/returnButton.png");
	returnButtonOnIdle1 = app->tex->Load("Assets/textures/GUI/returnButton_onIdle.png");
	returnButtonPressed1 = app->tex->Load("Assets/textures/GUI/returnButton_pressed.png");

	buttonClickedFx = app->audio->LoadFx("Assets/audio/fx/UISounds/buttonClickedFX.wav");

	returnButton_1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 25, "Return Button", { 10, 10, 71, 35 }, this, returnButton1, NULL, {});

	app->render->camera.x = 0;

	app->audio->ChangeMusic(CREDITS_THEME, 0, 0);

	fPosition.x = 80;
	fPosition.y = 155;

	fPosition1.x = -125;
	fPosition1.y = 196;
	fPosition2.x = -30;
	fPosition2.y = 196;

	fPosition3.x = -70;
	fPosition3.y = 203;
	fPosition7.x = -110;
	fPosition7.y = 203;

	fPosition4.x = -95;
	fPosition4.y = 200;
	fPosition8.x = -145;
	fPosition8.y = 200;

	fPosition5.x = -15;
	fPosition5.y = 203;
	fPosition9.x = -165;
	fPosition9.y = 203;

	fPosition6.x = -57;
	fPosition6.y = 203;

	/*app->render->camera.x = 0;
	app->render->camera.y = 0;*/

	return true;
}

bool CreditsScreen::PreUpdate()
{

	return true;
}

bool CreditsScreen::Update(float dt)
{
	/*delay++;

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
	}*/

	
	/*app->render->camera.x = (-(app->player->Player->body->GetPosition().x * 100) + 630);*/

	/*app->render->camera.x = (- (app->render->camera.x * 100) + 630);*/

	delay++;

	if ((delay % 2) == 0)
	{
		backwardsImage--;
	}

	if (creditsScene == true)
	{
		returnButton_1->canClick = true;
	}

	if (creditsScene == false)
	{
		returnButton_1->canClick = false;
	}

	app->creditsScreen->fPosition.x += 0.02;
	app->creditsScreen->fPosition1.x += 0.0187;
	app->creditsScreen->fPosition2.x += 0.0187;
	app->creditsScreen->fPosition3.x += 0.0187;
	app->creditsScreen->fPosition4.x += 0.0187;
	app->creditsScreen->fPosition5.x += 0.0187;
	app->creditsScreen->fPosition6.x += 0.0187;
	app->creditsScreen->fPosition7.x += 0.0187;
	app->creditsScreen->fPosition8.x += 0.0187;
	app->creditsScreen->fPosition9.x += 0.0187;

	playerAnimation->Update();
	currentAnimation->Update();
	currentAnimation1->Update();
	currentAnimation2->Update();
	currentAnimation3->Update();
	currentAnimation4->Update();

	return true;
}

bool CreditsScreen::PostUpdate()
{
	//bool ret = true;
	app->render->DrawTexture2(bgTexture, backwardsImage, 0);

	if (returnButton_1->state == GuiControlState::NORMAL && returnButton_1->canClick == true) returnButton_1->SetTexture(returnButton1);
	if (returnButton_1->state == GuiControlState::FOCUSED && returnButton_1->canClick == true) returnButton_1->SetTexture(returnButtonOnIdle1);
	if (returnButton_1->state == GuiControlState::SELECTED && returnButton_1->canClick == true) returnButton_1->SetTexture(returnButtonPressed1);
	returnButton_1->Draw(app->render);

	SDL_Rect rect = playerAnimation->GetCurrentFrame();
	app->render->DrawTexture2(texture, fPosition.x, fPosition.y, &rect);

	SDL_Rect rect0 = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture2(texture1, fPosition1.x, fPosition1.y, &rect0);

	SDL_Rect rect1 = currentAnimation1->GetCurrentFrame();
	app->render->DrawTexture2(texture1, fPosition2.x, fPosition2.y, &rect1);

	SDL_Rect rect2 = currentAnimation2->GetCurrentFrame();
	app->render->DrawTexture2(texture2, fPosition3.x, fPosition3.y, &rect2);
	app->render->DrawTexture2(texture2, fPosition7.x, fPosition7.y, &rect2);

	SDL_Rect rect3 = currentAnimation3->GetCurrentFrame();
	app->render->DrawTexture2(texture3, fPosition4.x, fPosition4.y, &rect3);
	app->render->DrawTexture2(texture3, fPosition8.x, fPosition8.y, &rect3);

	SDL_Rect rect4 = currentAnimation4->GetCurrentFrame();
	app->render->DrawTexture2(texture4, fPosition5.x, fPosition5.y, &rect4);
	app->render->DrawTexture2(texture4, fPosition6.x, fPosition6.y, &rect4);
	app->render->DrawTexture2(texture4, fPosition9.x, fPosition9.y, &rect4);


	//return ret;

	return true;
}

bool CreditsScreen::CleanUp()
{
	/*app->tex->UnLoad(logoAnimationP1);
	app->tex->UnLoad(logoAnimationP2);
	app->tex->UnLoad(logoAnimationP3);
	app->tex->UnLoad(logoAnimationP4);
	app->tex->UnLoad(logoAnimationP5);
	app->tex->UnLoad(logoAnimationP6);
	app->tex->UnLoad(logoAnimationP7);
	app->tex->UnLoad(logoAnimationP8);*/

	app->tex->UnLoad(texture);
	app->tex->UnLoad(texture1);
	app->tex->UnLoad(texture2);
	app->tex->UnLoad(texture3);
	app->tex->UnLoad(texture4);

	app->guiManager->DestroyGuiControl(25);

	return true;
}

bool CreditsScreen::OnGuiMouseClickEvent(GuiControl* control) {
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		//Checks the GUI element ID
		if (control->id == 25 && returnButton_1->canClick == true)
		{
			app->audio->PlayFx(buttonClickedFx, 0);

			creditsScene = false;

			app->titleScreen->Enable();
			app->creditsScreen->Disable();
		}
		
	default: break;
	}
	}

	return true;
}