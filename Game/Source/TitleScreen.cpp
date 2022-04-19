#include "TitleScreen.h"
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
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleFonts.h"
#include "GuiManager.h"
#include "GuiButton.h"
#include "PauseMenu.h"
#include "EntityManager.h"
#include "Entity.h"

#include "Defs.h"
#include "Log.h"

#include <SDL_mixer/include/SDL_mixer.h>
#include <iostream>
using namespace std;

TitleScreen::TitleScreen(bool start_enabled) : Module(start_enabled)
{
	name.Create("TitleScreen");
}

TitleScreen::~TitleScreen()
{
}

bool TitleScreen::Awake()
{
	LOG("TitleScreen Scene");
	bool ret = true;

	return ret;

	return true;
}

bool TitleScreen::Start()
{
	titleScreen = app->tex->Load("Assets/textures/Scenes/mainTitleBackground.png");
	titleScreenLetters = app->tex->Load("Assets/textures/Scenes/mainTitleLetters.png");
	settingsLetters = app->tex->Load("Assets/textures/Scenes/settingsLetters.png");

	titleScreen2 = app->tex->Load("Assets/textures/island.png");
	loading = app->tex->Load("Assets/textures/loadingScreen.png");
	creditsScene = app->tex->Load("Assets/textures/creditsScreen3.png");

	baseSlider_fx = app->tex->Load("Assets/textures/GUI/BaseSlider_fx.png");
	baseSlider_music = app->tex->Load("Assets/textures/GUI/BaseSlider_music.png");
	fullScreenTag = app->tex->Load("Assets/textures/GUI/Fullscreen_tag.png");
	VSyncOff = app->tex->Load("Assets/textures/GUI/Vsync_tag.png");
	VSyncOn = app->tex->Load("Assets/textures/GUI/VsyncOn.png");

	newGameButton = app->tex->Load("Assets/textures/GUI/startButton.png");
	continueButton = app->tex->Load("Assets/textures/GUI/continueButton.png");
	continueButtonOff = app->tex->Load("Assets/textures/GUI/continueButtonOff.png");
	optionsButton = app->tex->Load("Assets/textures/GUI/optionsButton.png");
	creditsButton = app->tex->Load("Assets/textures/GUI/creditsButton.png");
	exitButton = app->tex->Load("Assets/textures/GUI/exitButton.png");
	returnButton = app->tex->Load("Assets/textures/GUI/returnButton.png");
	sliderSelector = app->tex->Load("Assets/textures/GUI/sliderInput.png");
	fullScreenCheckOff = app->tex->Load("Assets/textures/GUI/checkBoxOff.png");
	fullScreenCheckOn = app->tex->Load("Assets/textures/GUI/checkBoxOn.png");

	newGameButtonOnIdle = app->tex->Load("Assets/textures/GUI/startButton_onIdle.png");
	continueButtonOnIdle = app->tex->Load("Assets/textures/GUI/continueButton_onIdle.png");
	continueButtonOffOnIdle = app->tex->Load("Assets/textures/GUI/continueButtonOff_onIdle.png");
	optionsButtonOnIdle = app->tex->Load("Assets/textures/GUI/optionsButton_onIdle.png");
	creditsButtonOnIdle = app->tex->Load("Assets/textures/GUI/creditsButton_onIdle.png");
	exitButtonOnIdle = app->tex->Load("Assets/textures/GUI/exitButton_onIdle.png");
	returnButtonOnIdle = app->tex->Load("Assets/textures/GUI/returnButton_onIdle.png");
	sliderSelectorOnIdle = app->tex->Load("Assets/textures/GUI/sliderInput_onIdle.png");

	newGameButtonPressed = app->tex->Load("Assets/textures/GUI/startButton_pressed.png");
	continueButtonPressed = app->tex->Load("Assets/textures/GUI/continueButton_pressed.png");
	continueButtonOffPressed = app->tex->Load("Assets/textures/GUI/continueButtonOff_pressed.png");
	optionsButtonPressed = app->tex->Load("Assets/textures/GUI/optionsButton_pressed.png");
	creditsButtonPressed = app->tex->Load("Assets/textures/GUI/creditsButton_pressed.png");
	exitButtonPressed = app->tex->Load("Assets/textures/GUI/exitButton_pressed.png");
	returnButtonPressed = app->tex->Load("Assets/textures/GUI/returnButton_pressed.png");
	sliderSelectorPressed = app->tex->Load("Assets/textures/GUI/sliderInput_pressed.png");

	// Load music
	app->audio->ChangeMusic(TITLE_THEME, 2, 2);
	buttonClickedFx = app->audio->LoadFx("Assets/audio/fx/UISounds/buttonClickedFX.wav");
	buttonNotClickedFx = app->audio->LoadFx("Assets/audio/fx/No.wav");

	// L14: TODO 2_D: Declare a GUI Button and create it using the GuiManager
	//BUTTONS
	newGameButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Start Button", { 10, 170, 108, 35 }, this, newGameButton,NULL, {}); //Observer (this): Class that will receive the event
	continueButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Continue Button", { 10, 200, 108, 35 }, this,continueButton, NULL, {});
	optionsButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Options Button", { 10, 240, 108, 35 }, this,optionsButton, NULL, {});
	creditsButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "Credits Button", { 10, 270, 108, 35 }, this,creditsButton, NULL, {});
	exitButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "Exit Button", { 10, 310, 108, 35 }, this,exitButton, NULL, {});
	returnButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "Return Button", { 10, 10, 71, 35 }, this, returnButton, NULL, {});

	//SLIDERS
	fxVolumeSlider = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 7, "Fx slider", { 20,140,350,35 }, this, baseSlider_fx, sliderSelector, { 250,157,14,16});
	musicVolumeSlider = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 8, "Music slider", { 20,190,350,35 }, this, baseSlider_music, sliderSelector, { 50,207,150,16 });

	//CHECKBOXES
	fullScreenCheck_ = (GuiCheckbox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 9, "Full Screen Check Box", { 300, 249, 35, 35 }, this, fullScreenCheckOff, NULL, {});
	fullScreenCheck_tag_ = (GuiCheckbox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 10, "Full Screen Tag", { 20, 240, 161, 9 }, this, fullScreenTag, NULL, {});

	VSyncCheck = (GuiCheckbox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 11, "Vsync", { 300,299,35,35 }, this, fullScreenCheckOff, NULL, {});
	VSyncCheck_tag_ = (GuiCheckbox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 23, "Vsync", { 20,290,213,35 }, this, VSyncOff, NULL, {});

	app->CheckGameRequest();
	app->SaveGameAudio();

	sceneTimer = 0;
	delay = 0;
	delayToContinue = 0;
	delayToCredits = 0;
	transition = false;
	continueTransition = false;
	GameHasContinued = false;
	credits = false;

	app->render->camera.x = 0;
	app->render->camera.y = 0;

	fxVolumeSlider->extraBounds.x = 33 + fxVolumeSlider->bounds.x * (app->audio->SliderLevelFX / 10);
	musicVolumeSlider->extraBounds.x = 33 + musicVolumeSlider->bounds.x * (app->audio->SliderLevelMusic / 10);

	return true;
}

