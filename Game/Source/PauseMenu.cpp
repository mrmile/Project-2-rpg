#include "PauseMenu.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneMainMap.h"
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

PauseMenu::PauseMenu(bool start_enabled) : Module(start_enabled)
{
	name.Create("PauseMenu");
}

// Destructor
PauseMenu::~PauseMenu()
{}

// Called before render is available
bool PauseMenu::Awake()
{
	LOG("Loading PauseMenu");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool PauseMenu::Start()
{
	PauseFrame = app->tex->Load("Assets/textures/GUI/PauseScreenEffects.png");
	PauseTitle = app->tex->Load("Assets/textures/Scenes/mainTitleLettersPauseMenu.png");
	settingsLetters = app->tex->Load("Assets/textures/Scenes/settingsLetters.png");

	buttonClickedFx = app->audio->LoadFx("Assets/audio/fx/UISounds/buttonClickedFX.wav");
	resumeButton = app->tex->Load("Assets/textures/GUI/resumeButton.png");
	optionsButton = app->tex->Load("Assets/textures/GUI/optionsButton.png");
	backToTitleButton = app->tex->Load("Assets/textures/GUI/titlescreenButton.png");
	exitButton = app->tex->Load("Assets/textures/GUI/exitButton.png");

	resumeButtonOnIdle = app->tex->Load("Assets/textures/GUI/resumeButton_onIdle.png");
	optionsButtonOnIdle = app->tex->Load("Assets/textures/GUI/optionsButton_onIdle.png");
	backToTitleButtonOnIdle = app->tex->Load("Assets/textures/GUI/titlescreenButton_onIdle.png");
	exitButtonOnIdle = app->tex->Load("Assets/textures/GUI/exitButton_onIdle.png");

	resumeButtonPressed = app->tex->Load("Assets/textures/GUI/resumeButton_pressed.png");
	optionsButtonPressed = app->tex->Load("Assets/textures/GUI/optionsButton_pressed.png");
	backToTitleButtonPressed = app->tex->Load("Assets/textures/GUI/titlescreenButton_pressed.png");
	exitButtonPressed = app->tex->Load("Assets/textures/GUI/exitButton_pressed.png");


	fullScreenTag = app->tex->Load("Assets/textures/GUI/Fullscreen_tag.png");
	VSyncOff = app->tex->Load("Assets/textures/GUI/Vsync_tag.png");
	VSyncOn = app->tex->Load("Assets/textures/GUI/VsyncOn.png");
	fullScreenCheckOff = app->tex->Load("Assets/textures/GUI/checkBoxOff.png");
	fullScreenCheckOn = app->tex->Load("Assets/textures/GUI/checkBoxOn.png");
	baseSlider_fx = app->tex->Load("Assets/textures/GUI/BaseSlider_fx.png");
	baseSlider_music = app->tex->Load("Assets/textures/GUI/BaseSlider_music.png");
	sliderSelector = app->tex->Load("Assets/textures/GUI/sliderInput.png");
	returnButton = app->tex->Load("Assets/textures/GUI/returnButton.png");
	returnButtonOnIdle = app->tex->Load("Assets/textures/GUI/returnButton_onIdle.png");
	returnButtonPressed = app->tex->Load("Assets/textures/GUI/returnButton_pressed.png");

	resumeButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 12, "Resume Button", { 25,160,108,35 }, this, resumeButton, NULL, {});
	optionsButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 13, "Settings Button", { 25,190,108,35 }, this,optionsButton, NULL, {});
	backToTitleButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 14, "Title Button", { 25,220,108,35 }, this,backToTitleButton, NULL, {});
	exitButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 15, "Exit Button", { 25, 250, 108, 35 }, this,exitButton, NULL, {});
	returnButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 16, "Return Button", { 20, 10, 71, 35 }, this, returnButton, NULL, {});
	
	//SLIDERS
	fxVolumeSlider = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 17, "Fx slider", { 20,140,350,35 }, this, baseSlider_fx, sliderSelector, { 250,157,14,16 });
	musicVolumeSlider = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 18, "Music slider", { 20,190,350,35 }, this, baseSlider_music, sliderSelector, { 50,207,150,16 });

	//CHECKBOXES
	fullScreenCheck_ = (GuiCheckbox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 19, "Full Screen Check Box", { 300, 249, 35, 35 }, this, fullScreenCheckOff, NULL, {});
	fullScreenCheck_tag_ = (GuiCheckbox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 20, "Full Screen Tag", { 20, 240, 161, 9 }, this, fullScreenTag, NULL, {});

	VSyncCheck = (GuiCheckbox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 21, "Vsync", { 300,299,35,35 }, this, fullScreenCheckOff, NULL, {});
	VSyncCheck_tag_ = (GuiCheckbox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 22, "Vsync", { 20,290,213,35 }, this, VSyncOff, NULL, {});

	app->SaveGameAudio();
	pauseTimer = 0;
	noPauseTimer = 0;
	sceneTimer = 0;
	

	fxVolumeSlider->extraBounds.x = 33 + fxVolumeSlider->bounds.x * (app->audio->SliderLevelFX / 10);
	musicVolumeSlider->extraBounds.x = 33 + musicVolumeSlider->bounds.x * (app->audio->SliderLevelMusic / 10);

	return true;
}

