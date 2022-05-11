#ifndef __PAUSE_MENU_H__
#define __PAUSE_MENU_H__

#include "Module.h"
#include "GuiButton.h"
#include "GuiCheckbox.h"
#include "GuiSlider.h"

struct SDL_Texture;

class PauseMenu : public Module
{
public:

	PauseMenu(bool start_enabled = false);

	// Destructor
	virtual ~PauseMenu();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control);

	bool CheckAudioSave(pugi::xml_node&);

	int buttonClickedFx = 0;
	int sceneTimer;
	int pauseTimer;
	int noPauseTimer;
	bool options = false;
	bool TitleTransition = false;

private:


	SDL_Texture* PauseFrame = nullptr;
	SDL_Texture* PauseTitle = nullptr;
	SDL_Texture* settingsLetters = nullptr;


	SDL_Texture* resumeButton = nullptr;
	SDL_Texture* optionsButton = nullptr;
	SDL_Texture* backToTitleButton = nullptr;
	SDL_Texture* exitButton = nullptr;
	SDL_Texture* returnButton = nullptr;

	SDL_Texture* resumeButtonOnIdle = nullptr;
	SDL_Texture* optionsButtonOnIdle = nullptr;
	SDL_Texture* backToTitleButtonOnIdle = nullptr;
	SDL_Texture* exitButtonOnIdle = nullptr;
	SDL_Texture* returnButtonOnIdle = nullptr;

	SDL_Texture* resumeButtonPressed = nullptr;
	SDL_Texture* optionsButtonPressed = nullptr;
	SDL_Texture* backToTitleButtonPressed = nullptr;
	SDL_Texture* exitButtonPressed = nullptr;
	SDL_Texture* returnButtonPressed = nullptr;
	
	//CHECBOX TEXTURES
	SDL_Texture* fullScreenCheckOn = nullptr;
	SDL_Texture* fullScreenCheckOff = nullptr;
	SDL_Texture* fullScreenTag = nullptr;
	SDL_Texture* VSyncOn = nullptr;
	SDL_Texture* VSyncOff = nullptr;

	SDL_Texture* fullScreenCheckOnOnIdle = nullptr;
	SDL_Texture* fullScreenCheckOffOnIdle = nullptr;
	SDL_Texture* VSyncOnOnIdle = nullptr;
	SDL_Texture* VSyncOffOnIdle = nullptr;

	SDL_Texture* fullScreenCheckOnPressed = nullptr;
	SDL_Texture* fullScreenCheckOffPressed = nullptr;
	SDL_Texture* VSyncOnPressed = nullptr;
	SDL_Texture* VSyncOffPressed = nullptr;
	//SLIDER TEXTURES
	SDL_Texture* baseSlider_fx = nullptr;
	SDL_Texture* baseSlider_music = nullptr;
	SDL_Texture* sliderSelector = nullptr;

	//GUI BUTTONS
	GuiButton* resumeButton_;
	GuiButton* optionsButton_;
	GuiButton* backToTitleButton_;
	GuiButton* exitButton_;
	GuiButton* returnButton_;
	//GUI CHECKBOX
	GuiCheckbox* fullScreenCheck_tag_;
	GuiCheckbox* fullScreenCheck_;
	GuiCheckbox* VSyncCheck;
	GuiCheckbox* VSyncCheck_tag_;

	//GUI SLIDER
	GuiSlider* musicVolumeSlider;
	GuiSlider* fxVolumeSlider;
};

#endif // __SCENE_FOREST_H__