bool TitleScreen::PreUpdate()
{
	

	return true;
}

bool TitleScreen::Update(float dt)
{
	sceneTimer++;

	//cout << "Fx: " << app->audio->SliderLevelFX << endl;
	//cout << "Music: " << app->audio->SliderLevelMusic << endl;

	if (app->input->keys[SDL_SCANCODE_F1] == KEY_DOWN)
	{
		transition = true;
	}
	if (MainMenu == true)
	{
		newGameButton_->canClick = true;
		continueButton_->canClick = true;
		optionsButton_->canClick = true;
		creditsButton_->canClick = true;
		exitButton_->canClick = true;
		returnButton_->canClick = false;
		fxVolumeSlider->canClick = false;
		musicVolumeSlider->canClick = false;
		fullScreenCheck_->canClick = false;
		fullScreenCheck_tag_->canClick = false;
		VSyncCheck->canClick = false;
		VSyncCheck_tag_->canClick = false;
	}
	if (OptionsMenu == true)
	{
		newGameButton_->canClick = false;
		continueButton_->canClick = false;
		optionsButton_->canClick = false;
		creditsButton_->canClick = false;
		exitButton_->canClick = false;
		returnButton_->canClick = true;
		fxVolumeSlider->canClick = true;
		musicVolumeSlider->canClick = true;
		fullScreenCheck_->canClick = true;
		fullScreenCheck_tag_->canClick = false;
		VSyncCheck->canClick = true;
		VSyncCheck_tag_->canClick = false;
	}
	if (credits == true)
	{
		newGameButton_->canClick = false;
		continueButton_->canClick = false;
		optionsButton_->canClick = false;
		creditsButton_->canClick = false;
		exitButton_->canClick = false;
		returnButton_->canClick = true;
		fxVolumeSlider->canClick = false;
		musicVolumeSlider->canClick = false;
		fullScreenCheck_->canClick = false;
		fullScreenCheck_tag_->canClick = false;
		VSyncCheck->canClick = false;
		VSyncCheck_tag_->canClick = false;
	}


	if (MainMenu == true)
	{
		//FOR CONTINUE BUTTON
		if (continueTransition == true) delayToContinue++;

		if (delayToContinue > 90 && delayToContinue <= 91)
		{
			//app->physics->Enable();
			//app->collisions->Enable();
			//app->map->Enable();
			//app->map->Start();
			//app->particles->Enable();
			//app->sceneMainMap->Enable();
			//app->player->Enable();
			//app->enemies->Enable();
			//app->fonts->Enable();
			//app->collisions->Enable();
			//app->map->Enable();
			//app->particles->Enable();
			//app->sceneMainMap->Enable();
			//app->player->Enable();
			//app->enemies->Enable();
			//app->fonts->Enable();
			//app->tex->Enable();
			//app->pause_menu->Enable();

			//app->physics->Enable();
			app->collisions->Enable();
			app->map->Enable();
			app->particles->Enable();
			app->sceneMainMap->Enable();
			app->player->Enable();
			app->entity_manager->Enable();
			app->fonts->Enable();
			app->tex->Enable();
			app->pause_menu->Enable();
		
			GameHasContinued = true;

			app->titleScreen->Disable();
			//app->fade->FadeToBlack(app->titleScreen, app->sceneCave, 60);
		}

		//FOR START BUTTON
		if (transition == true) delay++;

		if (delay > 90 && delay <= 91)
		{
			//app->physics->Enable();
			app->collisions->Enable();
			app->map->Enable();
			app->particles->Enable();
			app->sceneMainMap->Enable();
			app->player->Enable();
			app->entity_manager->Enable();
			app->fonts->Enable();
			app->tex->Enable();
			app->pause_menu->Enable();
			app->player->score = 0;
			app->player->lives = 3;
			SavedGame = false;
			app->player->entranceID = 0;
			

			app->titleScreen->Disable();
			//app->fade->FadeToBlack(app->titleScreen, app->sceneCave, 60);
		}
	}

	
	
	return true;
}