// Called each loop iteration
bool PauseMenu::PreUpdate()
{
	
	return true;
}

// Called each loop iteration
bool PauseMenu::Update(float dt)
{
	sceneTimer++;
	
	if (app->player->pauseMenu == true)
	{
		pauseTimer++;
		noPauseTimer = 0;

		

		if (TitleTransition == true)
		{
			app->titleScreen->Enable();
			app->titleScreen->MainMenu = true;
			app->player->pauseMenu = false;
			app->map->Disable();
			app->collisions->Disable();
			app->particles->Disable();
			app->sceneMainMap->Disable();
			app->player->Disable();
			app->entity_manager->Disable();
			app->fonts->Disable();
			app->pause_menu->Disable();
			TitleTransition = false;
		}
		
		if(pauseTimer <= 1) app->audio->ChangeMusic(PAUSE_MENU, 0.5f, 0.5f);
		if (options == false)
		{
			resumeButton_->canClick = true;
			optionsButton_->canClick = true;
			backToTitleButton_->canClick = true;
			exitButton_->canClick = true;
			returnButton_->canClick = false;
			fxVolumeSlider->canClick = false;
			musicVolumeSlider->canClick = false;
			fullScreenCheck_->canClick = false;
			fullScreenCheck_tag_->canClick = false;
			VSyncCheck->canClick = false;
			VSyncCheck_tag_->canClick = false;
		}
		if (options == true)
		{
			resumeButton_->canClick = false;
			optionsButton_->canClick = false;
			backToTitleButton_->canClick = false;
			exitButton_->canClick = false;
			fxVolumeSlider->canClick = true;
			musicVolumeSlider->canClick = true;
			fullScreenCheck_->canClick = true;
			fullScreenCheck_tag_->canClick = false;
			VSyncCheck->canClick = true;
			returnButton_->canClick = true;
			VSyncCheck_tag_->canClick = false;
		}
	}
	else
	{
		pauseTimer = 0;
		noPauseTimer++;

		if (noPauseTimer <= 1) app->audio->ChangeMusic(MAIN_MAP, 0.5f, 0.5f);
	}
	if (app->player->pauseMenu == false)
	{

		resumeButton_->canClick = false;
		optionsButton_->canClick = false;
		backToTitleButton_->canClick = false;
		exitButton_->canClick = false;
		returnButton_->canClick = false;
		fxVolumeSlider->canClick = false;
		musicVolumeSlider->canClick = false;
		fullScreenCheck_->canClick = false;
		fullScreenCheck_tag_->canClick = false;
		VSyncCheck->canClick = false;
		VSyncCheck_tag_->canClick = false;
	}
	

	return true;
}