bool TitleScreen::PostUpdate()
{
	bool ret = true;

	

	app->render->DrawTexture2(titleScreen, 0, 0, NULL);
	
	if (MainMenu == true) 
	{
		app->render->DrawTexture2(titleScreenLetters, -120, 60, NULL);

		if (newGameButton_->state == GuiControlState::NORMAL && newGameButton_->canClick == true) newGameButton_->SetTexture(newGameButton);
		if (newGameButton_->state == GuiControlState::FOCUSED && newGameButton_->canClick == true) newGameButton_->SetTexture(newGameButtonOnIdle);
		if (newGameButton_->state == GuiControlState::SELECTED && newGameButton_->canClick == true) newGameButton_->SetTexture(newGameButtonPressed);
		newGameButton_->Draw(app->render);

		if (SavedGame == true)
		{
			if (continueButton_->state == GuiControlState::NORMAL && continueButton_->canClick == true) continueButton_->SetTexture(continueButton);
			if (continueButton_->state == GuiControlState::FOCUSED && continueButton_->canClick == true) continueButton_->SetTexture(continueButtonOnIdle);
			if (continueButton_->state == GuiControlState::SELECTED && continueButton_->canClick == true) continueButton_->SetTexture(continueButtonPressed);
			continueButton_->Draw(app->render);
		}
		if (SavedGame == false)
		{
			continueButton_->SetTexture(continueButtonOff);
			continueButton_->Draw(app->render);
		}

		if (optionsButton_->state == GuiControlState::NORMAL && optionsButton_->canClick == true) optionsButton_->SetTexture(optionsButton);
		if (optionsButton_->state == GuiControlState::FOCUSED && optionsButton_->canClick == true) optionsButton_->SetTexture(optionsButtonOnIdle);
		if (optionsButton_->state == GuiControlState::SELECTED && optionsButton_->canClick == true) optionsButton_->SetTexture(optionsButtonPressed);
		optionsButton_->Draw(app->render);

		if (creditsButton_->state == GuiControlState::NORMAL && creditsButton_->canClick == true) creditsButton_->SetTexture(creditsButton);
		if (creditsButton_->state == GuiControlState::FOCUSED && creditsButton_->canClick == true) creditsButton_->SetTexture(creditsButtonOnIdle);
		if (creditsButton_->state == GuiControlState::SELECTED && creditsButton_->canClick == true) creditsButton_->SetTexture(creditsButtonPressed);
		creditsButton_->Draw(app->render);

		if (exitButton_->state == GuiControlState::NORMAL && exitButton_->canClick == true) exitButton_->SetTexture(exitButton);
		if (exitButton_->state == GuiControlState::FOCUSED && exitButton_->canClick == true) exitButton_->SetTexture(exitButtonOnIdle);
		if (exitButton_->state == GuiControlState::SELECTED && exitButton_->canClick == true) exitButton_->SetTexture(exitButtonPressed);
		exitButton_->Draw(app->render);
	}
	if (OptionsMenu == true)
	{
		/*app->render->DrawTexture2(titleScreen2, 0, 0, NULL);*/
		app->render->DrawTexture2(settingsLetters, -130, 30, NULL);

		if (returnButton_->state == GuiControlState::NORMAL && returnButton_->canClick == true) returnButton_->SetTexture(returnButton);
		if (returnButton_->state == GuiControlState::FOCUSED && returnButton_->canClick == true) returnButton_->SetTexture(returnButtonOnIdle);
		if (returnButton_->state == GuiControlState::SELECTED && returnButton_->canClick == true) returnButton_->SetTexture(returnButtonPressed);
		returnButton_->Draw(app->render);

		fxVolumeSlider->Draw(app->render);



		musicVolumeSlider->Draw(app->render);


		fullScreenCheck_tag_->SetTexture(fullScreenTag);
		fullScreenCheck_tag_->Draw(app->render);

		if(FullScreen == false) fullScreenCheck_->SetTexture(fullScreenCheckOff);
		if(FullScreen == true) fullScreenCheck_->SetTexture(fullScreenCheckOn);
		fullScreenCheck_->Draw(app->render);

		VSyncCheck_tag_->SetTexture(VSyncOff);
		VSyncCheck_tag_->Draw(app->render);

		if (Vsync == false) VSyncCheck->SetTexture(fullScreenCheckOff);
		if (Vsync == true) VSyncCheck->SetTexture(fullScreenCheckOn);
		VSyncCheck->Draw(app->render);

	}
	if (credits == true)
	{
		app->render->DrawTexture2(titleScreen2, 0, 0, NULL);
		app->render->DrawTexture2(creditsScene, 0, 0, NULL);

		if (returnButton_->state == GuiControlState::NORMAL && returnButton_->canClick == true) returnButton_->SetTexture(returnButton);
		if (returnButton_->state == GuiControlState::FOCUSED && returnButton_->canClick == true) returnButton_->SetTexture(returnButtonOnIdle);
		if (returnButton_->state == GuiControlState::SELECTED && returnButton_->canClick == true) returnButton_->SetTexture(returnButtonPressed);
		returnButton_->Draw(app->render);
	}

	if (transition == true || continueTransition == true) app->render->DrawTexture2(loading, 0, 0, NULL);

	return ret;
	
	//return true;
}

bool TitleScreen::CleanUp()
{
	app->tex->UnLoad(titleScreen);
	app->tex->UnLoad(newGameButton);
	app->tex->UnLoad(titleScreenLetters);
	app->tex->UnLoad(settingsLetters);
	app->tex->UnLoad(creditsScene);
	app->tex->UnLoad(titleScreen2);
	app->tex->UnLoad(loading);
	app->tex->UnLoad(fullScreenTag);

	app->tex->UnLoad(continueButton);
	app->tex->UnLoad(continueButtonOff);
	app->tex->UnLoad(optionsButton);
	app->tex->UnLoad(creditsButton);
	app->tex->UnLoad(exitButton);
	app->tex->UnLoad(returnButton);
	app->tex->UnLoad(sliderSelector);
	app->tex->UnLoad(baseSlider_fx);
	app->tex->UnLoad(baseSlider_music);

	app->tex->UnLoad(continueButtonOnIdle);
	app->tex->UnLoad(continueButtonOffOnIdle);
	app->tex->UnLoad(optionsButtonOnIdle);
	app->tex->UnLoad(creditsButtonOnIdle);
	app->tex->UnLoad(exitButtonOnIdle);
	app->tex->UnLoad(returnButtonOnIdle);
	app->tex->UnLoad(sliderSelectorOnIdle);

	app->tex->UnLoad(continueButtonPressed);
	app->tex->UnLoad(continueButtonOffPressed);
	app->tex->UnLoad(optionsButtonPressed);
	app->tex->UnLoad(creditsButtonPressed);
	app->tex->UnLoad(exitButtonPressed);
	app->tex->UnLoad(returnButtonPressed);
	app->tex->UnLoad(sliderSelectorPressed);
	app->tex->UnLoad(fullScreenTag);
	app->tex->UnLoad(fullScreenCheckOff);
	app->tex->UnLoad(fullScreenCheckOn);
	app->tex->UnLoad(VSyncOff);
	app->tex->UnLoad(VSyncOn);
	app->guiManager->DestroyGuiControl(1);
	app->guiManager->DestroyGuiControl(2);
	app->guiManager->DestroyGuiControl(3);
	app->guiManager->DestroyGuiControl(4);
	app->guiManager->DestroyGuiControl(5);
	app->guiManager->DestroyGuiControl(6);
	app->guiManager->DestroyGuiControl(7);
	app->guiManager->DestroyGuiControl(8);
	app->guiManager->DestroyGuiControl(9);
	app->guiManager->DestroyGuiControl(10);
	app->guiManager->DestroyGuiControl(11);
	return true;
}