// Called each loop iteration
bool PauseMenu::PostUpdate()
{
	bool ret = true;
	
	if (app->player->pauseMenu == true)
	{

		SDL_Rect bgquad;
		bgquad = { 20, 20, 380, 200 };
		/*app->render->DrawRectangle2(bgquad, 255, 255, 255, 150, 0.0f, true);*/
		app->render->DrawTexture2(PauseFrame, 0, 0, NULL);

		if (options == false)
		{
			app->render->DrawTexture2(PauseTitle, -105, 60, NULL);

			if (exitButton_->state == GuiControlState::NORMAL && exitButton_->canClick == true) exitButton_->SetTexture(exitButton);
			if (exitButton_->state == GuiControlState::FOCUSED && exitButton_->canClick == true) exitButton_->SetTexture(exitButtonOnIdle);
			if (exitButton_->state == GuiControlState::SELECTED && exitButton_->canClick == true) exitButton_->SetTexture(exitButtonPressed);
			exitButton_->Draw(app->render);

			if (resumeButton_->state == GuiControlState::NORMAL && resumeButton_->canClick == true) resumeButton_->SetTexture(resumeButton);
			if (resumeButton_->state == GuiControlState::FOCUSED && resumeButton_->canClick == true) resumeButton_->SetTexture(resumeButtonOnIdle);
			if (resumeButton_->state == GuiControlState::SELECTED && resumeButton_->canClick == true) resumeButton_->SetTexture(resumeButtonPressed);
			resumeButton_->Draw(app->render);

			if (optionsButton_->state == GuiControlState::NORMAL && optionsButton_->canClick == true) optionsButton_->SetTexture(optionsButton);
			if (optionsButton_->state == GuiControlState::FOCUSED && optionsButton_->canClick == true) optionsButton_->SetTexture(optionsButtonOnIdle);
			if (optionsButton_->state == GuiControlState::SELECTED && optionsButton_->canClick == true) optionsButton_->SetTexture(optionsButtonPressed);
			optionsButton_->Draw(app->render);

			if (backToTitleButton_->state == GuiControlState::NORMAL && backToTitleButton_->canClick == true) backToTitleButton_->SetTexture(backToTitleButton);
			if (backToTitleButton_->state == GuiControlState::FOCUSED && backToTitleButton_->canClick == true) backToTitleButton_->SetTexture(backToTitleButtonOnIdle);
			if (backToTitleButton_->state == GuiControlState::SELECTED && backToTitleButton_->canClick == true) backToTitleButton_->SetTexture(backToTitleButtonPressed);
			backToTitleButton_->Draw(app->render);
		}
		else if (options == true)
		{
			app->render->DrawTexture2(settingsLetters, -130, 30, NULL);

			if (returnButton_->state == GuiControlState::NORMAL && returnButton_->canClick == true) returnButton_->SetTexture(returnButton);
			if (returnButton_->state == GuiControlState::FOCUSED && returnButton_->canClick == true) returnButton_->SetTexture(returnButtonOnIdle);
			if (returnButton_->state == GuiControlState::SELECTED && returnButton_->canClick == true) returnButton_->SetTexture(returnButtonPressed);
			returnButton_->Draw(app->render);

			fxVolumeSlider->Draw(app->render);



			musicVolumeSlider->Draw(app->render);


			fullScreenCheck_tag_->SetTexture(fullScreenTag);
			fullScreenCheck_tag_->Draw(app->render);

			if (app->titleScreen->FullScreen == false) fullScreenCheck_->SetTexture(fullScreenCheckOff);
			if (app->titleScreen->FullScreen == true) fullScreenCheck_->SetTexture(fullScreenCheckOn);
			fullScreenCheck_->Draw(app->render);

			VSyncCheck_tag_->SetTexture(VSyncOff);
			VSyncCheck_tag_->Draw(app->render);

			if (app->titleScreen->Vsync == false) VSyncCheck->SetTexture(fullScreenCheckOff);
			if (app->titleScreen->Vsync == true) VSyncCheck->SetTexture(fullScreenCheckOn);
			VSyncCheck->Draw(app->render);
		}
	}
	


	//return ret;

	return true;
}

// Called before quitting
bool PauseMenu::CleanUp()
{
	app->tex->UnLoad(PauseFrame);
	app->tex->UnLoad(PauseTitle);
	app->tex->UnLoad(settingsLetters);

	app->tex->UnLoad(exitButton);
	app->tex->UnLoad(resumeButton);
	app->tex->UnLoad(optionsButton);
	app->tex->UnLoad(backToTitleButton);
	app->tex->UnLoad(exitButton);

	app->tex->UnLoad(exitButtonOnIdle);
	app->tex->UnLoad(optionsButtonOnIdle);
	app->tex->UnLoad(backToTitleButtonOnIdle);
	app->tex->UnLoad(exitButtonOnIdle);

	app->tex->UnLoad(exitButtonPressed);
	app->tex->UnLoad(resumeButtonPressed);
	app->tex->UnLoad(optionsButtonPressed);
	app->tex->UnLoad(backToTitleButtonPressed);
	app->tex->UnLoad(exitButtonPressed);
	app->guiManager->DestroyGuiControl(12);
	app->guiManager->DestroyGuiControl(13);
	app->guiManager->DestroyGuiControl(14);
	app->guiManager->DestroyGuiControl(15);
	app->guiManager->DestroyGuiControl(16);
	app->guiManager->DestroyGuiControl(17);
	app->guiManager->DestroyGuiControl(18);
	app->guiManager->DestroyGuiControl(19);
	app->guiManager->DestroyGuiControl(20);
	app->guiManager->DestroyGuiControl(21);
	return true;
}