bool TitleScreen::OnGuiMouseClickEvent(GuiControl* control)
{

	switch (control->type)
	{
		case GuiControlType::BUTTON:
		{
			//Checks the GUI element ID
			if (control->id == 1 && newGameButton_->canClick == true)
			{
				app->audio->PlayFx(buttonClickedFx, 0);
				transition = true;

			}

			if (control->id == 2 && continueButton_->canClick == true)
			{

				if (SavedGame == true)
				{
					app->audio->PlayFx(buttonClickedFx, 0);
					app->audio->PlayFx(buttonClickedFx, 0);
					continueTransition = true;
				}
				if (SavedGame == false)
				{
					app->audio->PlayFx(buttonNotClickedFx, 0);
				}
			}
			if (control->id == 3 && optionsButton_->canClick == true)
			{
				app->audio->PlayFx(buttonClickedFx, 0);
				
				MainMenu = false;
				OptionsMenu = true;
			}

			if (control->id == 4 && creditsButton_->canClick == true)
			{
				app->audio->PlayFx(buttonClickedFx, 0);

				MainMenu = false;
				credits = true;
			}
			if (control->id == 5 && exitButton_->canClick == true)
			{
				app->audio->PlayFx(buttonClickedFx, 0);
				exit(0);
			}
			if (control->id == 6 && returnButton_->canClick == true)
			{
				app->audio->PlayFx(buttonClickedFx, 0);
				app->SaveGameAudio();
				OptionsMenu = false; 
				credits = false;
				MainMenu = true;
			}


		}
		//Other cases here
		case GuiControlType::SLIDER:
		{
			if (control->id == 7 && fxVolumeSlider->canClick == true)
			{
				
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.9f) + 160 && control->extraBounds.x < control->bounds.x + control->bounds.w + 160)
				{
					app->audio->SliderLevelFX = 90;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.8f) + 160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.9f)+160)
				{
					app->audio->SliderLevelFX = 80;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.7f) + 160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.8f)+160)
				{
					app->audio->SliderLevelFX = 70;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.6f) + 160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.7f)+160)
				{
					app->audio->SliderLevelFX = 60;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.5f) +160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.6f)+160)
				{
					app->audio->SliderLevelFX = 50;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.4f)+160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.5f)+160)
				{
					app->audio->SliderLevelFX = 40;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.3f)+160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.4f)+160)
				{
					app->audio->SliderLevelFX = 30;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.2f)+160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.3f)+160)
				{
					app->audio->SliderLevelFX = 20;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.1f)+160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.2f)+160)
				{
					app->audio->SliderLevelFX = 10;
				}
				if (control->extraBounds.x > control->bounds.x +160&& control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.1f)+160)
				{
					app->audio->SliderLevelFX = 0;
				}

			}

			if (control->id == 8 && musicVolumeSlider->canClick == true)
			{
				
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.9f)+160 && control->extraBounds.x < control->bounds.x + control->bounds.w +160)
				{
					app->audio->SliderLevelMusic = 90;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.8f)+160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.9f) + 160)
				{
					app->audio->SliderLevelMusic = 80;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.7f)+160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.8f)+160)
				{
					app->audio->SliderLevelMusic = 70;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.6f)+160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.7f)+160)
				{
					app->audio->SliderLevelMusic = 60;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.5f)+160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.6f)+160)
				{
					app->audio->SliderLevelMusic = 50;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.4f)+160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.5f)+160)
				{
					app->audio->SliderLevelMusic = 40;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.3f)+160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.4f)+160)
				{
					app->audio->SliderLevelMusic = 30;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.2f)+160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.3f)+160)
				{
					app->audio->SliderLevelMusic = 20;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.1f)+160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.2f)+160)
				{
					app->audio->SliderLevelMusic = 10;
				}
				if (control->extraBounds.x > control->bounds.x +160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.1f)+160)
				{
					app->audio->SliderLevelMusic = 0;
				}
			}

		}
		case GuiControlType::CHECKBOX:
		{
			if (control->id == 9 && fullScreenCheck_->canClick == true)
			{
				FullScreen = !FullScreen;
				cout << "control->id 9 registered" << endl;
			}
			if (control->id == 10 && fullScreenCheck_tag_->canClick == true)
			{
				// Do nothing it is just decoration
			}
			if (control->id == 11 && VSyncCheck->canClick == true)
			{
				Vsync = !Vsync;
			}
		}
		if (control->id == 11 && VSyncCheck_tag_->canClick == true)
		{
			// Do nothing it is just decoration
		}
		default: break;
	}
	
	return true;
}
bool TitleScreen::CheckSave(pugi::xml_node& data) 
{
	SavedGame = data.child("saved_game").attribute("bool").as_bool();
	return true;
}

bool TitleScreen::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node savedGame = data.append_child("saved_game");
	
	savedGame.append_attribute("bool") = SavedGame;
	savedGame.append_attribute("Fx") = app->audio->SliderLevelFX;
	savedGame.append_attribute("Music") = app->audio->SliderLevelMusic;
	savedGame.append_attribute("FullScreen") = FullScreen;
	

	return true;
}
bool TitleScreen::CheckAudioSave(pugi::xml_node& data) 
{
	app->audio->SliderLevelFX = data.child("saved_game").attribute("Fx").as_int();
	app->audio->SliderLevelMusic = data.child("saved_game").attribute("Music").as_int();
	
	return true;
}