bool PauseMenu::OnGuiMouseClickEvent(GuiControl* control){
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		//Checks the GUI element ID
		if (control->id == 12 && resumeButton_->canClick==true)
		{
			//RESUME BUTTON
			app->audio->PlayFx(buttonClickedFx, 0);
			app->player->pauseMenu = false;
		}

		if (control->id == 13 && optionsButton_->canClick == true)
		{
			//SETTINGS BUTTON
			app->audio->PlayFx(buttonClickedFx, 0);
			options = true;
			

		}
		if (control->id == 14 && backToTitleButton_->canClick == true)
		{
			//BACK TO TITLE BUTTON
			app->audio->PlayFx(buttonClickedFx, 0);
			TitleTransition = true;
		}

		if (control->id == 15 && exitButton_->canClick == true)
		{
			//EXIT BUTTON
			app->audio->PlayFx(buttonClickedFx, 0);
			exit(0);

		}
		if (control->id == 16 && returnButton_->canClick == true)
		{
			app->audio->PlayFx(buttonClickedFx, 0);
			options = false;
		}
	}
	case GuiControlType::SLIDER:
	{
		if (control->id == 17 && fxVolumeSlider->canClick == true)
		{
			if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.9f) + 160 && control->extraBounds.x < control->bounds.x + control->bounds.w + 160)
			{
				app->audio->SliderLevelFX = 90;
			}
			if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.8f) + 160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.9f) + 160)
			{
				app->audio->SliderLevelFX = 80;
			}
			if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.7f) + 160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.8f) + 160)
			{
				app->audio->SliderLevelFX = 70;
			}
			if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.6f) + 160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.7f) + 160)
			{
				app->audio->SliderLevelFX = 60;
			}
			if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.5f) + 160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.6f) + 160)
			{
				app->audio->SliderLevelFX = 50;
			}
			if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.4f) + 160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.5f) + 160)
			{
				app->audio->SliderLevelFX = 40;
			}
			if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.3f) + 160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.4f) + 160)
			{
				app->audio->SliderLevelFX = 30;
			}
			if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.2f) + 160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.3f) + 160)
			{
				app->audio->SliderLevelFX = 20;
			}
			if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.1f) + 160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.2f) + 160)
			{
				app->audio->SliderLevelFX = 10;
			}
			if (control->extraBounds.x > control->bounds.x + 160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.1f) + 160)
			{
				app->audio->SliderLevelFX = 0;
			}
		}
		if (control->id == 18 && musicVolumeSlider->canClick == true)
		{
			if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.9f) + 160 && control->extraBounds.x < control->bounds.x + control->bounds.w + 160)
			{
				app->audio->SliderLevelMusic = 90;
			}
			if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.8f) + 160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.9f) + 160)
			{
				app->audio->SliderLevelMusic = 80;
			}
			if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.7f) + 160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.8f) + 160)
			{
				app->audio->SliderLevelMusic = 70;
			}
			if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.6f) + 160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.7f) + 160)
			{
				app->audio->SliderLevelMusic = 60;
			}
			if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.5f) + 160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.6f) + 160)
			{
				app->audio->SliderLevelMusic = 50;
			}
			if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.4f) + 160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.5f) + 160)
			{
				app->audio->SliderLevelMusic = 40;
			}
			if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.3f) + 160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.4f) + 160)
			{
				app->audio->SliderLevelMusic = 30;
			}
			if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.2f) + 160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.3f) + 160)
			{
				app->audio->SliderLevelMusic = 20;
			}
			if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.1f) + 160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.2f) + 160)
			{
				app->audio->SliderLevelMusic = 10;
			}
			if (control->extraBounds.x > control->bounds.x + 160 && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.1f) + 160)
			{
				app->audio->SliderLevelMusic = 0;
			}
		}
	}
	case GuiControlType::CHECKBOX:
	{
		if (control->id == 19 && fullScreenCheck_->canClick == true)
		{
			app->titleScreen->FullScreen = !app->titleScreen->FullScreen;
		}
		if (control->id == 20 && fullScreenCheck_tag_->canClick == true)
		{
			//Do nothing
		}
		if (control->id == 21 && VSyncCheck->canClick == true)
		{
			app->titleScreen->Vsync = !app->titleScreen->Vsync;
		}
		if (control->id == 22 && VSyncCheck_tag_->canClick == true)
		{
			//Do nothing
		}
	}
	default: break;
	}

	return true;
}
bool PauseMenu::CheckAudioSave(pugi::xml_node& data)
{
	app->audio->SliderLevelFX = data.child("saved_game").attribute("Fx").as_int();
	app->audio->SliderLevelMusic = data.child("saved_game").attribute("Music").as_int();

	return true;
}